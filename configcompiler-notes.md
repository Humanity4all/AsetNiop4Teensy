# Config compiler for Asetniop key maps

## Intermediate data structures

    yaml file
    ... --[ yaml.safe_load(...) ]-->  raw yaml reading result
    ... --[ clean_yaml(...) ]------>  validated and cleaned yaml structure
    ... --[ Layer(...) ]----------->  a Layer object with a __getitem__ method
                                      that allows accessing any switch pair and
                                      getting a valid result
    ... --[ layer1[2, 1] ]--------->  the correct bytes value for switch pair 2, 1
    ... --[ list comprehension ]--->  a layer's bytes values in order
    ... --[ populate_buffer ]------>  a buffer with the byte values written at
                                      the correct locations

### yaml file

Top level is a dict with one entry for each layer. Layers should be named
`layer 1`, `layer 2`, ..., `layer n`, without gaps. There will also be an entry
called e.g. `config` containing the global configuration.

Inside a layer, each entry is a dict 'switch pair: key name'

* the switch pair is a space-separated pair of switch numbers
* the key name is either
    * a string representing a key name, e.g. `<Up>` or `a`,  or
    * a one-digit integer, convert it to string to get the key name.

Within a layer, any switch combination can be undefined. If a switch
combination is missing but its complement is defined, it is assumed to
have the same value as its complement.

A switch combination can be explicitly undefined: write `undefined`. This means
it is undefined even if its complement is present.


### validated and cleaned yaml

* list of layers
* layer is a dict of (switch pair) -> (key name) entries
* pairs may still be missing.
* handles the fact that yaml interprets a bare y or n as bools
* translates 'undefined' to None


### Layer object

Has a `__getitem__()` method that accepts a `switch1, switch2` tuple, looks up
that tuple in the yaml object (falling back on the complement definition if
needed), and returns the bytes value of that pair's keycode


### Buffer values list

sequence of bytes representing key codes, one byte for
each switch combination we expect in a layer.
e.g. '\x00', '\x01'
One byte for each.


## Syntax of the config file

### How to refer to individual switches?

Options: Zero-based indexing, or one-based indexing, or by their standard
letters.

    0 1 2 3  4 5 6 7 (zero-based)
    1 2 3 4  5 6 7 8 (one-based)
    a s e t  n i o p (letter-based)

If we can only choose one, I'd say one-based indexing, because:

* It's consistent with how people count.
* The association with letters is a help for the normal typing layer, but a
  hindrance as soon as you're implementing any special layer.

But perhaps make it possible to declare switch names for a layer?


### How to write a switch combination -> result entry?

Ini-style:

    1 1 = a
    2 2 = s
    1 2 = w

Ini-style (nested):

    not sensibly possible

yaml-style (flat):

    1: a
    1 2: w

    2: s
    2 3: x

yaml-style (nested):

    1:
      1: a
      2: w

    2:
      2: s
    

### How to refer to layers?

Just number them:

    # This is an alphabetical layer
    [layer 1]
    1 2: 8
    
    # This is the arrow key layer
    [layer 2]
    1 2: <Up>


## Nice to have stuff

* allow 2 forms of binary->config decompilation:

  1. Simplified, e.g. if '1 2' == '2 1', then omit '2 1'
  2. Verbose.
