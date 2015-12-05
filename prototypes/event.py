"""Event class, to carry around information on switch states."""


class Event(object):

    """
    Event to carry around switch state info.

    We went for different event types throughout the code base,
    switch events, protokey events, switch vectors, event strings,
    all kinds of information flying around. And in the end, it turns
    out we need all the info that we filtered out in the beginning
    anyway. So why not make a single event with the necessary info?
    """

    def __init__(self, raw_switch_state):
        """Set (effective) switch vector."""
        self._raw_switch_state = raw_switch_state
        self._old_switch_state = raw_switch_state

        # On a rising edge (switch release), the active switch
        # is a 1. On a falling edge (switch press), the active switch
        # is also a 1.
        self._effective_switch_vector = None
        self._get_effective_switch_vector()

        # Rising or falling edge
        self.edge = None
        # Up, down or reset
        self.event = None
        # True or False
        self.is_chord = None

    def _get_effective_switch_vector(self):
        """Translate raw switch states to effective switch vector."""
        diff = self.state_diff()
        self._effective_switch_vector = self._raw_switch_state[:]
        if diff is not None:
            if self._effective_switch_vector[diff] == 0:
                self.edge = 'falling'
            else:
                self.edge = 'rising'
            self._effective_switch_vector[diff] = 1

    def new_switch_state(self, raw_switch_state):
        """Update (eftective) switch vector. (used by PinInterface)."""
        self._old_switch_state = self._raw_switch_state
        self._raw_switch_state = raw_switch_state
        self._get_effective_switch_vector()

    def set_event_info(self, event, is_chord):
        """Set event information (used by SwitchBoard)."""
        self.event = event
        self.is_chord = is_chord

    def count_active(self):
        """Return number of active switches."""
        return self._effective_switch_vector.count(1)

    # pylint: disable=invalid-name
    # n is always a valid name!
    def get_active_switch(self, n=1):
        """
        Return index of n'th active switch.

        Caution!!! One indexed!!! For the first active switch, n=1.
        """
        i = -1
        for _ in xrange(n):
            i = self._effective_switch_vector.index(1, i + 1)
        return i

    def state_diff(self):
        """
        Return index of difference between old and current raw switch states.

        Theoretically there should only ever be one permutation.
        """
        for i in range(len(self._raw_switch_state)):
            if self._raw_switch_state[i] != self._old_switch_state[i]:
                return i
        return None
