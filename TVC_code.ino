#include<"Adafruit_MPU6050.h">
#include<"Adafruit_BME280.h">
#include<"Servo.h">
#include<"Wire.h">
#include<"Adafruit_Sensor.h">

Adafruit_BME280 baro;
Adafruit_MPU6050 mpu;

unsigned long lastMicros = 0;

float output = 0;
float x = 0;
float y = 0;
float dt = 0;

float xTune;
float yTune;

int yServoPin = 17;
int xServoPin = 16;

Servo yServo;
Servo xServo;

float PI(float Kp, float Ki, float dt, float measured){
    static float P = 0;
    static float I = 0;
    float error = 0 - measured;
    P = error * Kp;
    I += error * dt * Ki;
    return P + I;
}

void setup(){
    Serial.begin(9600);
    if(!mpu.begin()){
        Serial.println("Gyro init failed");
    }
    Serial.println("Gyro init success");
    if(!baro.begin()){
        Serial.println("Baro init init");
    }
    Serial.println("Baro init success");
    lastMicros = micros();
    yServo.attach(yServoPin);
    xServo.attach(xServoPin);
}

void loop(){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    unsigned long now = micros();
    dt = (now - lastMicros)/1e6;
    x += g.gyro.x * dt;
    y += g.gyro.y * dt;
    xTune = PI(0.4, 0.2, dt, x);
    xServo.write(xTune * 57.2958);
    yTune = PI(0.4, 0.2, dt, y);
    yServo.write(yTune * 57.2958);
    lastMicros = now;
    delay(2);
}
