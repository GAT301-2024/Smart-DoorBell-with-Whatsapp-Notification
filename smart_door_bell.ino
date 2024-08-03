#include <Arduino.h>
#include <WiFi.h>
#include <Callmebot_ESP32.h>


// Define the GPIO pinsll
const int ALARM = 21;
const int BUTTON_PIN = 4;
const char* ssid = "omatech";
const char* password = "omatech1992";

String local_IP;
String phoneNumber = "+256782191479";
String apiKey = "6304470";
String messsage = "someone at your door";

void setup() {
  // Initialize the LED pin as an output
  pinMode(ALARM, OUTPUT);
  

  // Initialize the button pin as an input with internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize serial communication for debugging
  Serial.begin(115200);
    WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  // Ensure alarm is initially off
  digitalWrite(ALARM, LOW);
}



void loop() {
  // Read the button state
  int buttonState = digitalRead(BUTTON_PIN);

  // Check if the button is pressed (LOW because of the pull-up resistor)
  if (buttonState == LOW) {
    // Turn on the ALARM
    digitalWrite(ALARM, HIGH);
    delay(50);
    Serial.println("Button pressed, ALARM ON");
     // Whatsapp Message
  Callmebot.whatsappMessage(phoneNumber, apiKey, messsage);
  Serial.println(Callmebot.debug());
  digitalWrite(ALARM,HIGH);
  // Optional: Add a delay to prevent multiple messages
    delay(5000); // Wait 5 seconds
  } else {
    // Turn off the LED
    digitalWrite(ALARM, LOW);
    //Serial.println("Button released, ALARM off");
  }

  // Small delay to debounce the button
  delay(50);
}
