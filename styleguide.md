# Style Guide
This is just a proposal so far

## Naming conventions
* functions, methods and variables: lowercase_with_underscores
* enums, structs and typedefs: _t suffix
* enum members, #define members: ALLCAPS_WITH_UNDERSCORES
* classes: CamelCase

We don't use dromedaryCase here at all. Only, I can't think of a good place
to use them without breaking existing conventions in the libraries we use.

## Whitespace
* indent with 4 spaces - except in namespaces, which are not indented
* single space around operators
* single newline between function definitions
* no spaces directly inside parenteses, single space outside of them
* no trailing whitespace

## Nesting
* opening accolade on same line as function definition / control statement
* closing accolade on its own line except in case of an else statement

## Comments
* copyright string at top of each file: Copyright 2015 Stichting Humanity4all
* comment goes before code, not after it
* strive to avoid inline comments
* prefer /* */ style over //

## Other formatting
* line length of 80
* use a header guard in header files -> SRC_FILENAME_H_ if file is in the src directory.

## Design decisions
* separate hardware interface and application logic as much as possible
* write unit tests for your code where possible
* no memory allocation outside of the setup function

