"""Event class, to carry around information on switch states."""

from collections import namedtuple

EventData = namedtuple('EventData', [
    'old_switch_state',
    'new_switch_state'])


class Event(EventData):

    """
    Event to carry around switch state info.

    We went for different event types throughout the code base,
    switch events, protokey events, switch vectors, event strings,
    all kinds of information flying around. And in the end, it turns
    out we need all the info that we filtered out in the beginning
    anyway. So why not make a single event with the necessary info?
    """

    def __init__(self, old_switch_state, new_switch_state):
        """Set (effective) switch vector."""
        EventData.__init__(old_switch_state, new_switch_state)
        # On a rising edge (switch release), the active switch
        # is a 1. On a falling edge (switch press), the active switch
        # is also a 1.
        self._effective_switch_vector = None

        # Rising or falling edge
        self.edge = None

        self._update_effectite_switch_vector()

    def _update_effectite_switch_vector(self):
        """Translate raw switch states to effective switch vector."""
        diff = self.state_diff()
        self._effective_switch_vector = self.new_switch_state[:]
        if diff is not None:
            if self._effective_switch_vector[diff] == 0:
                self.edge = 'falling'
            else:
                self.edge = 'rising'
            self._effective_switch_vector[diff] = 1

    def new_event(self, new_switch_state):
        """Update (eftective) switch vector. (used by PinInterface)."""
        return Event(self.new_switch_state, new_switch_state)

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
        for i in range(len(self.new_switch_state)):
            if self.new_switch_state[i] != self.old_switch_state[i]:
                return i
        return None
