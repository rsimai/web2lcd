#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <uri/UriBraces.h>
#include <uri/UriRegex.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

const char *ssid = "YOURSID";
const char *password = "YOURPASSPHRASE";
String mytext;

WebServer server(80);

void setup(void) {
  Serial.begin(115200);
  Serial.println("init LCD");
  lcd.init();
  lcd.backlight();
  delay(250);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.print(".");
  }
  Serial.println("");
  lcd.setCursor(0, 0);
  Serial.print("Connected to ");
  lcd.print("Connected to ");
  Serial.println(ssid);
  lcd.print(ssid);
  Serial.print("IP address: ");
  lcd.setCursor(0,1);
  lcd.print("IP: ");
  Serial.println(WiFi.localIP());
  lcd.print(WiFi.localIP());
  lcd.setCursor(0,2);
  lcd.print("http://esp.fritz.box");

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on(F("/"), []() {
    String page="<html>";
    page += "<head><title>esp2lcd interface</title></head>";
    page += "<body><p>Hello from esp32!</p>";
    page += "<p>use POST with http://esp.fritz.box/text/ to control the display.</p>";
    page += "<p>Available commands:<table border=1>";
    page += "<tr><th>parameter</th><th>value</th><th>explanation</th></tr>";
    page += "<tr><td>c</td><td>clear</td><td>clear display, cursor home</td></tr>";
    page += "<tr><td>c</td><td>home</td><td>cursor home</td></tr>";
    page += "<tr><td>c</td><td>blon</td><td>backlight on</td></tr>";
    page += "<tr><td>c</td><td>bloff</td><td>backlight off</td></tr>";
    page += "<tr><td>c</td><td>restart</td><td>restart the esp32 device</td></tr>";
    page += "<tr><td>t</td><td>TEXT</td><td>text to be displayed</td></tr>";
    page += "<tr><td>x</td><td>0-19</td><td>cursor x position</td></tr>";
    page += "<tr><td>y</td><td>0-3</td><td>cursor y position</td></tr>";
    page += "</table></body></html>";
    
    server.send(200, "text/html", page);
  });

  server.on(UriBraces("/text/{}"), []() {
    String text = "";
    String command="";
    int x=0;
    int y=0;

    String message = "\nDebug\n\n";  //some debug message for the serial console
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";

    for (uint8_t i = 0; i < server.args(); i++) {  //iterate through the args to process them
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";

      command=server.argName(i); // parameter
      text = server.arg(i);      // value
      

      if (command.equals("c")) {
        if (text.equals("clear")) {
          lcd.clear();
        }
        else if (text.equals("home")) {
          lcd.home();
        }
        else if (text.equals("blon")) {
          lcd.backlight();
        }
        else if (text.equals("bloff")) {
          lcd.noBacklight();
        }
        else if (text.equals("restart")) {
          ESP.restart();
        }
      }
      else if (command.equals("x")) {
        x = text.toInt();
        lcd.setCursor(x, y);
      }
      else if (command.equals("y")) {
        y = text.toInt();
        lcd.setCursor(x, y);
      }

      else if (command.equals("t")) {
          lcd.print(text);
      }
    }
  Serial.println(message); //output the debug message
  });

  server.begin();
  Serial.println("HTTP server started");
  lcd.setCursor(0,3);
  lcd.print("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
