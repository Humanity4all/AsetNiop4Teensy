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

## Terminology

There can be a bit of confusion on what we mean with key,
character and switch - since what a user would normally call a key is actually
a switch. When we use the term key, we mean a key in the software sense, more
specifically a keycode paired a keyDown or keyUp event. Something we send to
the attached computer. What the user would cal a key, we call a switch, a
physical device with 2 states, whose state is indicated by a LOW or HIGH
voltage in the attached microprocessor pin. We keep calling that a switch in
the software until it goes through the translation service and becomes a key.

To complicate things, we call the device we're building a keyboard, though
input device would be more accurate. Since that would be really confusing, to
name state carrying objects a keyboard when we're actually talking about
switches, and keys don't come into it at all, we've decided on the term
switchboard.

## Top-Level design

Hardware software interface (PinInterface) polls input pinns. By comparing with
the current SwitchVector inside the SwitchBoard state machine, it determines if
there have been events (switch press or release). It communicates these events
to the SwitchBoard.

The SwitchBoard state machine determines if a keyevent needs to be sent out. It
doesn't care or know which key, all it knows is the SwitchVector. If something
does need to be sent, it calls the Translation service with the KeyVector and
up/down/empty event.

The translation service interprets the SwitchVector and handles translation to
keys (and the communication of said keys to operating system). It does this
dependent on which layer is currently active, and what the modifier states are.

## PinInterface

### PinInterface::PinInterface
Allocate memory, and create a Bounce object for every pin.
Also creates a SwitchBoard state machine.

### PinInterface::update
Poll pins (or more accurately, the bounce objects), record changes and call the
switchboard state machine accordingly. This is the method called by the loop()
function in main.cpp

### PinInterface::~PinInterface
Release memory.

## SwitchBoard State Machine

### IDLE / WAITING
geen toetsen ingedrukt - niks doen

* IDLE -> Press -> ONESWITCH --> KeyDown(nochord)
* IDLE !> Release

### ONESWITCH

* ONESWITCH -> Press -> TWOSWITCH --> KeyDown(nochord)
* ONESWITCH -> Release -> IDLE --> KeyDown(chord), KeyUp(chord)

### TWOSWITCH

* TWOSWITCH -> Press -> INVALID --> EmptyKey
* TWOSWITCH -> Release -> ONESWITCHUSED --> KeyUp(chord)


### ONESWITCHUSED

* ONESWITCHUSED -> Press -> TWOSWITCH --> KeyDown(nochord)
* ONESWITCHUSED -> Release -> IDLE --> KeyUp(nochord)


### INVALID

* INVALID -> Press -> INVALID
* INVALID -> Release(some switches still Pressed) -> INVALID
* INVALID -> Release(no switches still Pressed) -> IDLE

