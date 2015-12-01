"""TranslationService State Machine."""


class TranslationServiceState(object):

    """Prototype for TranslationService states."""

    def __init__(self):
        """Set keymaps and stuff."""

    def key_up(self, switch_vector, chord):
        """
        Process key_up event.

        switch_vector: effective switch states
        chord: boolean, if this event belongs to chorded or non-chorded mode
        """
        pass

    def key_down(self, switch_vector, chord):
        """Process key_down event.

        switch_vector: effective switch states
        chord: boolean, if this event belongs to chorded or non-chorded mode
        """
        pass

    def empty_key(self):
        """Entering invalid state, clear all keys."""
        pass


class ExampleLayer(TranslationServiceState):

    """Example layer with chording."""

    def __init__(self):
        """Set basic keymap."""
        TranslationServiceState.__init__(self)
        self._keymap = [
            ['a', 'b', 'c'],
            ['b', 'd', 'e'],
            ['c', 'e', 'f']]

    def key_up(self, switch_vector, chord):
        """Send key to os, only if chorded."""
        if chord:
            # TODO read from switch vector which switches are pressed
            # and use that to read key from keymap.
            print switch_vector

    def key_down(self, switch_vector, chord):
        """Set key to os, only if chorded."""
        if chord:
            # TODO: read switch vector, use it to get key from keymap
            print switch_vector

    def empty_key(self):
        """Send empty key state."""
        print "EmptyKey"


class ExampleNonChordedLayer(TranslationServiceState):

    """Example layer without chording."""

    def __init__(self):
        """Set basic keymap."""
        TranslationServiceState.__init__(self)
        self._keymap = ['a', 'b', 'c']

    def key_up(self, switch_vector, chord):
        """Send key to os."""
        # TODO read switch vector, use it to get key from keymap
        print switch_vector

    def key_down(self, switch_vector, chord):
        """Send key to os."""
        # TODO read switch vector, use it to get key from keymap
        print switch_vector

    def empty_key(self):
        """Send EmptyKey."""
        print "EmptyKey"""


class TranslationService(object):

    """TranslationService state machine."""

    def __init__(self):
        """Set state to ExampleLayer."""
        self._state = ExampleLayer()

    def key_up(self, switch_vector, chord):
        """Pass on key event."""
        self._state.key_up(switch_vector, chord)

    def key_down(self, switch_vector, chord):
        """Pass on key event."""
        self._state.key_up(switch_vector, chord)

    def empty_key(self):
        """Pass on key event."""
        self._state.empty_key()

    def switch_state(self, new_state):
        """Change state."""
        self._state = new_state
