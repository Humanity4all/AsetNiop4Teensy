"""SwitchBoard state machine."""

from collections import namedtuple

# A protokeyevent is a key movement on
# the virtual keyboard. A protokeyevent
# indicates a keydown or keyup event, or
# a reset of the entire virtual keyboard.
#
# At this point it is still unknown which
# key will be making the movement, hence
# the 'proto'. It carries the switchvector
# so the translation service can determine this
# and make it an actual key event.

# switch_vector: list of pinstates relevant to event

# event can be
# 'up': virtual key is to be released
# 'down': virtual key is to be pressed
# 'reset': entire virtual keyboard should be reset

# chord: Bool - indicates relevance of event to chord and nochord mode
ProtoKeyEvent = namedtuple('ProtoKeyEvent', [
    'event',
    'switch_vector',
    'is_chord'])

# For a down event, the switch_vector is the vector it resulted in.
# For an up event, the switch_vector is the vector it came from.
SwitchEvent = namedtuple('SwitchEvent', [
    'event',
    'switch_vector'])


class SwitchBoardState(object):

    """SwitchBoard State prototype."""

    def press(self, state_machine, switch_vector):
        """Process switch press."""
        raise NotImplementedError

    def release(self, state_machine, switch_vector):
        """Process switch release."""
        raise NotImplementedError


class Idle(SwitchBoardState):

    """No switches are pressed."""

    def press(self, state_machine, switch_vector):
        """Switch state to OneSwitch + issue KeyDown(nochord)."""
        state_machine.switch_state(OneSwitch())
        return [ProtoKeyEvent('down', switch_vector, False)]

    def release(self, state_machine, switch_vector):
        """Impossible - no switches are pressed."""
        return None


class OneSwitch(SwitchBoardState):

    """One switch is pressed."""

    def press(self, state_machine, switch_vector):
        """Switch state to TwoSwitch + issue KeyDown(chord) event."""
        state_machine.switch_state(TwoSwitch())
        return [ProtoKeyEvent('down', switch_vector, True)]

    def release(self, state_machine, switch_vector):
        """Switch state to Idle + issue KeyDown(chord) & KeyUp(chord) event."""
        state_machine.switch_state(Idle())
        return [
            ProtoKeyEvent('down', switch_vector, True),
            ProtoKeyEvent('up', switch_vector, True)]


class OneSwitchUsed(SwitchBoardState):

    """One switch is pressed, but a key event has been issued already."""

    def press(self, state_machine, switch_vector):
        """Switch state to TwoSwitch + KeyDown(nochord)."""
        state_machine.switch_state(TwoSwitch())
        return [ProtoKeyEvent('down', switch_vector, True)]

    def release(self, state_machine, switch_vector):
        """Switch state to Idle + KeyUp(nochord)."""
        state_machine.switch_state(Idle())
        return [ProtoKeyEvent('up', switch_vector, False)]


class TwoSwitch(SwitchBoardState):

    """Two switches are pressed."""

    def press(self, state_machine, switch_vector):
        """Switch state to ManySwitch + issue EmptyKey event."""
        state_machine.switch_state(ManySwitch())
        return [
            ProtoKeyEvent('down', switch_vector, False),
            ProtoKeyEvent('reset', switch_vector, True)]

    def release(self, state_machine, switch_vector):
        """Switch state to OneSwitchUsed + issue KeyUp(chord) event."""
        state_machine.switch_state(OneSwitchUsed())
        return [ProtoKeyEvent('up', switch_vector, True)]


class ManySwitch(SwitchBoardState):

    """
    Three or more switches are or were pressed.

    This state is activated once three switches or more
    are pressed. It stays active until zero switches
    are pressed.
    """

    def press(self, state_machine, switch_vector):
        """Stay in invalid."""
        return [ProtoKeyEvent('down', switch_vector, False)]

    def release(self, state_machine, switch_vector):
        """Either return to Idle or stay in ManySwitch."""
        if switch_vector.count(1) <= 1:
            state_machine.switch_state(Idle())
        return [ProtoKeyEvent('up', switch_vector, False)]


class SwitchBoard(object):

    """SwitchBoard state machine."""

    def __init__(self):
        """Set state to Idle."""
        self._state = Idle()

    def switch_state(self, new_state):
        """Change state."""
        self._state = new_state

    def process_switch_event(self, switch_event):
        """Process a switch event."""
        if switch_event.event == "up":
            return self._state.release(self, switch_event.switch_vector)
        elif switch_event.event == "down":
            return self._state.press(self, switch_event.switch_vector)
        else:
            raise
