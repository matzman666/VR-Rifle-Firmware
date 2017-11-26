#pragma once

#include "config.h"
#include "Arduino.h"


/**
 * Represents a joystick consisting of two analog axes and a digital button.
 */
class Joystick {
public:
	Joystick(int8_t xPin, int8_t yPin, int8_t sPin) : _xPin(xPin), _yPin(yPin), _sPin(sPin) {}

	/**
	 * Configures the used Arduino ports.
	 */
	void init();

	/**
	 * Calibrates the zero position of the joystick.
	 *
	 * Should be called right at the beginning.
	 */
	void calibrateZeroPos();

	/**
	 * Updates the joystick state.
	 *
	 * Should be regularly called in the update loop.
	 *
	 * \param timestamp time value as returned by millis().
	 */
	void update(unsigned long timestamp);

	/**
	 * Returns whether the joystick state has been changed since the last update.
	 */
	bool hasChanged() {
		return _valuesChanged;
	}

	/**
	 * Returns the value of the x-axis.
	 *
	 * Value ranges from -32768 to 32767, 0 represents the zero position.
	 * Can be directly fed to the Vive tracker.
	 */
	short xAxis() {
		return _xValue;
	}


	/**
	 * Returns the value of the y-axis.
	 *
	 * Value ranges from -32768 to 32767, 0 represents the zero position.
	 * Can be directly fed to the Vive tracker.
	 */
	short yAxis() {
		return _yValue;
	}

	/**
	 * Returns whether the joystick button has been pressed.
	 */
	bool button() {
		return _sValue;
	}

	/**
	 * Returns whether the joystick has been "touched".
	 *
	 * Most joystick don't have a touch sensors unlike the Vive controller's touchpad this value is set based on whether the
	 * current joystick state did change. When there is a change the joystick is assumed to be "touched", and only after there
	 * was no state change for some time the joystick is supposed to be "untouched".
	 */
	bool touched() {
		return _sTouched;
	}

	/**
	 * Returns whether the joystick's zero position has been calibrated
	 */
	bool isCalibrated() {
		return _tIsCalibrated;
	}

private:
	// Arduino pins
	int8_t _xPin = -1;
	int8_t _yPin = -1;
	int8_t _sPin = -1;

	short _xZeroValue = 2048;
	short _xMaxValue = 4095;

	short _yZeroValue = 2048;
	short _yMaxValue = 4095;

	bool _valuesChanged = false;
	bool _tIsCalibrated = false;
	short _xValue = 0;
	short _yValue = 0;
	bool _sValue = false;
	bool _sTouched = false;
	uint32_t _sTouchedTimeout = 0;

	short _readAxis(int8_t pin, short zeroValue, short maxValue, bool inverse) {
		int raw = analogRead(pin);
		if (raw <= zeroValue + JOYSTICK_DEADZONE && raw >= zeroValue - JOYSTICK_DEADZONE) {
			raw = zeroValue;
		}
		if (raw < zeroValue) {
			if (inverse) {
				return map(raw, 0, zeroValue, 32767, 0);
			} else {
				return map(raw, 0, zeroValue, -32768, 0);
			}
		} else if (raw > zeroValue) {
			if (inverse) {
				return map(raw, zeroValue, maxValue, 0, -32768);
			} else {
				return map(raw, zeroValue, maxValue, 0, 32767);
			}
		} else {
			return 0;
		}
	}

};


/**
 * Inits the joystick.
 *
 * Convenience function to make adding more joystick easier.
 */
void joystick_init();


/**
 * Updates the joystick.
 *
 * Convenience function to make adding more joystick easier.
 */
void joystick_update(unsigned long timestamp);


/**
 * Object representing joystick #0
 */
extern Joystick joystick0;

