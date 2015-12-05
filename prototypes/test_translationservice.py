"""Test TranslationService prototype."""
# pylint: disable=no-name-in-module, wildcard-import, relative-import
# pylint: disable=unused-wildcard-import, protected-access
from nose.tools import assert_equals, assert_is_instance, assert_is

from translationservice import *
from switchboard import ProtoKeyEvent


def test_translationservice():
    """Test TranslationService prototype."""
    machine = TranslationService()
    assert_is_instance(machine._state, ExampleLayer)

    # Test ExampleLayer with chord
    event = ProtoKeyEvent(event='down', switch_vector=[1, 0, 1], is_chord=True)
    expected_char = 'c'
    expected_event = 'down'

    observed_char, observed_event = machine.process_protokey_event(event)

    assert_equals(expected_char, observed_char)
    assert_equals(expected_event, observed_event)

    # Test ExampleLayer with single switch
    event = ProtoKeyEvent(event='up', switch_vector=[0, 1, 0], is_chord=True)
    expected_char = 'd'
    expected_event = 'up'

    observed_char, observed_event = machine.process_protokey_event(event)

    assert_equals(expected_char, observed_char)
    assert_equals(expected_event, observed_event)

    # Do a reset
    event = ProtoKeyEvent(
        event='reset',
        switch_vector=[1, 1, 1],
        is_chord=True)
    expected_char = 'EmptyKey'
    expected_event = 'reset'

    observed_char, observed_event = machine.process_protokey_event(event)

    assert_equals(expected_char, observed_char)
    assert_equals(expected_event, observed_event)

    # This should be ignored - accumulating!
    event = ProtoKeyEvent(
        event='down',
        switch_vector=[1, 0, 0],
        is_chord=False)
    observed = machine.process_protokey_event(event)
    assert_is(observed, None)

    # Switch layer (right now there's no key for that!)
    machine._state = ExampleNonChordedLayer()

    event = ProtoKeyEvent(
        event='down',
        switch_vector=[0, 0, 1],
        is_chord=False)
    expected_char = 'c'
    expected_event = 'down'

    observed_char, observed_event = machine.process_protokey_event(event)

    assert_equals(expected_char, observed_char)
    assert_equals(expected_event, observed_event)
