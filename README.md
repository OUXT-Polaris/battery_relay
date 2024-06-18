# Firmware for battery relay.

## Parts
1. [Core2 v1.1](https://docs.m5stack.com/ja/core/Core2%20v1.1)
2. [RELAY](https://docs.m5stack.com/ja/unit/relay)
3. [LAN Base with W5500 V12](https://docs.m5stack.com/ja/base/lan_v12)

## How to use.

1. Confiture IP address/mac address in [main.cpp](https://github.com/OUXT-Polaris/battery_relay/blob/610158f9c25edcca5f182bcb9c78c370128f6c33/src/main.cpp#L11-L12)
2. Flash firmware to M5Stack Core2 by platform.io
3. Connect lan and turn on M5stack.
4. python3 (path_to_battery_relay_directory)/scripts/client.py
