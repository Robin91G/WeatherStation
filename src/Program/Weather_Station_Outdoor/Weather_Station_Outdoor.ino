#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "dht.h"
#include <BH1750.h>
#include "Adafruit_VEML6070.h"
#include <SFE_BMP180.h>
#include <MQ135.h>

#define pinSensorDTH22 8
#define pin_radio_CE 9
#define pin_radio_CSN 10

#define pinGasSensor A0
#define pinGirouette A1
#define pinRainSensor A2

RF24 radio(pin_radio_CE, pin_radio_CSN);
dht DHT;
BH1750 lightMeter(0x23);
Adafruit_VEML6070 uvIndex = Adafruit_VEML6070();
SFE_BMP180 pressure;
MQ135 mq135_sensor(pinGasSensor);

const byte addresses [] [6] = {"00001", "00002"};

//strure of data
struct Weather_Station {
  int temperatureOutdoor;
  int humidityOutdoor;
  int rainIntensity;
  int intensityLightOutdoor;
  int uvIndexOutdoor;
  int pressureAtmoOutdoor;
  int altitudeOutdoor;
  int airQualityOutdoor;
  int windDirectionOutdoor;
  int windSpeedOutdoor;
};
Weather_Station data; //Create a variable with the above structure

int readDHT22, temperatureOutdoor, humidityOutdoor, rainIntensity, intensityLightOutdoor, uvIndexOutdoor, airQualityOutdoor, windDirectionOutdoor, windSpeedOutdoor;
char statusBmp180;
double outTemp, outPressure, outAltitude;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin();

  // Define the radio communication
  radio.begin();
  //radio.enableDynamicPayloads();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(125);
  //radio.setRetries(15, 15);
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setAutoAck(true);
  radio.stopListening();

  softSerial.begin(115200);

  lightMeter.begin();
  uvIndex.begin(VEML6070_1_T);
}

void loop() {
  // put your main code here, to run repeatedly:

}