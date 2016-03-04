import struct


OFFSET = 100
N_SWITCHES = 8


def populate_buffer(values, offset=OFFSET, n_switches=N_SWITCHES):
    error_message = "Expected {n}^2 = {n2} values, got {actual_n}".format(
        n=n_switches, n2=n_switches**2, actual_n=len(values))
    assert len(values) == n_switches**2, error_message
    # The values will be packed into a little-endian struct of n*n bytes
    s = struct.Struct('<' + 'b ' * n_switches * n_switches)
    # The actual bytearray consists of some front matter + the values struct
    buf = bytearray(s.size + OFFSET)
    # Write the values struct into the right end of the bytearray
    s.pack_into(buf, offset, *values)
    return buf
