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
  initBMP180()
}

void loop() {
  // put your main code here, to run repeatedly:
  setTemperatureOutdoor();
  setHumidityOutdoor();
  setPressureAtmoOutdoor();

for (int i = 0; i <= 3; i++) {           // Send the data 3 times
    radio.write(&data, sizeof(Weather_Station));
    delay(50);
  }
}

void initBMP180() {
  if (pressure.begin()) { //If initialization was successful, continue
    Serial.println("BMP180 init success");
  } else {
    //Else, stop code forever
    Serial.println("BMP180 init fail");
  }
}

void readSensorDTH22Outdoor() {
  readDHT22 = DHT.read22(pinSensorDTH22); // Reads the data from the sensor
}

void setTemperatureOutdoor() {
  readSensorDTH22Outdoor();

  temperatureOutdoor = DHT.temperature;
  data.temperatureOutdoor = temperatureOutdoor;// Gets the values of the temperature
}

void setHumidityOutdoor() {
  readSensorDTH22Outdoor();

  humidityOutdoor = DHT.humidity;
  data.humidityOutdoor = humidityOutdoor; // Gets the values of the humidity
}


void setPressureAtmoOutdoor() {

  statusBmp180 = pressure.startTemperature();
  delay(statusBmp180);
  statusBmp180 = pressure.getTemperature(outTemp);

  statusBmp180 = pressure.startPressure(3);
  delay(statusBmp180);
  statusBmp180 = pressure.getPressure(outPressure, outTemp);

  data.pressureAtmoOutdoor = int(outPressure);

  /*double p0 = pressure.sealevel(outPressure, seaAltitude);

    Serial.print("relative (sea-level) pressure: ");
    Serial.println(p0);

    outAltitude = pressure.altitude(outPressure, p0);
    Serial.print(" Altitude : " ) ;
    Serial.print(outAltitude);
    Serial.println( " Mètres ");*/
}
