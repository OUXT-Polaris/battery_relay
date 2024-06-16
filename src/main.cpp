#include <Arduino.h>
#include <Ethernet.h>
// #include <EthernetUdp.h>
// #include <M5_Ethernet.h>
#include <M5Core2.h>
#include <SPI.h>
#include <ctime>

#define CS 26

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 210);

void setup() {
  M5.begin(true, false, false);
  M5.Lcd.println("Battery Relay");
  M5.Lcd.println(" ");
  Ethernet.init(CS);
  Ethernet.begin(mac, ip);
  delay(100);
  M5.Lcd.print(Ethernet.localIP());
  // Udp.begin(80);
}

void loop() {
}