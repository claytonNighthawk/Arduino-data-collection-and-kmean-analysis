#include <rgb_lcd.h>
#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <time.h>
#include <stdlib.h>

// MQTT setup
//  you should set your time zone and be sure it is updating from ntp
// timedatectl set-timezone American/Los_Angeles; date;
// these are note to fix the below hard coding of dhcp information.  If we don't fix it and the dhcp lease expires the connection will break.
// also this setup presumes that the edison has been connected to the wifi via other means.  console in our case. 

//https://www.arduino.cc/en/Reference/EthernetLocalIP
//https://www.arduino.cc/en/Reference/WiFiLocalIP
//https://www.arduino.cc/en/Reference/WiFiMACAddress
//dig cas-cls.uoregon.edu | grep -v ';' | awk '/cas-cls/ {print $NF}'
//configure_edison --showWiFiIP
//ip = WiFi.localIP();
//WiFi.macAddress(mac);

// Update these with values suitable for your network.
byte mac[]    = {  0x90, 0xB6, 0x86, 0x0E, 0x3D, 0x0D };
IPAddress ip(10, 111, 224, 47);
IPAddress server(128, 223, 31, 3);
void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}
EthernetClient ethClient;
PubSubClient client(server, 8883, callback, ethClient);
char clientName[] = "arduinoClient";
char userName[] = "Project330";
char password[] = "R00tb33r!123";
char channel[] = "testing123";

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

    Ethernet.begin(mac, ip);


}

void loop() {
    //using the time.h c library
    //need current time stamp
    char timestring[24];
    time_t t;
    struct tm * localt;
    time(&t);
    localt = localtime(&t);
    strftime(timestring, 22, "%Y.%m.%d %H:%M:%S ", localt);

    //create output buffer and place the time stamp in it
    String data = String(timestring);

    if (!client.connected()) {
      client.connect(clientName, userName, password);
    } 

    //setup lcd printing
    int cursor = 0;
    lcd.setCursor(cursor, 0);

    //get temp
    float temperature = calcTemp();
    
    String convert= "";
//    dtostrf(temperature, 4, 3, convert );
    data + " " + data + convert + " C";
    
    lcd.print(temperature);
    cursor += 5;
    lcd.setCursor(cursor, 0);
    lcd.print("C");
    cursor += 2;


    // Unknown units, guessing dB 
    // doesn't update very fast, can't tell what exactly is happening  
    int soundValue = calcSound();
    
    data + String(soundValue) + " dB  ";
    
    lcd.setCursor(cursor, 0);
    lcd.print(soundValue);
    cursor += 3;
    lcd.setCursor(cursor, 0);
    lcd.print("\"dB\""); //incorrect units

    
    cursor = 0;
    // Unknown units, guessing Lumins
    int lightValue = calcLight();
    
    data + String(lightValue) + " LUX  ";
    
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

    //send the data to our channel as a char array.
    client.publish(channel,data.buffer);

    
    // Wait one second between measurements.
    delay(500);
}

