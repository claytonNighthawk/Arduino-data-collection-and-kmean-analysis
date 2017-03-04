/*
 Basic MQTT example with Authentication

  - connects to an MQTT server, providing username
    and password
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
*/

#include <SPI.h>
#include <Ethernet.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

//https://www.arduino.cc/en/Reference/EthernetLocalIP

//https://www.arduino.cc/en/Reference/WiFiLocalIP

//https://www.arduino.cc/en/Reference/WiFiMACAddress

//dig cas-cls.uoregon.edu | grep -v ';' | awk '/cas-cls/ {print $NF}'

//configure_edison --showWiFiIP

ip = WiFi.localIP();
WiFi.macAddress(mac);
byte mac[]    = {  0x90, 0xB6, 0x86, 0x0E, 0x3D, 0x0D };
IPAddress ip(10, 111, 224, 47);
IPAddress server(128, 223, 31, 3);

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

EthernetClient ethClient;
PubSubClient client(server, 8883, callback, ethClient);

void setup()
{
  Ethernet.begin(mac, ip);
  // Note - the default maximum packet size is 128 bytes. If the
  // combined length of clientId, username and password exceed this,
  // you will need to increase the value of MQTT_MAX_PACKET_SIZE in
  // PubSubClient.h
  
  if (client.connect("arduinoClient", "Project330", "R00tb33r!123")) {
    client.publish("testing123","yo MTV raps");
    //client.subscribe("inTopic");
  }
}

void loop()
{
  client.loop();
}