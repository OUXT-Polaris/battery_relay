#include <Arduino.h>
#include <ctime>
#include <M5_ACSSR.h>
#include <M5_Ethernet.h>
#include <M5Core2.h>
#include <SPI.h>

#define CS 26

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 210);

EthernetServer server(8080);
M5_ACSSR SSR;

void scan_addr() {
  int device_count = 0;
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire1.beginTransmission(addr);
    if (Wire1.endTransmission() == 0) {
      M5.Lcd.printf ("Device I2C Addr is: 0x%02X\r\n", addr);
      ++device_count;
    }
  }
  if(device_count == 0) {
    M5.Lcd.println("IC2 addres could not found.");
    while (true) {
      delay(100);
    }
  }
}

void setup() {
  M5.begin(true, false, true);
  M5.Lcd.println("Battery Relay");
  M5.Lcd.println(" ");
  Ethernet.init(CS);
  Ethernet.begin(mac, ip);
  delay(500);
  M5.Lcd.println(Ethernet.localIP());

  scan_addr();
  if(SSR.begin(&Wire1, 32, 33, 0x50)) {
    M5.Lcd.println("Solid state relay found.");
  }
  else {
    M5.Lcd.println("Solid state relay did not find.");
    while(true) {
      delay(100);
    }
  }
  SSR.setLEDColor(0xff0000);

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