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

RF24 radio(pin_radio_CE, pin_radio_CSN);
Adafruit_SSD1306 screen(128, 64, &Wire, pinButtonOledReset);

const byte addresses [] [6] = {"00001", "00002"};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin();

  pinMode(pinButton1, INPUT);
  pinMode(pinButton2, INPUT);
  pinMode(pinLedReceivedData, OUTPUT);
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);
  pinMode(pinSensorDTH22, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinDigitalSensorMq2, INPUT);

  attachInterrupt(digitalPinToInterrupt(pinButton1), readStateButton, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinButton2), readStateButton, FALLING);

  // Define the radio communication
  radio.begin();
  //radio.enableDynamicPayloads();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(125);
  //radio.setRetries(15, 15);
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setAutoAck(true);
  radio.startListening();

  screen.begin(SSD1306_SWITCHCAPVCC, 0x3C); //or 0x3C
  screen.setTextColor(WHITE);
  screen.print("Initialisation...");
  screen.display();
  delay(2000); // Pause for 2 seconds

}

void loop() {
  // put your main code here, to run repeatedly:
screen.clearDisplay(); //for Clearing the display

  screen.setTextSize(2);
  screen.setCursor(screen.width() / 6, 0);

  screen.println("INDOOR");
  //screen.drawBitmap(0, (screen.height() - sizeBitmap), bitmap, sizeBitmap, sizeBitmap, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)

  screen.setTextSize(2);
  screen.setCursor(screen.width() / 2, screen.height() / 2);

readDHT22 = DHT.read22(pinSensorDTH22); // Reads the data from the sensor
screen.clearDisplay();
temperatureIndoor = DHT.temperature; // Gets the values of the temperature
  inTemp = String(temperatureIndoor) + char(247) + "C";

   screen.print(inTemp);
  screen.display();
screen.clearDisplay();

  humidityIndoor = DHT.humidity; // Gets the values of the humidity
  inHum = String(humidityIndoor) + char(37);

  screen.print(inHum);
  screen.display();

 
}