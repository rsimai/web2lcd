POST data to 4x20 LCD display within WLAN
=========================================

### ESP-32 to bridge clients from local WLAN to a HD44780 compatible display

Connected through I2C, needs 

GND - GND
5V  - 5V
G21 - SDA
G22 - SCL

### greets the browser

Hello from esp32!

use POST with http://esp.your.domain/text/ to control the display.

Available commands:
│ parameter │ value │ explanation │
│ c │ clear   │ clear display, cursor home │
│ c │ home    │ cursor home                │
│ c │ blon    │ backlight on               │
│ c │ bloff   │ backlight off              │
│ c │ restart │ restart the esp32 device   │
│ t │ TEXT    │ text to be displayed       │
│ x │ 0-19    │ cursor x position          │
│ y │ 0-3     │ cursor y position          │

### build

Edit and adjust your ssid and password, compile and upload through the Arduino IDE. Enjoy.

