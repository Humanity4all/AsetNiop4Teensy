"""Test Event class."""
# pylint: disable=no-name-in-module, relative-import, protected-access
from nose.tools import assert_equals, assert_items_equal

from event import Event


def test_event():
    """Test Event class."""
    # Test __init__
    switch_state = [0, 0, 0]
    event = Event(switch_state)
    assert_equals(event._raw_switch_state, switch_state)
    assert_items_equal(event._effective_switch_vector, switch_state)

    # Test new_switch_state and state_diff
    switch_state = [1, 0, 0]
    event.new_switch_state(switch_state)
    assert_items_equal(event._effective_switch_vector, switch_state)
    assert_equals(event.state_diff(), 0)

    # Test _get_effective_switch_vector and state_diff
    switch_state = [0, 0, 0]
    event.new_switch_state(switch_state)
    assert_items_equal(event._effective_switch_vector, [1, 0, 0])
    assert_equals(event.state_diff(), 0)

    # Test count_active and get_active_switch
    switch_state = [1, 0, 0]
    event.new_switch_state(switch_state)
    switch_state = [1, 0, 1]
    event.new_switch_state(switch_state)
    assert_equals(event.count_active(), 2)
    first = event.get_active_switch(1)
    assert_equals(first, 0)
    second = event.get_active_switch(2)
    assert_equals(second, 2)
