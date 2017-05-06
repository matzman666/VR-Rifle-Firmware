
#include "trigger.h"


Trigger trigger0(TRIGGER_AXIS_PIN, TRIGGER_ENDSTOP_PIN);


void trigger_init() {
	trigger0.init();
	trigger0.calibrateZeroPos();
}


void trigger_update(unsigned long timestamp) {
	trigger0.update(timestamp);
}

void Trigger::init() {
	if (_sPin > 0) {
		pinMode(_sPin, INPUT_PULLUP);
	}
}


void Trigger::calibrateZeroPos() {
	// Read raw values several times and calculate mean
	int maxCount = 10;
	long tvalue = 0;
	for (int i = 0; i < maxCount; i++) {
		if (_tPin > 0) {
			tvalue += analogRead(_tPin);
		}
		delay(100);
	}
	if (_tPin > 0) {
		_tRawZeroValue = tvalue / maxCount;
	}
}


void Trigger::update(unsigned long timestamp) {
	_valuesChanged = false;
	unsigned short _tRawValue = 0;
	// Read endstop
	bool _sRawValue = false;
	if (_sPin > 0) {
		bool v = !digitalRead(_sPin);
		_sRawValue = v;
	}
	// Read analog trigger axis
	if (_tPin > 0) {
		int raw = analogRead(_tPin);
		if (raw <= _tRawZeroValue + TRIGGER_DEADZONE) {
			raw = _tRawZeroValue;
		}
		if (!_tIsCalibrated) {
			if (_sRawValue) {
				_tRawMaxValue = raw;
				_tIsCalibrated = true;
#if DEBUG_OUTPUT == 1
				char buffer[256];
				snprintf(buffer, 256, "%u: Trigger successfully calibrated.\n", timestamp);
				Serial.write(buffer);
#endif
			}
		} else {
			if (_tRawValue > _tRawMaxValue) {
				_tRawValue = _tRawMaxValue;
			}
			_tRawValue = map(raw, _tRawZeroValue, _tRawMaxValue, 0, 255);
		}
	}
	// Update trigger state
	if (_tIsCalibrated) {
		unsigned short tval = 0;
		bool sval = false;
		if (_sRawValue) {
			tval = 255;
			sval = true;
		} else {
			tval = _tRawValue;
		}
		if (_tValue != tval || _sValue != sval) {
			_valuesChanged = true;
			_sValue = sval;
			_tValue = tval;
		}
	}
}

