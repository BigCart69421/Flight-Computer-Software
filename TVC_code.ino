#include<Servo.h>
#include<SD.h>
#include<SPI.h>
#include<Adafruit_BMP085.h>
#include<Adafruit_MPU6050.h>
#include<Adafruit_Sensor.h>
#include<Wire.h>
#include<Servo.h>

#define SD_CS 9
#define LED_R 21
#define LED_G 19
#define LED_B 20
#define BUZZER 18
#define PY1 10
#define PY2 11
#define yPin 1
#define xPin 2

Servo xServo;
Servo yServo;

Adafruit_MPU6050 imu;
Adafruit_BMP085 baro;

File flightData;

float galt;
float zalt;
float nalt;
float x;
float y;


void startupTone() {
  tone(BUZZER, 1000, 120);
  delay(140);
  tone(BUZZER, 1500, 120);
  delay(140);
  tone(BUZZER, 2000, 120);
  delay(140);
  tone(BUZZER, 2500, 120);
  delay(140);
  tone(BUZZER, 2000, 100);
  delay(120);
  tone(BUZZER, 1500, 100);
  delay(120);
  tone(BUZZER, 1000, 150);
  delay(170);
  noTone(BUZZER);
}

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(PY1, OUTPUT);
  pinMode(PY2, OUTPUT);

  startupTone();

  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, HIGH);
  digitalWrite(PY1, LOW);
  digitalWrite(PY2, LOW);

  if (!SD.begin(SD_CS)){
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R, LOW);
    tone(BUZZER, 440, 500);
  }
  digitalWrite(LED_G, LOW);
  if (!baro.begin()){
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R, LOW);
    tone(BUZZER, 440, 500);
  }
  digtalWrite(LED_G, LOW);
  digtalWrite(LED_B, LOW);
  galt = baro.readAltitude();

  xServo.attach(xPin);
  yServo.attach(yPin);

}

void loop() {
  File flightData = SD.open("flightData.txt", FILE_WRITE);
  nalt = baro.readAltitude();
  zalt = nalt - galt;
  flightData.println(zalt);
  x = a.acceleration.x;
  y = a.acceleration.y;
  xServo.write(x);
  yServo.write(y);
  flightData.print("X accel: ");
  flightData.println(x);
  flightData.print("Y accel: ");
  flightData.println(y);
}
