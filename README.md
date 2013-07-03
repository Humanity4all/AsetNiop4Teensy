AsetNiop4Teensy
===============

Teensyduino usb microcontroller driver for low actuation AsetNiop keyboard.

AsetNiop is a keyboard layout that only uses around 15 keys, 20 in this configuration (counting mouse buttons). This is possible by chord typin (forming characters by pressing multiple keys at once).

I have a connective tissue disorder that severely limits my ability to type. As a programmer, you can see why that's a problem. I've tried several 'traditional' solutions. Speech recognition, on-screen keyboards with head movement tracking, low actuation force keyboards, even a laser keyboard. But none of those enabled me to input text precise and fast enough to make programming possible.

Then I found asetniop (asetniop.com). At the time it was still in development but the idea seemed so promising that I contacted the developer and started implementing it in an os x keyboard remapper (KeyRemap4MacBook). With asetniop and a low actuation force keyboard I was able to type better and faster than I had ever been able to.

Unfortunately my illness is progressive, and as I deteriorated I realized I would need even lower actuation force keyswitches. I decided to build my own keyboard before I wouldn't be able to any more. Thus asetniop4teensy was born.

The hardware
===============

The cherry keyswitches that are most common in high-end keyboards require too much force, so I decided to go with the saia-burgess g3m1tipul microswitches (I got the idea from mykeyboard.co.uk). This type only requires 0.15 N for a keypress. For keycaps I used simple generic square microswitch keycaps. Not the cherry switch caps that Tim Tyler uses. The usb microcontroller I chose is the teensy 3.0 (with pins).

Because of the low number of keys and the type of terminals used (t1 uses 2 faston 6.3 x 0.8 mm male pins) the keyboard will be solderless (with use of a breadboard). This makes assembly a lot easier and less error prone.

As for the physical layout, I am going for a datahand-like device, with the exception that I'll use 2 keys per finger and they won't be mounted under the fingers but in front and behind (bending and flexing is easier for me). I also want to add a trackball under my right thumb so I won't have to move my hands with switching.

The trackball is pretty easy. Mount a regular mouse upside down with a track ball (roller deodorant ball or something a bit more classy) above it. I dislike the idea of having two usb cables for something that's actually one device. I'm looking into connecting the mouse directly to teensy or implemening an optical mouse sensor into the circuit.

I'm not exactly sure how to mount the keys yet.

The case is going to be transparent plastic, such a cool piece of work has to be shown off :)

The software
===============

I decided to go with teensyduino because writing a keyboard driver would be so much easier that way. I had no previous experience with C and I did not want to complicate things more than necessary.

I've wired the keyboard to be able to handle n simultaneous keys. Teensy only sends 6 regular keys and modifiers at one time, but that doesn't really matter as most of the chording is handled by teensy itself.
