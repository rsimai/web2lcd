GET/POST data to 4x20 LCD display within WLAN
=============================================

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
| parameter | value   | explanation                │
| ---       | ---     | ---                        |
| c         | clear   | clear display, cursor home |
| c         | home    | cursor home                |
| c         | blon    | backlight on               |
| c         | bloff   | backlight off              |
| c         | restart | restart the esp32 device   |
| t         | TEXT    | text to be displayed       |
| x         | 0-19    | cursor x position          |
| y         | 0-3     | cursor y position          |


### curl POST example
```
curl -d "c=clear" -d "t=Some text here" -d "x=0" -d "y=1" -d "t=continue here" -d "x=0" -d "y=2" -d "t=third line" -d "x=0" -d "y=3" -d "t=four" -H "Content-Type: application/x-www-form-urlencoded" -X POST http://esp.your.domain/text/
```

### browser GET example
```
http://esp.your.domain/text/?c=clear&t=Text%20first%20line&x=0&y=1&t=continue%20second
```

### build

Edit and adjust your ssid and password, compile and upload through the Arduino IDE. Enjoy.

