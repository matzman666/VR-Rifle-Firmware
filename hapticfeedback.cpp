
#include "config.h"
#include "hapticfeedback.h"
#include "ViveTrackerController.h"


HapticFeedback hapticFeedback(HAPTICFEEDBACK_INPUT_PIN, HAPTICFEEDBACK_OUTPUT_PIN);

int8_t HapticFeedback::_inPin = -1;
int8_t HapticFeedback::_outPin = -1;
bool HapticFeedback::_enabled = false;
ViveTrackerController* HapticFeedback::_controller = nullptr;


void HapticFeedback::init(ViveTrackerController* controller) {
	HapticFeedback::_controller = controller;
	if (_inPin > 0) {
		pinMode(_inPin, INPUT);
		attachInterrupt(digitalPinToInterrupt((unsigned)_inPin), inputPinTriggerFunc, CHANGE);
	}
	if (_outPin > 0) {
		pinMode(_outPin, OUTPUT);
		digitalWrite(_outPin, LOW);
	}

}


void HapticFeedback::inputPinTriggerFunc() {
	auto raw = digitalRead(_inPin);
	if (_enabled && _outPin > -1) {
		if (raw) {
			// Lower cutoff frequency of low-pass filter before turning on vibration motors
			// to avoid tracking problems due to the vibrations
			_controller->setLpfConfig(VIVETRACKER_LPF_5HZ);
			analogWrite(_outPin, HAPTICFEEDBACK_MAGNITUDE);
		} else {
			analogWrite(_outPin, 0);
			// Set cutoff frequency of low-pass filter back to default
			_controller->setLpfConfig(VIVETRACKER_LPF_DEFAULT);
		}
	}
}


