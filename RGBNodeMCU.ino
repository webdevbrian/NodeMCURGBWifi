#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include "common/RGBLED.h"
Ticker ticker;
WiFiClient espClient;
PubSubClient client(espClient);

void tick() {
  //toggle state
  int state = digitalRead(BledPin);
  digitalWrite(BledPin, !state);
}

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode...");
  Serial.println(WiFi.softAPIP());
  ticker.detach();
  ticker.attach(0.1, tick);
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup() {
  // sets the pins as output
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  digitalWrite(BledPin, 1);

  /* Wifi setup */
  ticker.attach(0.7, tick);

  Serial.begin(115200);

  // Initialize WiFiManager and then destroy it after it's used
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setConnectTimeout(20);

  // Enable to hard reset saved settings
  //wifiManager.resetSettings();

  // Set the SSID name
  wifiManager.autoConnect("NodeMCURGBWifi");
  Serial.println("Connected to Wifi.");

  ticker.detach();

  // Initialize any endpoints here
  digitalWrite(BledPin, LOW);
}

void loop() {
  //
  // REMINDERS: - All pins must be faded in first to be able to be faded out after.
  //            - Delay is set at 2ms (check _delay to see it's setting) (255 steps = 1.5seconds for fading in and out)
  //            - loop will only start when wifi is connected and configured. Connect to the SSID named above from a phone or computer to configure.
  //

  FadeOn(RledPin);
  FadeOn(GledPin);
  FadeOn(BledPin);
  FadeOff(GledPin);
  FadeOff(BledPin);
  FadeOn(GledPin);
  FadeOff(RledPin);
  FadeOn(BledPin);
  FadeOn(RledPin);
  Pulse(RledPin, 5, 1);
  Pulse(BledPin, 5, 4);
  Pulse(GledPin, 5, 10);
  FadeOff(BledPin);
  FadeOff(GledPin);
  FadeOff(RledPin);

/* 
  changeColorByHex("ff0000");
  delay(200);
  changeColorByHex("c300c5");
  delay(200);
  changeColorByHex("0013c5");
  delay(200);
  changeColorByHex("00c5c3");
  delay(200);
  changeColorByHex("00c54f");
  delay(200);
  changeColorByHex("25c500");
  delay(200); 
  changeColorByHex("86c500");
  delay(200);
  changeColorByHex("ffa200");
  delay(random(200));
  changeColorByHex("ff3c00");
  delay(random(200));
  changeColorByHex("ff0000");
  delay(random(200));
*/

/* 
  changeColorByHex("5300ff");
  delay(random(100));
  changeColorByHex("0018ff");
  delay(random(100));
  changeColorByHex("0060ff");
  delay(random(100));
  changeColorByHex("0066ff");
  delay(random(100));
*/

/* 
  FadeOn(RledPin);
  FadeOn(GledPin);
  FadeOn(BledPin);
  Pulse(RledPin, 5, 1);
  Pulse(RledPin, 5, 4);
  Pulse(RledPin, 5, 10);
  TurnOff(RledPin);
  TurnOff(GledPin);
  TurnOff(BledPin);

  //Serial.println("Main loop end");
*/
}