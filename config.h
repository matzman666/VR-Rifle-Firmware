
#pragma once

// Enable debug output
#define DEBUG_OUTPUT 1

// Arduino analog pin joystick x-axis has been connected to
#define JOYSTICK_XAXIS_PIN			A0
// Whether x-axis should be inverted
#define JOYSTICK_XAXIS_INVERSE		true
// Arduino analog pin joystick y-axis has been connected to
#define JOYSTICK_YAXIS_PIN			A1
// Whether y-axis should be inverted
#define JOYSTICK_YAXIS_INVERSE		true
// Arduino digital pin joystick button has been connected to
#define JOYSTICK_BUTTON_PIN			53
// Deadzone around zero pose
#define JOYSTICK_DEADZONE			20
// Timeout for "touched" state
#define JOYSTICK_TOUCHED_TIMEOUT	500

// Arduino analog pin trigger axis has been connected to
#define TRIGGER_AXIS_PIN		A2
// Arduino digital pin trigger endstop has been connected to
#define TRIGGER_ENDSTOP_PIN		51
// Deadzone around zero pose
#define TRIGGER_DEADZONE		4

// Flash frequencies for status led
#define STATUSLED_UNCALIBRATED_INTERVAL		 300
#define STATUSLED_DISCONNECTED_INTERVAL		 100
#define STATUSLED_CALIBRATED_INTERVAL		1000

// Arduino digital pins the buttons have been connected to
#define BUTTON0_PIN		5 // System
#define BUTTON1_PIN		6 // Menu
#define BUTTON2_PIN		4 // Grip


