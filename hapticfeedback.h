#pragma once

#include "config.h"
#include "Arduino.h"


// forward declaration
class ViveTrackerController;


/**
 * Represents a joystick consisting of two analog axes and a digital button.
 */
class HapticFeedback {
public:
	HapticFeedback(int8_t inPin, int8_t outPin) {
		_inPin = inPin;
		_outPin = outPin;
	}

	/**
	 * Configures the used Arduino ports.
	 */
	void init(ViveTrackerController* controller);

	/**
	 * Enable/disable haptic feedback.
	 */
	void enable(bool val) {
		_enabled = val;
		if (!val && _outPin >= 0) {
			digitalWrite(_outPin, 0);
		}
	}

private:
	// Arduino pins
	static int8_t _inPin;
	static int8_t _outPin;

	static ViveTrackerController* _controller;
	static bool _enabled;

	static void inputPinTriggerFunc();
};



/**
 * Object representing haptic feedback
 */
extern HapticFeedback hapticFeedback;

