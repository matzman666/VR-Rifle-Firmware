
#pragma once

// Enable debug output
#define DEBUG_OUTPUT 1

// Status LED pins
#define STATUS_LED0_PIN 	13
#define STATUS_LED1_PIN 	12

// Flash frequencies for status LEDs
#define STATUSLED_SLOWBLINKING_INTERVAL		 1000
#define STATUSLED_FASTBLINKIN_INTERVAL		 100

// Arduino analog pin joystick x-axis has been connected to
#define JOYSTICK_XAXIS_PIN			A2
// Whether x-axis should be inverted
#define JOYSTICK_XAXIS_INVERSE		true
// Arduino analog pin joystick y-axis has been connected to
#define JOYSTICK_YAXIS_PIN			A1
// Whether y-axis should be inverted
#define JOYSTICK_YAXIS_INVERSE		true
// Arduino digital pin joystick button has been connected to
#define JOYSTICK_BUTTON_PIN			5
// Deadzone around zero pose
#define JOYSTICK_DEADZONE			20
// Timeout for "touched" state
#define JOYSTICK_TOUCHED_TIMEOUT	500

// Arduino analog pin trigger axis has been connected to
#define TRIGGER_AXIS_PIN		A0
// Arduino digital pin trigger endstop has been connected to
#define TRIGGER_ENDSTOP_PIN		6
// Deadzone around zero pose
#define TRIGGER_DEADZONE		4

// Arduino digital pins the buttons have been connected to
#define BUTTON0_PIN		11 // System
#define BUTTON1_PIN		10 // Menu
#define BUTTON2_PIN		9 // Grip

// Haptic feedback related
#define HAPTICFEEDBACK_INPUT_PIN 		7
#define HAPTICFEEDBACK_OUTPUT_PIN 		8
#define HAPTICFEEDBACK_MAGNITUDE 		120
