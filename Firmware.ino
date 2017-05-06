
#include <Arduino.h>
#include "config.h"
#include "logging.h"
#include "joystick.h"
#include "trigger.h"
#include "button.h"
#include <ViveTrackerController.h>

// Init USB
USBHost usb;
ViveTrackerController tracker(usb);

void setup() {
	// Set up serial connection
	Serial.begin(115200);

	// Set adc converter resolution to 12 bit
	analogReadResolution(12);

	// setup joystick, trigger, buttons and status led
	pinMode(LED_BUILTIN, OUTPUT);
	joystick_init();
	trigger_init();
	button_init();

#if DEBUG_OUTPUT == 1
	Serial.write("VR Rifle Firmware v0.1-alpha1 successfully loaded.\n");
#endif
}


bool statusLedState = false;
uint32_t statusLedInterval = STATUSLED_UNCALIBRATED_INTERVAL;
uint32_t statusLedNextChange = 0;

bool _lastUSBConnectState = false;


void loop() {
	auto timestamp = millis();
	// Update USB connection state
	tracker.Task();

	// Blink the status led
	// It has three distinct states:
	// 1) joystick/trigger are not calibrated (default: 3 flashes per second)
	// 1) USB is not connected (default: 10 flashes per second)
	// 1) Everything is ok (default: 1 flash per second)
	if (timestamp >= statusLedNextChange) {
		statusLedState = !statusLedState;
		digitalWrite(LED_BUILTIN, statusLedState ? HIGH : LOW);
		if (!joystick0.isCalibrated() || !trigger0.isCalibrated()) {
			statusLedNextChange = timestamp + STATUSLED_UNCALIBRATED_INTERVAL;
		} else if (!_lastUSBConnectState) {
			statusLedNextChange = timestamp + STATUSLED_DISCONNECTED_INTERVAL;
		} else {
			statusLedNextChange = timestamp + STATUSLED_CALIBRATED_INTERVAL;
		}
	}

	// Update joystick, trigger and buttons
	joystick_update(timestamp);
	trigger_update(timestamp);
	button_update(timestamp);

	uint8_t buttons = 0;
	int16_t padX = 0;
	int16_t padY = 0;
	uint8_t trigger = 0;
	uint16_t batteryLevel = 0;

	// read joystick state
	padX = joystick0.xAxis();
	padY = joystick0.yAxis();
	// update button state related to joystick
	if (joystick0.touched()) {
		buttons |= VIVETRACKER_BUTTON_PADTOUCHED;
	}
	if (joystick0.button()) {
		buttons |= VIVETRACKER_BUTTON_PADTRIGGERED | VIVETRACKER_BUTTON_PADTOUCHED;;
	}

#if DEBUG_OUTPUT == 1
	if (joystick0.hasChanged()) {
		char buffer[256];
		snprintf(buffer, 256, "%u: JS: %hi - %hi - %hhx \n", timestamp, padX, padY, joystick0.button());
		Serial.write(buffer);
	}
#endif

	// read trigger state
	trigger = trigger0.triggerAxis();
	// update button state related to trigger
	if (trigger0.triggerButton()) {
		buttons |= VIVETRACKER_BUTTON_TRIGGER;
	}

#if DEBUG_OUTPUT == 1
	if (trigger0.hasChanged()) {
		char buffer[256];
		snprintf(buffer, 256, "%u: T: %hu - %hhx \n", timestamp, trigger, trigger0.triggerButton());
		Serial.write(buffer);
	}
#endif

	// read system button state
	if (button0.button()) {
		buttons |= VIVETRACKER_BUTTON_SYSTEM;
	}

	// read menu button state
	if (button1.button()) {
		buttons |= VIVETRACKER_BUTTON_MENU;
	}

	// read grip button state
	if (button2.button()) {
		buttons |= VIVETRACKER_BUTTON_GRIP;
	}

#if DEBUG_OUTPUT == 1
	if (button0.hasChanged() || button1.hasChanged() || button2.hasChanged()) {
		char buffer[256];
		snprintf(buffer, 256, "%u: B: %hhx - %hhx - %hhx\n", timestamp, button0.button(), button1.button(), button2.button());
		Serial.write(buffer);
	}
#endif

	if (tracker.isConnected()) {
		if (!_lastUSBConnectState) {
#if DEBUG_OUTPUT == 1
			char buffer[256];
			snprintf(buffer, 256, "%u: USB connection established.\n", timestamp);
			Serial.write(buffer);
#endif
			_lastUSBConnectState = true;
		}
		// send state to tracker via USB
		tracker.setTrackerStatus(buttons, padX, padY, trigger, batteryLevel);
	} else if (_lastUSBConnectState) {
#if DEBUG_OUTPUT == 1
		char buffer[256];
		snprintf(buffer, 256, "%u: USB connection lost.\n", timestamp);
		Serial.write(buffer);
#endif
		_lastUSBConnectState = false;
	}

	// Documentation says we need to wait more than 10 ms before sending another data packet to the tracker.
	delay(11);
}
