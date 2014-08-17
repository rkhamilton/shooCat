/*
 * shooCat.ino
 *
 * Created: 7/18/2014 1:32:23 PM
 * Author: Ryan Hamilton
 */ 

#include "LowPower.h"

//define pins
const int LED = 3;
const int SPEAKER = 1;
const int PIR = 0;
const int VIBRATE = 2;

boolean motionSeen = false; //is motion detected? do we need to scare a cat away?
boolean currentlyAlarming = false; // are we currently alarming

// the setup routine runs once when you press reset:
void setup() {
    int i;
    pinMode(LED, OUTPUT);
    pinMode(SPEAKER, OUTPUT);
    pinMode(PIR, INPUT);
    pinMode(VIBRATE, OUTPUT);

    // after power up wait 10 seconds before doing anything
    for (i = 0; i < 10; i++) {
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        delay(500);
    }
}

// the loop routine runs over and over again forever:
void loop() {
    // monitor for a cat to be found
    motionSeen = digitalRead(PIR);

    // if a motion was detected we need to run the vibration motor and buzzer
    if (motionSeen && !currentlyAlarming) startAlarm();
    if (currentlyAlarming && !motionSeen) stopAlarm();

    //at full power the system consumes 41 mA
    //the idle line below drops the system to 26 mA
    //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_OFF);
    //in powerdown mode the system consumes 9.2 mA
    if (!motionSeen && !currentlyAlarming) LowPower.powerDown(SLEEP_250MS, ADC_OFF, BOD_ON);
    
}

void startAlarm() {
    currentlyAlarming = true;
    digitalWrite(VIBRATE, HIGH);
    digitalWrite(LED, HIGH);
    digitalWrite(SPEAKER,HIGH);
}

void stopAlarm() {
    currentlyAlarming = false;
    digitalWrite(VIBRATE, LOW);
    digitalWrite(LED, LOW);
    digitalWrite(SPEAKER,LOW);
}