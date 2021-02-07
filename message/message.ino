#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <EEPROM.h>
#include <Servo.h>
#include "SSD1306Wire.h"
#include <ArduinoWebsockets.h>

#include "credentials.h"
const char* ssid = _ssid;
const char* password = _password;
const String wsEndpoint = _wsEndpoint;

// Config
const int readDelay = 5; // delay in second for read status 

using namespace websockets;

WebsocketsClient client;

SSD1306Wire oled(0x3C, D2, D1);
Servo myservo;
int pos = 90;
int increment = -1;
int lightValue;
bool wasRead;

void drawMessage(const String& message) {
  oled.clear();
  oled.drawStringMaxWidth(0, 0, 128, message);
  oled.display();
}

void wifiConnect() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);

    for (int i = 0; i < 15 && WiFi.status() != WL_CONNECTED; i++) {
      Serial.print(".");
      delay(1000);
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   // ESP IP Address

}

void spinServo() {
  myservo.write(pos);
  delay(50);    // 50ms between turns

  if (pos == 75 || pos == 105) { // rot 75°-105°
    increment *= -1;
  }
  pos += increment;
}

void onMessageCallback(WebsocketsMessage message) {
  Serial.print("Got Message: ");
  Serial.println(message.data());
  wasRead = 0;
  drawMessage(message.data());
  while (!wasRead) {
    spinServo();
    lightValue = analogRead(0);
    Serial.println("Light: ");
    Serial.println(lightValue);
    if (lightValue > 300) {
      wasRead = 1;
      Serial.print("Message read.");
      delay(readDelay * 1000); //wait (5) second before clearing the screen
      oled.clear();
      oled.drawString(55, 25, "<3");
      oled.display();
    }
  }
}

void onEventsCallback(WebsocketsEvent event, String data) {
  if (event == WebsocketsEvent::ConnectionOpened) {
    Serial.println("Connnection Opened");
  } else if (event == WebsocketsEvent::ConnectionClosed) {
    Serial.println("Connnection Closed");
  } else if (event == WebsocketsEvent::GotPing) {
    Serial.println("Got a Ping!");
  } else if (event == WebsocketsEvent::GotPong) {
    Serial.println("Got a Pong!");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  myservo.attach(16);     // D0 pin

  oled.init();
  oled.flipScreenVertically();
  oled.setColor(WHITE);
  oled.setTextAlignment(TEXT_ALIGN_LEFT);
  oled.setFont(ArialMT_Plain_16);

  oled.clear();
  oled.drawString(55, 25, "<3");
  oled.display();

  wifiConnect();

  // Setup Callbacks
  client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);
  // Connect to server
  client.connect(wsEndpoint);
  // Send a message
  client.send("Hi Server!");
  // Send a ping
  client.ping();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi");
    wifiConnect();
  }

  client.poll();

}
