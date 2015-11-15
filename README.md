AsetNiop4Teensy
===============

Teensyduino usb microcontroller driver for low actuation AsetNiop keyboard.

AsetNiop is a keyboard layout that only uses around 15 keys, 10 in this
configuration (counting mouse buttons). This is possible by chord typing
(forming characters by pressing multiple keys at once).

I have a connective tissue disorder that severely limits my ability to type. As
a programmer, you can see why that's a problem. I've tried several
'traditional' solutions. Speech recognition, on-screen keyboards with head
movement tracking, low actuation force keyboards, even a laser keyboard. But
none of those enabled me to input text accurately and fast enough to make
programming possible.

Then I found asetniop (asetniop.com). At the time it was still in development
but the idea seemed so promising that I contacted the developer and started
implementing it in an os x keyboard remapper (KeyRemap4MacBook). With asetniop
and a low actuation force keyboard I was able to type better and faster than I
had ever been able to.

Unfortunately my illness is progressive, and as I deteriorated I realized I
would need even lower actuation force keyswitches. I decided to build my own
keyboard before I wouldn't be able to any more. Thus asetniop4teensy was born.

The hardware
===============

The cherry keyswitches that are most common in high-end keyboards require too
much force, so I decided to go with low-actuation force microswitches. This
type only requires 0.15 N for a keypress. Combine this with a teensy 3.0 
microcontroller, and a boat load of polymorph, and you've got a keyboard.
Well, sort of. More of an input device. Or just a mound of plastic, depending
on how you look at it.

As for the physical layout, I am going for a datahand-like device, with the
exception that I'll use 1 key per finger (2 under the left thumb), with the
hands tilted upright and completely supported. I also want to add a trackball
under my right thumb so I won't have to move my hands between keyboard and
mouse all the time.

The software
===============

We use platformio to compile and get the code onto the microprocessor, because
that just works so much easier. Especially coupled with a version control
system like git.

When all's said and done, the input device will seem like a normal keyboard
to the computer. Any operating system will be able to recognize it, as long
as arduino is supported (that's the case on most operating systems).

Current state
===============

We've started from scratch for the second time, and hopefully the last. A lot
has changed in the physical design of the keyboard, and we have waited for a
semi-usable prototype before further developing the codebase. Now is that time.
