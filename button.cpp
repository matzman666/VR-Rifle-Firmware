
#include "button.h"


Button button0(BUTTON0_PIN);
Button button1(BUTTON1_PIN);
Button button2(BUTTON2_PIN);


void button_init() {
	button0.init();
	button1.init();
	button2.init();
}


void button_update(unsigned long timestamp) {
	button0.update(timestamp);
	button1.update(timestamp);
	button2.update(timestamp);
}

void Button::init() {
	if (_sPin > 0) {
		pinMode(_sPin, INPUT_PULLUP);
	}
}

void Button::update(unsigned long) {
	_valuesChanged = false;
	// Update button state
	if (_sPin > 0) {
		bool v = !digitalRead(_sPin);
		if (v != _sValue) {
			_valuesChanged = true;
			_sValue = v;
		}
	}
}

