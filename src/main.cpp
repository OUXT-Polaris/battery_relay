#include <Arduino.h>
#include <M5_Ethernet.h>
#include <M5Core2.h>
#include <SPI.h>
#include <ctime>

#define CS 26

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 210);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

EthernetServer server(8080);

void setup() {
  M5.begin(true, false, false);
  M5.Lcd.println("Battery Relay");
  M5.Lcd.println(" ");
  Ethernet.init(CS);
  // Ethernet.begin(mac, ip, gateway, gateway, subnet);
  Ethernet.begin(mac, ip);
  delay(500);
  M5.Lcd.print(Ethernet.localIP());

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
    M5.Lcd.println(__LINE__);
  }
//   if (client && client.available() > 0) {
//     server.write(client.read());
//     // M5.Lcd.setCursor(0, 30);
//     // M5.Lcd.println("Connected");
//   } else {
//     // M5.Lcd.setCursor(0, 30);
//     // M5.Lcd.println("Not Connected");
//   }
  delay(100);
}