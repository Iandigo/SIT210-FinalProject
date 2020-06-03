#include "HC_SR04.h"
#include <Wire.h>
double cm = 0.0;

int trigPin = 8;
int echoPin = 7;
int state = 0;

HC_SR04 rangefinder = HC_SR04(trigPin, echoPin);

void setup() 
{
    Wire.begin(0x08); // Join I2C bus 
    Spark.variable("cm", &cm, DOUBLE); 
    // define LED
    for (int i = 3; i <=6; i++) {
        pinMode(i, OUTPUT);
    }
    // define the sensor
    pinMode (trigPin, OUTPUT);
    pinMode (echoPin, INPUT);
    //defiine i2c communication
    Wire.onRequest(sendData);
}

void loop() 
{
    cm = rangefinder.getDistanceCM();
    
    Particle.publish("motion", (String) cm);
    
    delay(3000);
    
    // condition to start the LED timer
    if (cm <= 15) {
        ledtimer();
        //check Handwash timer status
        if (state == 1) {
            Particle.publish("timer", "start");
        }
    } 
    
    
    
}

void ledtimer()
{
    state = 1; // change the state of the timer to start
    digitalWrite(6, HIGH);
    delay(3000);
    for (int i = 5; i >= 3; i--) {
        digitalWrite (i, HIGH);
        if (i == 3) {
            digitalWrite (6, LOW);
        }
        delay(6666);
    }
    for (int i = 6; i >= 3; i--) {
        digitalWrite(i, LOW);
    }
    state = 0;
}

void sendData() {
    Wire.write(state); // send the timer state to RPi
}
