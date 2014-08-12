/*
 * shooCat.ino
 *
 * Created: 7/18/2014 1:32:23 PM
 * Author: Ryan Hamilton
 */ 

#include "pitches.h"
#include "LowPower.h"

//#define DEBUG

//define pins
const int LED = 12;
const int STOCK_LED = 13;
const int SPEAKER = 5;
const int PIR1 = 2;
const int PIR2 = 7;
const int VIBRATE = 6;

boolean motionSeen = false; //is motion detected? do we need to scare a cat away?
boolean currentlyAlarming = false; // are we currently alarming

// the setup routine runs once when you press reset:
void setup() {
    int i;
    pinMode(LED, OUTPUT);
    pinMode(STOCK_LED, OUTPUT);
    pinMode(SPEAKER, OUTPUT);
    pinMode(PIR1, INPUT);
    pinMode(PIR2, INPUT);
    pinMode(VIBRATE, OUTPUT);

#ifdef DEBUG
    Serial.begin(115200);
    Serial.println("Setup loop starting");
#endif    
    // after power up wait 10 seconds before doing anything
    for (i = 0; i < 10; i++) {
        digitalWrite(LED, HIGH);
        digitalWrite(STOCK_LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        digitalWrite(STOCK_LED, LOW);
        delay(500);
    }

#ifdef DEBUG
    Serial.println("Setup loop complete");
#endif
}

// the loop routine runs over and over again forever:
void loop() {
    // monitor for a cat to be found
    motionSeen = digitalRead(PIR1) || digitalRead(PIR2);
    #ifdef DEBUG
    Serial.print("PIR1: ");
    Serial.print(digitalRead(PIR1));
    Serial.print(" PIR2: ");
    Serial.print(digitalRead(PIR2));
    Serial.print(" motionSeen: ");
    Serial.println(motionSeen);
    #endif

    // if a motion was detected we need to run the vibration motor and buzzer
    if (motionSeen && !currentlyAlarming) startAlarm();
    if (currentlyAlarming && !motionSeen) stopAlarm();


    //at full power the system consumes 41 mA
    //the idle line below drops the system to 26 mA
    //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_OFF);
    //in powerdown mode the system consumes 9.2 mA
    if (!motionSeen && !currentlyAlarming) LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_ON);
    
}

void startAlarm() {

#ifdef DEBUG
    Serial.println("start alarm");
#endif
    currentlyAlarming = true;
    digitalWrite(VIBRATE, HIGH);
    digitalWrite(LED, HIGH);
    digitalWrite(STOCK_LED, HIGH);
    tone(SPEAKER, NOTE_A4);
}

void stopAlarm() {

#ifdef DEBUG
    Serial.println("stop alarm");
#endif
    currentlyAlarming = false;
    digitalWrite(VIBRATE, LOW);
    digitalWrite(LED, LOW);
    digitalWrite(STOCK_LED, LOW);
    noTone(SPEAKER);
}