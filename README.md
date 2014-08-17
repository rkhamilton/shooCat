shooCat
=======

This project uses a PIR motion sensor to trigger a vibration motor and buzzer to scare cats off of my counter.
![shooCat](/images/shooCat2-assembled.jpg)

This second revision of the shooCat project uses an ATtiny85 microcontroller chip on a custom PCB. The typical power draw during non-alarming conditions is about 50 uA at 4.5 V (uses three AAA batteries with no voltage regulator). I estimate it should last for over 5 year on one set of batteries. That's a nice improvement over version 1, which would run for 12 hours on a 9 volt battery!

#Acknowledgements

* This project uses the [Rocketscream LowPower.h library](http://www.rocketscream.com/blog/2011/07/04/lightweight-low-power-arduino-library/).
