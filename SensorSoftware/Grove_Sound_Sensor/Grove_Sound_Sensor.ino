// Demo for Grove - Starter Kit V2.0

// Turns on the Grove - LED when the sound level measured by the 
// Grove - Sound Sensor exceeds a certain value.
// Connect the Grove - Sound Sensor to the socket marked A1

// Define the pin the sound sensor is connected to.
const int pinSound = A1;

// Define the sound level above which to turn on the LED.
// Change this to a larger value to require a louder noise level.
int thresholdValue = 600;

void setup() {
    // Configure LED's pin for output signals.
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    // Read the value of the sound sensor.
    int sensorValue = analogRead(pinSound);

    // If the measured sound level is above the threshold, blink the LED.
    if (sensorValue > thresholdValue) {
        // Turn the LED on for 200ms, then turn it back off.
        digitalWrite(LED_BUILTIN,HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN,LOW);
    }
}

