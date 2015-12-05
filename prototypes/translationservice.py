"""TranslationService State Machine."""


# TODO merge key_up, key_down and possibly empty_key, they have
# too much code in common.
# TODO figure out which methods should be private/ protected
class TranslationServiceState(object):

    """Prototype for TranslationService states."""

    def __init__(self):
        """Set keymaps and stuff."""

    def key_up(self, state_machine, switch_vector, chord):
        """
        Process key_up event.

        switch_vector: effective switch states
        chord: boolean, if this event belongs to chorded or non-chorded mode
        """
        pass

    def key_down(self, state_machine, switch_vector, chord):
        """Process key_down event.

        switch_vector: effective switch states
        chord: boolean, if this event belongs to chorded or non-chorded mode
        """
        pass

    def empty_key(self, state_machine, switch_vector, chord):
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

    def key_up(self, state_machine, switch_vector, chord):
        """Send key to os, only if chorded."""
        if chord:
            switch1 = switch_vector.index(1)
            # set switch1 to 0, so we can find the second active switch
            switch_vector[switch1] = 0
            # we're not sure if a second switch is pressed at this point
            try:
                switch2 = switch_vector.index(1)
            except ValueError:
                switch2 = switch1
            key = self._keymap[switch1][switch2]
            return state_machine.send_key(key, 'up')

    def key_down(self, state_machine, switch_vector, chord):
        """Set key to os, only if chorded."""
        if chord:
            switch1 = switch_vector.index(1)
            # set switch1 to 0, so we can find the second active switch
            switch_vector[switch1] = 0
            # we're not sure if a second switch is pressed at this point
            try:
                switch2 = switch_vector.index(1)
            except ValueError:
                switch2 = switch1
            key = self._keymap[switch1][switch2]
            return state_machine.send_key(key, 'down')

    def empty_key(self, state_machine, switch_vector, chord):
        """Send empty key state."""
        return state_machine.send_key("EmptyKey", 'reset')


class ExampleNonChordedLayer(TranslationServiceState):

    """
    Example layer without chording.

    This is a very simple non-chorded layer, it's exclusively
    non-chorded. In reality, some of the switches will be able
    to form chords, to retain the ability to switch layers and
    use modifiers.
    """

    def __init__(self):
        """Set basic keymap."""
        TranslationServiceState.__init__(self)
        self._keymap = ['a', 'b', 'c']

    def key_up(self, state_machine, switch_vector, chord):
        """Send key to os."""
        key = self._keymap[switch_vector.index(1)]
        return state_machine.send_key(key, 'up')

    def key_down(self, state_machine, switch_vector, chord):
        """Send key to os."""
        key = self._keymap[switch_vector.index(1)]
        return state_machine.send_key(key, 'down')

    def empty_key(self, state_machine, switch_vector, chord):
        """Send EmptyKey."""
        # TODO non-chorded layers don't always reset at more than 2
        # keys, implement this. In this case, it is exclusively
        # non-chorded, so it will never enter an invalid state.
        # TODO: this method needs to know if it's a down or up
        return state_machine.send_key("EmptyKey", 'reset')


class TranslationService(object):

    """TranslationService state machine."""

    def __init__(self):
        """Set state to ExampleLayer and initialize modifiers."""
        self._state = ExampleLayer()
        # TODO initialize modifiers

    def process_protkey_event(self, protokey_event):
        """Pass on key event."""
        if protokey_event.event == "up":
            self._state.key_up(
                self,
                protokey_event.switch_vector,
                protokey_event.is_chord)
        elif protokey_event.event == "down":
            self._state.key_down(
                self,
                protokey_event.switch_vector,
                protokey_event.is_chord)
        elif protokey_event.event == "reset":
            self._state.empty_key(
                self,
                protokey_event.switch_vector,
                protokey_event.is_chord)
        else:
            raise NotImplementedError

    def switch_state(self, new_state):
        """Change state."""
        self._state = new_state

    def send_key(self, key, event):
        """Send key to operating system."""
        # Here, the key will be translated to a key code the os
        # understands, using self.use_modifiers
        return key, event  # for now just return so we can test

    def set_modifier(self, key_event):
        """Set modifier state."""
        # TODO set modifier to either idle, active or lazy.
        pass

    def use_modifiers(self):
        """Return modifier states + update states."""
        # TODO return modifier states and change active modifiers to idle
        pass
