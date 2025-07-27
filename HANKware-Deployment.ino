#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <SD.h>

/***************************************************************
 HANKware v1.0 for MOSES R2 Flight Computer
 
 Deployment Firmware
 
 Also Available : Dattalogger (no Ejection)
 Piggy Board Support Coming Soon.
 ****************************************************************/


//Define outputs
int led = 5;
int buzzer = 6;
int pyro = 8;

float altitude;
float pressure;
float groundLevel;
float zeroedAltitude;
float temperature;
float prevAlt;
float deployAlt;

String altitudeStr = "";
String temperatureStr = "";
String pressureStr = "";
String deployAlt = "";

const int chipSelect = 10;

String dataString = "";

Adafruit_BMP085 bmp;

File dataFile = SD.open("hankware_flightdata.txt", FILE_WRITE);


void setup() {
  
  Serial.begin(9600);
  Serial.println("Beggining HANKware 1");
  tone(buzzer, 440, 500);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  SD.begin(chipSelect);
  groundLevel = bmp.readAltitude();

  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT); 
  pinMode(pyro, OUTPUT);

}

void landed() {
  dataFile.close();
  while(true) {
    tone(buzzer, 440, 500);
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    }
  
  }

void loop() {
  digitalWrite(led, LOW);
  altitude = bmp.readAltitude();
  zeroedAltitude = (altitude - groundLevel);
  pressure = bmp.readPressure();
  temperature = bmp.readTemperature();
  altitudeStr = zeroedAltitude;
  temperatureStr = temperature;
  pressureStr = pressure;
  dataString = "Altitude: " + altitudeStr + "Temperature: " + temperatureStr + "Pressure: " + pressureStr; 
  dataFile.println(dataString);
  Serial.println(dataString);
  if (prevAlt > zeroedAltitude) {
    digitalWrite(pyro, HIGH);
    delay(1000);
    digitalWrite(pyro, LOW);
    }
  if (zeroedAltitude < 5) {
    delay(5000);
    if (zeroedAltitude < 5){
      landed();
      }
    }
  prevalt = zeroedAltitude;
  digitalWrite(led, HIGH);
  delay(25);

}
