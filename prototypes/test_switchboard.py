import pytest
import ipdb

from switchboard import SwitchBoard, SwitchEvent, ProtoKeyEvent

def test_switchboard():
    switchboard = SwitchBoard()
    observed = switchboard.process_switch_event(
        SwitchEvent('down', [0, 1, 0]))
    expected = ProtoKeyEvent(
        switch_vector=[0, 1, 0],
        event='down',
        is_chord=False)
    ipdb.set_trace()
    assert observed = expected
