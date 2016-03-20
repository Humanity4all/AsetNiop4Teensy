import itertools
import struct

import yaml


OFFSET = 100
N_SWITCHES = 8


def clean_yaml(yaml):
    """
    Take a yaml.safe_load result, and clean its values

    * because yaml interprets `n` as `false`, convert all `false` to `'n'`
    * convert numbers to their string representation
    """
    raise NotImplementedError


class Layer(object):

    def __init__(self, layer):
        """`layer` is a dict of switch1, switch2: key name pairs"""
        raise NotImplementedError

    def __getitem__(self, index):
        """Return the keycode corresponding to a switch pair"""
        raise NotImplementedError


def populate_buffer(values, offset=OFFSET, n_switches=N_SWITCHES):
    """Create a buffer with layer values written in it at a certain offset."""

    error_message = "Expected {n}^2 = {n2} values, got {actual_n}".format(
        n=n_switches, n2=n_switches**2, actual_n=len(values))
    assert len(values) == n_switches**2, error_message

    # The values will be packed into a little-endian struct of n*n bytes
    s = struct.Struct('<' + 'b ' * n_switches**2)
    # The actual bytearray consists of some front matter + the values struct
    buf = bytearray(s.size + offset)
    # Write the values struct into the right end of the bytearray
    s.pack_into(buf, offset, *values)

    return buf


def buffer_from_data(data, offset, n_switches):
    """
    Take a dict with items like 'layer 1', and return a buffer with that can be
    used as an asetniop keymap

    * an offset at the start containing setup data
    * a layer section containing the data
    """

    layers = list()
    for i in itertools.count():
        if 'layer ' + str(i) in yaml_data_clean:
            layers.append(Layer(yaml_data_clean['layer ' + str(i)]))
        else:
            break

    if 2 <= len(layers):
        raise NotImplementedError

    for layer in layers:
        values = [layer[s1, s2] for s1, s2 in switch_pairs(n_switches)]
        buf = populate_buffer(values, offset, n_switches)

    return buf


def main(yaml_file, output_file, offset=OFFSET, n_switches=N_SWITCHES):
    """
    Read a yaml file, clean it, process it, and write the result to file.
    """

    # FIXME: if safe_load gives an error, warn that
    #
    #     ! ? = , - ' " ` [ ] { } * & ~ # | > : @
    #
    # all need quoting. Perhaps say all non-alphanum chars need quoting?
    yaml_data = yaml.safe_load(yaml_file)

    yaml_data_clean = clean_yaml(yaml_data)

    buf = buffer_from_data(yaml_data_clean, offset, n_switches)

    with open(output_file, 'wb') as f:
        f.write(buf)
