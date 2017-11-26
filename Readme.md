
![license_gpl3](https://img.shields.io/badge/License-GPL%203.0-green.svg)

# DIY VR-Rifle Firmware

This is the source code of the firmware powering my DIY VR-rifle (the blueprints and used parts can be found [here](https://raw.githubusercontent.com/matzman666/VR-Rifle-Blueprints)).

I wrote it for use with an Arduino Due, I don't know if it works with other Arduino boards.

Requires a [modified Arduino USB host library](https://github.com/matzman666/USBHost) with support for the Vive tracker.

## Features

- Supports a joystick (with two analog axes and a digital button).
- Supports an analog trigger (consisting of an analog axis and a digital endstop).
- Supports System/Menu/Grip buttons.
- Supports a status LED.

## Usage

Either open Firmware.ino in the Arduino IDE, or import as existing project into Eclipse (requires Arduino addon).
 