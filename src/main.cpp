#include <Arduino.h>
#include <Ethernet.h>
// #include <EthernetUdp.h>
// #include <M5_Ethernet.h>
#include <M5Core2.h>
#include <SPI.h>
#include <ctime>

#define M5STACK_LAN
#define CS   26

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 210);
EthernetUDP Udp;
struct tm last_timestamp;
constexpr double timeout = 0.1;

void handle_timer_error() {
  M5.Lcd.println("Failed to obtain time");
  while(true) {
    delay(100);
  }
}

void handle_no_ethernet_hardware() {
  M5.Lcd.println("Hardware did not find. Please check your M5Stack.");
  while(true) {
    delay(100);
  }
}

void setup() {
  M5.begin(true, false, false, false, mbus_mode_t::kMBusModeOutput, false);
  // M5.Power.begin();
  M5.Lcd.println("Battery Relay");
  M5.Lcd.println(" ");

  // if (Ethernet.hardwareStatus() == EthernetNoHardware) {
  //   handle_no_ethernet_hardware();
  // }

  // if (!getLocalTime(&last_timestamp)) {
  //   handle_timer_error();
  // }
  Ethernet.init(CS);
  Ethernet.begin(mac, ip);
  M5.Lcd.print(Ethernet.localIP());
  // Udp.begin(80);
}

void loop() {
//   if (Ethernet.linkStatus() == LinkOFF) {
//     return;
//     // M5.Lcd.println("Ethernet cable is not connected.");
//   }
  // M5.Lcd.print(Ethernet.localIP());
//   const int packet_size = Udp.parsePacket();
//   if(packet_size != 0) {
//     M5.Lcd.println(std::to_string(packet_size).c_str());
//   }
  // struct tm now;
  // if(Udp.parsePacket() != 0) {
  //   if (!getLocalTime(&now)) {
  //     handle_timer_error();
  //   }
  //   last_timestamp = now;
  // }
  // else {
  //   if(!getLocalTime(&now)) {
  //     handle_timer_error();
  //   }
  // }
  // if(difftime(mktime(&now), mktime(&last_timestamp))>= timeout) {
  //   M5.Lcd.println("Connection timeout.");
  //   return;
  // }
  // M5.Lcd.println("Connection success.");
}


