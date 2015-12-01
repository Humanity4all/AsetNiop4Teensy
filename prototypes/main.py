"""Prototype of main execution loop."""
# pylint: disable=relative-import
from pininterface import PinInterface
from switchboard import SwitchBoard
from translationservice import TranslationService


# This would happen in the setup() function
# pylint: disable=invalid-name
pin_interface = PinInterface()
switch_board = SwitchBoard()
key_event_queue = []
translation_service = TranslationService()


def loop():
    """Executed continuously on the microcontroller."""
    switch_event_queue = pin_interface.get_switch_event()
    for switch_event in switch_event_queue:
        key_event_queue.append(switch_board.process_switch_event(switch_event))
    for key_event in key_event_queue:
        translation_service.process_key_event(key_event)
