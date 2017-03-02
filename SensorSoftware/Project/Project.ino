#include <Wire.h>
#include "rgb_lcd.h"

// Connect LCD to one of the I2C ports
rgb_lcd lcd;

const int colorR = 0;
const int colorG = 255;
const int colorB = 0;

// Connect the light sensor 
const int pinLight = A0;

// Connect the sound sensor
const int pinSound = A1;

// Connect the temp sensor 
const int pinTemp = A2;

// Define the B-value of the thermistor.
// This value is a property of the thermistor, 
// used to convert from the analog value to a temperature value.
const int B = 3975;

float calcTemp() {
    // Get the (raw) value of the temperature sensor.
    int val = analogRead(pinTemp);

    // Determine the current resistance of the thermistor based on the sensor value.
    float resistance = (float)(1023-val)*10000/val;

    // Calculate the temperature based on the resistance value.
    float temperature = 1/(log(resistance/10000)/B+1/298.15)-273.15;

    // Returns Celsius
    return temperature;
}

int calcSound() {
    return analogRead(pinSound);
}

int calcLight() {
    return analogRead(pinLight);
}

void setup() {
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
}

void loop() {
    int cursor = 0;
    lcd.setCursor(cursor, 0);

    float temperature = calcTemp();

    lcd.print(temperature);
    cursor += 5;
    lcd.setCursor(cursor, 0);
    lcd.print("C");
    cursor += 2;

    // Unknown units, guessing dB 
    // doesn't update very fast, can't tell what exactly is happening  
    int soundValue = calcSound();
    lcd.setCursor(cursor, 0);
    lcd.print(soundValue);
    cursor += 3;
    lcd.setCursor(cursor, 0);
    lcd.print("\"dB\""); //incorrect units

    
    cursor = 0;
    // Unknown units, guessing Lumins
    int lightValue = calcLight();
    lcd.setCursor(cursor, 1);
    lcd.print(lightValue);
    cursor += 3;
    lcd.setCursor(cursor, 1);
    lcd.print("\"LUX\""); //incorrect units
    cursor += 6;

    //Seconds 
    lcd.setCursor(cursor, 1);
    int seconds = millis()/1000;
    lcd.print(seconds);
    lcd.setCursor(cursor + 1 + floor(log10(seconds)), 1);
    lcd.print("sec");


    // Wait one second between measurements.
    delay(500);
}

