
#include "config.h"
#include "joystick.h"


Joystick joystick0(JOYSTICK_XAXIS_PIN, JOYSTICK_YAXIS_PIN, JOYSTICK_BUTTON_PIN);


void joystick_init() {
	joystick0.init();
	joystick0.calibrateZeroPos();
}


void joystick_update(unsigned long timestamp) {
	joystick0.update(timestamp);
}


void Joystick::init() {
	if (_sPin > 0) {
		pinMode(_sPin, INPUT_PULLUP);
	}
}


void Joystick::calibrateZeroPos() {
	// Read x/y raw values several times and calculate mean
	int maxCount = 10;
	long xvalue = 0;
	long yvalue = 0;
	for (int i = 0; i < maxCount; i++) {
		if (_xPin > 0) {
			xvalue += analogRead(_xPin);
		}
		if (_yPin > 0) {
			yvalue += analogRead(_yPin);
		}
		delay(100);
	}
	if (_xPin > 0) {
		_xZeroValue = xvalue / maxCount;
	}
	if (_yPin > 0) {
		_yZeroValue = yvalue / maxCount;
	}
	_tIsCalibrated = true;

#if DEBUG_OUTPUT == 1
	Serial.write("Joystick successfully calibrated.\n");
#endif
}


void Joystick::update(unsigned long timestamp) {
	_valuesChanged = false;
	// Update x-axis
	if (_xPin > 0) {
		auto v = _readAxis(_xPin, _xZeroValue, _xMaxValue, JOYSTICK_XAXIS_INVERSE);
		if (v != _xValue) {
			_valuesChanged = true;
			_xValue = v;
		}
	}
	// Update y-axis
	if (_yPin > 0) {
		auto v = _readAxis(_yPin, _yZeroValue, _yMaxValue, JOYSTICK_YAXIS_INVERSE);
		if (v != _yValue) {
			_valuesChanged = true;
			_yValue = v;
		}
	}
	// Update switch
	if (_sPin > 0) {
		bool v = !digitalRead(_sPin);
		if (v != _sValue) {
			_valuesChanged = true;
			_sValue = v;
		}
	}
	// Update "touched" state
	if (_valuesChanged || _xValue != 0 || _yValue != 0 ) {
		_sTouched = true;
		_sTouchedTimeout = timestamp + JOYSTICK_TOUCHED_TIMEOUT;
	} else if (_sTouchedTimeout <= timestamp) {
		_sTouched = false;
	}
}
