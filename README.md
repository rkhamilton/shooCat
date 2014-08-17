shooCat
=======

This project uses a PIR motion sensor to trigger a vibration motor and buzzer to scare cats off of my counter.

The heart of the project is an Arduino Micro socketed onto a custom PCB. The LowPower.h library from rocketscream is used to reduce power consumption. Nevertheless, the hardware choices made in this first version of the project result in poor batter life. The average power consumption is about 60 mA.

