#include <Arduino.h>
#include <ctime>
#include <M5_Ethernet.h>
#include <M5Core2.h>
#include <SPI.h>
#include <limits>

#define CS 26
#define RELAY_PIN 32

/// @sa https://ouxt-polaris.esa.io/posts/532

// If you want to configure as right motor, please comment in this line.
#define RIGHT_MOTOR

#ifdef RIGHT_MOTOR
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 200);
IPAddress control_machine_ip(192, 168, 0, 190);
const int port = 2000;
#endif // RIGHT_MOTOR

// If you want to configure as left motor, please comment in this line.
// #define LEFT_MOTOR

#ifdef LEFT_MOTOR
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE};
IPAddress ip(192, 168, 0, 210);
IPAddress control_machine_ip(192, 168, 0, 100);
const int port = 2000;
#endif // LEFT_MOTOR

EthernetServer server(port);
EthernetClient return_connection_client;
uint16_t timeout_count = 20; // When starting this program, relay should be OFF.
bool connection_timeouted = true;

void display_timeout() {
  M5.Lcd.fillRect(0, 30, 320, 210, RED);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(90, 120);
  M5.Lcd.printf("Timeout");
  M5.Lcd.setTextSize(1);
}

void display(bool relay_on) {
  if(relay_on) {
    if(connection_timeouted) {
      M5.Lcd.fillRect(0, 30, 320, 190, GREEN);
      M5.Lcd.fillRect(0, 190, 320, 50, BLACK);
    }

    M5.Lcd.setTextSize(3);
    double until_timeout = 2.0 - timeout_count * 0.1;
    M5.Lcd.setCursor(0, 192);
    M5.Lcd.printf("Until timeout => \n%3f [sec]", until_timeout);
    M5.Lcd.setTextSize(1);
  }
  else {
    if(!connection_timeouted) {
      display_timeout();
    }    
  }
}

void setup() {
  M5.begin(true, false, true);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  Ethernet.init(CS);
  Ethernet.begin(mac, ip);
  delay(500);
  
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Battery Relay\n");
  M5.Lcd.setCursor(0, 15);
  M5.Lcd.println(Ethernet.localIP());
  // M5.Lcd.setCursor(180, 15);
  // M5.Lcd.println(control_machine_ip);
  display_timeout();

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet was not found, please check hardware connection.");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  return_connection_client.connect(control_machine_ip, port);
  return_connection_client.setConnectionTimeout(2000);

  server.begin();
}

void loop() {
  if(Ethernet.linkStatus() != LinkON) {
    timeout_count = 20;
  }
  else {
    return_connection_client.flush();
    if(return_connection_client.connected()) {
      timeout_count = 0;
    } else {
      return_connection_client.connect(control_machine_ip, port);
      ++timeout_count;
    }
  }

  const auto is_timeout = [&]() ->bool { return timeout_count >= 20; };
  display(!is_timeout());

  digitalWrite(RELAY_PIN, [&](){ return is_timeout() ? LOW : HIGH; }());
  delay(100);
  connection_timeouted = is_timeout();
}
