"""SwitchBoard state machine."""


class SwitchBoardState(object):

    """SwitchBoard State prototype."""

    def press(self):
        """Process switch press."""
        pass

    def release(self):
        """Process switch release."""
        pass


class Idle(SwitchBoardState):

    """No switches are pressed."""

    def press(self):
        """Switch state to OneSwitch + issue KeyDown(nochord)."""
        pass

    def release(self):
        """Impossible - no switches are pressed."""
        pass


class OneSwitch(SwitchBoardState):

    """One switch is pressed."""

    def press(self):
        """Switch state to TwoSwitch + issue KeyDown(chord) event."""
        pass

    def release(self):
        """Switch state to Idle + issue KeyDown(chord) & KeyUp(chord) event."""
        pass


class OneSwitchUsed(SwitchBoardState):

    """One switch is pressed, but a key event has been issued already."""

    def press(self):
        """Switch state to TwoSwitch + KeyDown(nochord)."""
        pass

    def release(self):
        """Switch state to Idle + KeyUp(nochord)."""
        pass


class TwoSwitch(SwitchBoardState):

    """Two switches are pressed."""

    def press(self):
        """Switch state to Invalid + issue EmptyKey event."""
        pass

    def release(self):
        """Switch state to OneSwitchUsed + issue KeyUp(chord) event."""
        pass


class Invalid(SwitchBoardState):

    """
    Three or more switches are or were pressed.

    This state is activated once three switches or more
    are pressed. It stays active until zero switches
    are pressed.
    """

    def press(self):
        """Stay in invalid."""
        pass

    def release(self):
        """Either return to Idle or stay in Invalid."""
        pass


class SwitchBoard(object):

    """SwitchBoard state machine."""

    def __init__(self):
        """Set state to Idle."""
        self.state = Idle()

    def press(self):
        """Pass on switch press to state."""
        self.state.press()

    def release(self):
        """Pass on switch release to state."""
        self.state.release()
