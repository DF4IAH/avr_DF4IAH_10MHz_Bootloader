# avr_DF4IAH_Bootloader

## GPS disciplined 10 MHz reference oscillator based on a (VC)TCXO
The project name for this reference oscillator is __10 MHz-Ref.-Osc. V2.x__

This device is attached at the USB bus and receives power and does communication over it.
An optional LCD module can be connected to the I2C compatible bus for stand-alone operation.

The author of it is Ulrich Habel (DF4IAH) with the idea having a low-cost and low-power device for a module to generate a 10 MHz signal at 3.3V TTL, that is adjusted to the GPS/Glonass satellite clock system. By this the local clock is kept in its boundaries to satisfy the long-term stability of the GPS/Glonass system. The negative aspect on it (I want to inform, also) with the use of a low power consuming VC-TCXO is, that the short-term variance is much higher than the variance of the devices using a temperature controlled oscillator like a rubidium lightwave controlled one.

### Contents of this repository
- Atmel ATmega 328P: master control and USB communications, bootloader for programming via USB - sources and binaries 

- CPLD: phase detection unit - source and binary

- Eagle drawings: oscillator and LCD - the schematics and boards for all variants of V2.x

### Additional information
The idea behind that project was to get a local oscillator in phase of the GPS clock system.
The device shall have a frequency and phase locked loop.
When the local frequency is trimmed to the reference GPS clock the phase locked loop gets in place of the frequency control.
Whenever the phase gets out of the secured boundaries, the system switches back to the frequency correction mode.
Due to its nature the device has to keep the local clock in the secured boundaries.
Only then the high quality stability of the GPS clock system can be delivered to the user.
For this reason when the local clock gets more out of balance and to one of its boundaries, a phase correction impulse is added to the local system to find the balance, again.
When running long this is fine and gived good results for the user.
On the other hand when the GPS receiption is bad, the almanac data poor or the temperature variance at the VC-TCXO increasing, that local error-signal has to be corrected sometimes whith sharp corrections.
So be warned to keep the device running in an air-locked container and a good GPS antenna position is a __must__ to get good results.

There are three different kinds of GPS units used by this project.
Each of them are utilizing the __MediaTek MT3333__ chipset, but each of the manufacturer is running its own configuration on it.
By this, some minor differences occur.
All of this GPS devices are able to track on GPS (western satellites) and Glonass/BeiDou (eastern satellites) signals.
Later at the works the author found out that the parallel receiption of GPS and Glonass can result to interrupted functionality.
With NMEA programming the GPS device receives the command to ignore the Glonass signals but not all of them do honour that and start up tracking of all received signals.
The only work-around for this is to use a more selective GPS-antenna that filters out the Glonass signals away from the single GPS frequency.

The author have his reference clocks running for month without any problems, the firmware is stable - __use on your own risk, only!__

If you find this project nice you are welcommed to spawn of.

Any new modifications may result to harm this behaviour.
Make your own decitions, be warned.

### Credits
I like to thank these following programmers and groups:

- __VUSB__ This code helped me to have USB communication on an ATmega, that does not support USB communication on its own.
All is done by interrupt software, many parts are assembly language based code.
Due to this nature all code in the bootloader as well as the firmware are very sensitive to changes on the code.
Only a very short interrupt time is allowed for the firmware avoiding the USB communication.
Find more about it: https://www.obdev.at/products/vusb/index.html

- __xxx__ The xxx company reserves a valid USB address to be used by the community.
I like to thank for this, also.
xxx

- __avrdude__ The base idea of the circuit as well as the bootloader code is reflected of the avrdude software and the AVR programmer, that is controlled by the avrdude software.

- __HF-Messzwerg__ When the author got in contact with the team of this device, he started to learn about SMD soldering and USB communication in relation with an ATmega.
Communication done is with the help of an USB/serial converter, there.

I wish you a nice expirience with this product.
Fell free and enjoy it.

Cheers

Ulrich Habel  (DF4IAH)
