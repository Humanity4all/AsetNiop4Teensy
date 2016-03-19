import configcompiler as cc

class TestPopulateBuffer():

    def test_the_happy_path(self):
        result = cc.populate_buffer([1, 2, 3, 4], offset=2, n_switches=2)
        expected = '\x00\x00\x01\x02\x03\x04'
        assert result == expected
