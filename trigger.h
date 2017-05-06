
#pragma once

#include "config.h"
#include <Arduino.h>


/**
 * Represents the trigger consisting of an analog axis and a digital endstop.
 *
 * One word on calibration: The zero pose should be calibrated right at the beginning. But to be able to use the trigger
 * the end position also needs to be calibrated. This is done automatically the first time the trigger is fully pulled
 * (meaning the endstop gets activated). Before this has happened no trigger events are reported.
 */
class Trigger {
public:
	Trigger(int8_t tPin, int8_t sPin) : _tPin(tPin), _sPin(sPin) {}

	/**
	 * Configures the used Arduino ports.
	 */
	void init();

	/**
	 * Calibrates the zero position of the trigger.
	 *
	 * Should be called right at the beginning.
	 */
	void calibrateZeroPos();

	/**
	 * Updates the trigger state.
	 *
	 * Should be regularly called in the update loop.
	 *
	 * \param timestamp time value as returned by millis().
	 */
	void update(unsigned long timestamp);

	/**
	 * Returns whether the trigger state has been changed since the last update.
	 */
	bool hasChanged() {
		return _valuesChanged;
	}

	/**
	 * Returns the value of the analog trigger axis.
	 *
	 * Value ranges from 0 to 255, 0 represents the zero position.
	 * Can be directly fed to the Vive tracker.
	 * Note: The Vive tracker's documentation states a larger value range,
	 * but in reality only one byte is used for the analog trigger value.
	 */
	uint8_t triggerAxis() {
		return _tValue;
	}

	/**
	 * Returns whether the digital endstop has been activated.
	 */
	bool triggerButton() {
		return _sValue;
	}

	/**
	 * Returns whether the trigger has been fully calibrated.
	 */
	bool isCalibrated() {
		return _tIsCalibrated;
	}

private:
	// Arduino pins
	int8_t _tPin = -1;
	int8_t _sPin = -1;

	int _tRawZeroValue = 0;
	int _tRawMaxValue = 65535;
	bool _tIsCalibrated = false;

	bool _valuesChanged = false;
	unsigned short _tValue = 0;
	bool _sValue = false;

};


/**
 * Inits the trigger.
 *
 * Convenience function to make adding more triggers easier.
 */
void trigger_init();


/**
 * Updates the trigger.
 *
 * Convenience function to make adding more triggers easier.
 */
void trigger_update(unsigned long timestamp);


/**
 * Object representing trigger #0
 */
extern Trigger trigger0;

