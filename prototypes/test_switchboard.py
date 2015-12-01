from nose.tools import assert_items_equal, assert_is_instance
# sorry, I know this is messy, but so much easier!
from switchboard import *
# from switchboard import SwitchBoard, SwitchEvent, ProtoKeyEvent


def test_switchboard():
    switchboard = SwitchBoard()
    observed = switchboard.process_switch_event(
        SwitchEvent('down', [0, 1, 0]))
    expected = [ProtoKeyEvent(
        switch_vector=[0, 1, 0],
        event='down',
        is_chord=False)]
    assert_items_equal(observed, expected)
    assert_is_instance(switchboard._state, OneSwitch)

    # Now press a second switch

    observed = switchboard.process_switch_event(
        SwitchEvent('down', [1, 1, 0]))
    expected = [ProtoKeyEvent('down', [1, 1, 0], True)]
    assert_items_equal(observed, expected)
    assert_is_instance(switchboard._state, TwoSwitch)

    # Release a switch

    observed = switchboard.process_switch_event(
        SwitchEvent('up', [1, 1, 0]))
    expected = [ProtoKeyEvent('up', [1, 1, 0], True)]
    assert_items_equal(observed, expected)
    assert_is_instance(switchboard._state, OneSwitchUsed)

    # Drop back to idle

    observed = switchboard.process_switch_event(
        SwitchEvent('up', [1, 0, 0]))
    expected = [ProtoKeyEvent('up', [1, 0, 0], False)]
    assert_items_equal(observed, expected)
    assert_is_instance(switchboard._state, Idle)

    # See if it behaves correctle after press press release press
    switchboard.process_switch_event(
        SwitchEvent('down', [1, 0, 0]))
    switchboard.process_switch_event(
        SwitchEvent('down', [1, 1, 0]))
    switchboard.process_switch_event(
        SwitchEvent('up', [1, 1, 0]))
    observed = switchboard.process_switch_event(
        SwitchEvent('down', [1, 0, 1]))
    expected = [ProtoKeyEvent('down', [1, 0, 1], True)]
    assert_items_equal(observed, expected)
    assert_is_instance(switchboard._state, TwoSwitch)

    # Now test ManySwitches!
    observed = switchboard.process_switch_event(
        SwitchEvent('down', [1, 1, 1]))
    expected = [
        ProtoKeyEvent('down', [1, 1, 1], False),
        ProtoKeyEvent('reset', [1, 1, 1], True)]
    assert_items_equal(observed, expected)
    assert_is_instance(switchboard._state, ManySwitch)

    observed = switchboard.process_switch_event(
        SwitchEvent('up', [1, 1, 1]))
    expected = [ProtoKeyEvent('up', [1, 1, 1], False)]
    assert_items_equal(observed, expected)
    assert_is_instance(switchboard._state, ManySwitch)

    switchboard.process_switch_event(
        SwitchEvent('up', [1, 1, 0]))
    assert_is_instance(switchboard._state, ManySwitch)

    switchboard.process_switch_event(
        SwitchEvent('up', [1, 0, 0]))
    assert_is_instance(switchboard._state, Idle)

    # Test pres release

    switchboard.process_switch_event(
        SwitchEvent('down', [0, 0, 1]))
    observed = switchboard.process_switch_event(
        SwitchEvent('up', [0, 0, 1]))
    expected = [
        ProtoKeyEvent('down', [0, 0, 1], True),
        ProtoKeyEvent('up', [0, 0, 1], True)]
    assert_items_equal(observed, expected)
    assert_is_instance(switchboard._state, Idle)
