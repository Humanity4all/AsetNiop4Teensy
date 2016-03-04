import binascii
import itertools

import configcompiler

# Create a value for every combination of two switches.
# In this case, just the numbers 1..256.
values = [
    switch1 * configcompiler.N_SWITCHES + switch2
    for switch1 in range(0,8)
    for switch2 in range(0,8)
]

# Create a buffer of front matter + values
buf = configcompiler.populate_buffer(
    configcompiler.OFFSET,
    configcompiler.N_SWITCHES,
    values
)

# Print the hex of that buffer to output
print(binascii.hexlify(buf))

# Print the output to file.
with open('test.bin', 'wb') as f:
    f.write(buf)
