
#pragma once

#include "config.h"
#include <Arduino.h>


/**
 * Represents a digital button.
 */
class Button {
public:
	Button(int8_t sPin) : _sPin(sPin) {}

	/**
	 * Configures the used Arduino ports.
	 */
	void init();

	/**
	 * Updates the button state.
	 *
	 * Should be regularly called in the update loop.
	 *
	 * \param timestamp time value as returned by millis().
	 */
	void update(unsigned long timestamp);

	/**
	 * Returns whether the button state has been changed since the last update.
	 */
	bool hasChanged() {
		return _valuesChanged;
	}

	/**
	 * Returns whether the button is pressed.
	 */
	bool button() {
		return _sValue;
	}

private:
	// Arduino pins
	int8_t _sPin = -1;

	bool _valuesChanged = false;
	bool _sValue = false;

};


/**
 * Inits the buttons.
 *
 * Convenience function to make handling several buttons at once easier.
 */
void button_init();


/**
 * Updates the buttons.
 *
 * Convenience function to make handling several buttons at once easier.
 */
void button_update(unsigned long timestamp);


/**
 * Object representing button #0
 */
extern Button button0;

/**
 * Object representing button #1
 */
extern Button button1;

/**
 * Object representing button #2
 */
extern Button button2;

