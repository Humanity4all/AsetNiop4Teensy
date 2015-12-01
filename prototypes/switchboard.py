"""SwitchBoard state machine"""


class SwitchBoardState(object):

    """SwitchBoard State prototype"""

    def press(self):
        """Process switch press."""
        pass

    def release(self):
        """Process switch release."""
        pass


class Idle(SwitchBoardState):

    """No switches are pressed."""

    def press(self):
        pass

    def release(self):
        pass


class OneSwitch(SwitchBoardState):

    """One switch is pressed."""

    def press(self):
        pass

    def release(self):
        pass


class TwoSwitch(SwitchBoardState):

    """Two switches are pressed."""

    def press(self):
        pass

    def release(self):
        pass


class Invalid(SwitchBoardState):

    """
    Three or more switches are or were pressed.

    This state is activated once three switches or more
    are pressed. It stays active until zero switches
    are pressed.
    """

    def press(self):
        pass

    def release(self):
        pass


class SwitchBoard(object):

    """SwitchBoard state machine"""

    def __init__(self):
        self.state = Idle()

    def press(self):
        """Pass on switch press to state."""
        self.state.press()

    def release(self):
        """Pass on switch release to state."""
        self.state.release()
