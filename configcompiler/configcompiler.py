import struct
import binascii

OFFSET = 100
N_SWITCHES = 8


def populate_buffer(offset, n_switches, values):
    # The values will be packed into a little-endian struct of n*n bytes
    s = struct.Struct('<' + 'b ' * n_switches * n_switches)
    # The actual bytearray consists of some front matter + the values struct
    buf = bytearray(s.size + OFFSET)
    # Write the values struct into the right end of the bytearray
    s.pack_into(buf, offset, *values)
    return buf

# Create a value for every switch combination. In this case, just
# the numbers 1..256
values = range(N_SWITCHES**2)

# Create a buffer of front matter + values
buf = populate_buffer(OFFSET, N_SWITCHES, values)

# Print the hex of that buffer to output
print(binascii.hexlify(buf))

# TODO: write the result to a file, and inspect the file with hexedit.
# http://linux.byexamples.com/archives/478/python-writing-binary-file/
