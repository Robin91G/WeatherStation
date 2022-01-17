#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RTClib.h>
#include "dht.h"
#include <MQ2.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

//Definition Digital Pin
#define pinButton1 2
#define pinButton2 3
#define pinLedReceivedData 4
#define pinLedRed 5
#define pinLedGreen 6
#define pin_radio_CE 7
#define pin_radio_CSN 8
#define pinSensorDTH22 9
#define pinBuzzer 10
#define pinButtonOledReset 14 //A0
#define pinDigitalSensorMq2  15 //A1

//Definition Analog Pin
#define pinSensorMq2 A2


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(pinButton1, INPUT);
  pinMode(pinButton2, INPUT);
  pinMode(pinLedReceivedData, OUTPUT);
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);
  pinMode(pinSensorDTH22, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinDigitalSensorMq2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}