from StringIO import StringIO
import textwrap

import configcompiler as cc
import pytest


class TestPopulateBuffer():

    def test_the_happy_path(self):
        result = cc.populate_buffer([1, 2, 3, 4], offset=2, n_switches=2)
        expected = '\x00\x00\x01\x02\x03\x04'
        assert result == expected


class Test_read_yaml():

    def test_it_makes_a_friendly_exit_on_bad_yaml(self, capsys):

        yaml_stream = StringIO(textwrap.dedent('''\
            layer 1:
              1: a
              5: [
              6: b
            '''))

        with pytest.raises(SystemExit) as exc_info:
            cc.read_yaml(yaml_stream)

        assert exc_info.value.code == 1

        out, err = capsys.readouterr()
        assert err == ('Error while loading config file. Did you forget '
                       'to quote a non-alphanumeric character?')

    def test_the_happy_path(self):
        yaml_stream = StringIO(textwrap.dedent('''\
            layer 1:
              1: a
              2: b
              3: '['
              4: e
            '''))
        result = cc.read_yaml(yaml_stream)
        assert result == {
            'layer 1': {1: 'a', 2: 'b', 3: '[', 4: 'e'}
        }
