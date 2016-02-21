import struct
import binascii

OFFSET = 100
N_SWITCHES = 8


def populate_buffer(offset, n_switches, values):
    s = struct.Struct('<' + 'b ' * n_switches * n_switches)
    buf = bytearray(s.size + OFFSET)
    s.pack_into(buf, offset, *values)
    return buf

values = range(N_SWITCHES**2)
buf = populate_buffer(OFFSET, N_SWITCHES, values)

print(binascii.hexlify(buf))

# TODO: write the result to a file, and inspect the file with hexedit.
# http://linux.byexamples.com/archives/478/python-writing-binary-file/
