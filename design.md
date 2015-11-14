# Design document

## Overview
The user presses switches on the input device. The state of all the
switches on the device is read out once per loop().

The new and old switch vectors are compared. Based on the changes in
the switch states, zero or more switch events are generated and placed
on the switch event stack. If there is more than one switch event in
one loop(), Release events are given priority, as this yields a
greater chance of staying out of INVALID.

Subsequently the state machine processes the switch event stack and
sends appropriate KeyEvents tp the usb driver. This is comparable to a
user typing on a normal keyboard.

## Process Switch State Machine

### IDLE / WAITING
geen toetsen ingedrukt - niks doen

* IDLE -> Press -> ONESWITCH
* IDLE !> Release

### ONESWITCH

* ONESWITCH -> Press -> TWOSWITCH --> KeyDown
* ONESWITCH -> Release -> IDLE --> KeyDown, KeyUp

### TWOSWITCH

* TWOSWITCH -> Press -> INVALID
* TWOSWITCH -> Release -> ONESWITCHUSED --> KeyUp


### ONESWITCHUSED

* ONESWITCHUSED -> Press -> TWOSWITCH
* ONESWITCHUSED -> Release -> IDLE


### INVALID

* INVALID -> Press -> INVALID --> EmptyKey
* INVALID -> Release(some switches still Pressed) -> INVALID
* INVALID -> Release(no switches still Pressed) t-> IDLE

