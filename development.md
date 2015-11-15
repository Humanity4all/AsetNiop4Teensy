## Development

### ToDo

* decide on a way to pass around swich states
** pass around a pointer to a SwitchVector - and keep updating it? But what about old - new info then? Have a switchvector remember that until it is used up by the translation service?
** create new SwitchVectors for every mutation - but what about modifier persistence? Split that off into a separate class/struct? Will this result in malloc use outside of setup()?
* define switchboard state machine
* create the translation service
* phase out typedefs.h and create a main.h
* figure out what design pattern to use for software-hardware interface (read: where do we poll the physical switches & store the Bounce objects?)
* implement modifiers
* write unit tests -> figure out how unit testing works with embedded cpp (this really shouldn't be this low on the list...)
* implement layout layers in translation service (e.g. alphabetic, numerical)
* expand on the design.md document - include other parts of the process (translation service, hardware-software interface, etc.) (maybe this should be first on the list...)

