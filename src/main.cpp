#include <Arduino.h>
#include <ctime>
#include <M5_Ethernet.h>
#include <M5Core2.h>
#include <SPI.h>

#define CS 26
#define RELAY_PIN 32

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 210);

EthernetServer server(8080);

void setup() {
  M5.begin(true, false, true);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  M5.Lcd.println("Battery Relay");
  M5.Lcd.println(" ");
  Ethernet.init(CS);
  Ethernet.begin(mac, ip);
  delay(500);
  M5.Lcd.println(Ethernet.localIP());

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet was not found, please check hardware connection.");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }

  server.begin();
}

void loop() {
  EthernetClient client = server.available();
  if(client) {
    digitalWrite(RELAY_PIN, HIGH);
  }
  delay(100);
}
