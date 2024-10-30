// Inspiration: https://www.reddit.com/r/arduino/comments/12uy1r2/never_gunna_give_you_up_wifi_beacon/

//"Free Wifi" WiFi Beacon
//code written by @n4bi10p for the good of humanity!

//You can change Each line of the string in the array for multiple ap's
//is 36 characters (including spaces) or less
//to comply with SSID naming limitations.

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

String never_gonna[] = {
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
  "FREE WIFI",
};

const int update_interval = 30000; // SSID update interval in ms

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String responseHTML = ""
                      "<!DOCTYPE html><html lang='en'><head>"
                      "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>"
                      "<meta name='viewport' content='width=device-width'>"
                      "<title>Fuckkingg the WiFi</title></head><body>"

"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⢤⣶⡐⠭⡛⢿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢩⡞⢯⢻⡿⢿⣷⡦⡑⢌⢻⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢟⣜⣿⣽⣿⣷⣿⣿⣷⠷⣈⡶⣼⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢏⣴⢯⢿⣿⣿⣿⣿⣿⠯⣃⡾⢡⣿⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⣜⡾⣯⣷⣹⠿⢷⣿⣍⡼⡟⣱⣿⣿⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⢺⣽⣻⣽⣷⣯⡟⣬⡝⣎⠗⣼⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠋⣛⠛⡛⠛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⣨⣿⣿⣿⣿⣽⣷⣿⣷⣻⠃⣾⣿⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠁⢠⠓⣤⠒⡔⢲⠉⡌⠙⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢡⣽⣿⣿⣿⣿⡝⣿⣿⣿⣿⠁⣼⣿⣿⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⢬⣛⣾⣱⣎⢷⢣⡚⡄⠆⡄⣈⢉⠉⢉⡉⠉⠙⠛⢿⠋⣠⣿⣿⣿⣿⣿⣿⣿⣯⣟⡖⣰⣿⣿⣿⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⣿⣿⠃⢘⣦⡝⣾⢷⣿⣿⣷⣿⣾⣴⣻⡵⣮⣻⣧⢿⡱⢢⠀⢠⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⡿⠁⢀⡛⢾⡽⣞⣿⣿⣿⣿⣿⣿⢷⣾⡾⣵⣋⣬⣾⢣⠁⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⣿⡿⠋⠀⡠⢂⠽⣩⢻⡽⡿⠋⣃⢡⢀⠤⢢⣤⣤⣁⠙⠛⠁⠂⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣽⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⡟⠁⠰⣌⡱⠩⣆⠱⢣⠘⢀⣞⡱⣎⣮⣗⣷⣾⣿⣿⣷⣶⠄⢰⣯⢿⣿⣿⣿⣿⣿⣿⣿⣿⡯⠅⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⡇⢨⢑⠦⣙⢇⢦⠃⢀⡴⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢠⣟⣯⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⡇⠸⢌⢊⠵⣪⠖⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢁⣾⣾⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⠍⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⡇⠀⠠⠞⡙⠂⢠⣯⣾⣿⡿⣟⣿⣿⣿⣿⣿⣿⣿⣿⡟⢸⣧⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⡇⣼⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⡇⢀⣰⢶⠛⠀⣞⡷⣛⡾⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⠡⡞⣿⡿⣿⣿⣿⣿⣿⣿⣿⠋⡴⠀⣁⣽⣭⣧⣌⠉⠻⣿⣿⣿⣿⣿⣿⣿ <br>"
"⣿⣿⡟⠡⠊⣉⠀⠀⡾⢡⣛⣭⣟⣾⣽⣿⣿⣿⣿⣿⣿⣿⡏⢰⡹⣽⣻⣿⣿⣿⣿⣿⣿⣖⡻⠀⣴⣾⣿⣿⣾⣾⣞⢧⠀⣿⣿⣿⣿⣿⣿ <br>"
"⣿⠏⠀⢠⡞⠁⡀⠳⣌⢧⣛⣶⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⢁⢮⣳⢯⣷⣻⣿⣽⡾⣯⡳⡽⠀⡼⣶⣿⣿⣟⡷⣟⢮⡹⡂⣿⣿⣿⣿⣿⣿ <br>"
"⡿⠀⢠⡞⠀⢠⡑⡳⡜⣯⣻⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⡰⣎⣷⣻⣞⣿⣳⢯⡿⣴⡛⠔⣸⣽⣿⣿⣿⣾⢿⣛⣎⠷⢠⣿⣿⣿⣿⣿⣿ <br>"
"⡇⠀⠸⠌⢐⢢⡑⢧⡻⣼⣳⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⣰⢳⣝⣾⣳⣟⡾⣽⣫⢷⣣⠍⣰⣿⣿⣿⣿⣟⣾⡿⡿⣽⠊⢈⣛⡛⢛⠿⣿⣿ <br>"
"⡇⠀⠠⢉⢆⠲⣙⢮⢷⣻⣿⣿⣿⣿⣿⣿⣿⣿⣛⠆⣜⢧⣟⣾⣳⣿⢾⡽⣳⢟⡶⠃⣸⣿⣿⣿⣿⣿⣽⡷⣿⢟⣧⠋⣰⣷⣿⣷⣅⡊⢹ <br>"
"⡇⠀⠀⡉⢆⡹⣌⣻⢾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⣟⣾⣻⢾⣳⣿⣯⣻⣵⣛⢾⡘⢁⣾⣿⣿⣿⣿⣿⣿⣻⣯⣟⡆⢰⣿⣿⢿⣻⢮⡟⢸ <br>"
"⣇⠀⠀⠰⢌⡲⢥⡿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⡿⣽⠾⣽⣿⣿⣿⣳⢯⡶⣯⢳⡅⢸⣿⣿⣿⣿⣿⣿⣿⣿⣵⡏⢠⣿⣿⣿⣿⡽⣯⡐⢣ <br>"
"⣿⡄⠀⠐⠨⢕⡯⣽⣻⢿⣿⣿⡿⣿⣻⢿⣟⣯⣟⢷⣻⣳⢯⣿⣯⣟⣷⣻⡽⣣⠆⣻⣿⣯⣿⣿⠿⣾⡽⣯⡟⢀⣿⣿⣿⣿⢿⣳⢷⣊⢸ <br>"
"⣿⡇⠀⠀⠀⠈⢟⡳⢯⡿⣾⣻⣽⣳⢿⣿⣿⣻⣞⡯⣗⣯⣿⢯⣷⣻⣞⡷⣹⢆⡣⢿⣽⣿⣿⢯⣟⣷⡼⣿⠁⣿⣿⣿⣿⣿⣟⡿⣬⢇⢸ <br>"
"⣿⣷⠀⠀⠀⠀⠀⠉⠳⠙⢧⢓⠮⡝⣯⢿⣽⣳⢟⣾⣽⣾⣻⣻⣾⣳⢯⡽⣓⢮⡹⣿⣟⡿⣽⣞⡿⣽⣳⠇⣘⣿⣿⣿⣟⡿⣾⡝⣧⠃⣾ <br>"
"⣿⣿⡀⠀⠀⠀⠀⠀⠀⢃⠘⡘⠜⣣⠻⣜⢧⣛⢟⣿⣿⣧⢿⣿⣻⠿⡼⢧⡛⣤⣻⣧⣟⡻⣼⣛⣿⣻⢿⠀⣿⣿⣿⣟⣿⣿⢧⣻⠄⡄⣿ <br>"
"⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠐⠀⠌⡀⠛⢬⢣⢯⣿⣿⢻⡼⣻⣟⢿⡻⣝⡣⡝⢶⢯⡷⣯⢷⢧⣛⡶⢯⡞⣰⢯⣟⣾⣽⢿⣞⡯⡗⡋⣰⣿ <br>"
"⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠈⠐⠠⠀⠂⠌⠲⡉⠎⠳⣽⣳⡾⣏⠷⣍⠲⣝⢯⣾⣿⣿⣯⣿⡿⣽⡻⣜⢧⣟⡾⣽⢯⣟⡾⡝⡱⢀⣿⣿ <br>"
"⣿⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠁⠀⠉⠑⠉⠃⡌⠱⢎⡳⣝⢾⣻⠾⣿⣽⡳⣽⡹⣾⣽⣻⢽⣚⡮⢷⡍⢁⣼⣿⣿ <br>"
"⣿⣿⣿⣿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠁⠊⠐⠉⠢⢍⡳⢧⡞⣽⡲⣟⣳⢯⣟⣧⢻⡜⡃⢀⣾⣿⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⣶⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠀⠂⠉⠒⡙⠶⣙⢧⡻⣝⠮⡜⢣⠎⣡⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠐⠈⠄⡐⠠⠀⠀⠈⠠⠁⠊⠑⠊⠅⠙⣀⣼⣿⣿⣿⣿⣿⣿ <br>"
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣀⣀⣀⣀⣀⣀⣀⣀⣤⣴⣦⣤⣤⣤⣄⣀⣀⣀⠀⠀⠀⠀⢀⣠⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿ <br>"
"All Your's xD 😝 <br>"
                      "<p><a href='https://youtu.be/dQw4w9WgXcQ?si=6yt-VS1i-l2I2Twl'>Have fun</a></p></body></html>";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("RickRoller started...");

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  
  Serial.println("Setting SSID to '" + never_gonna[0] + "'.");
  WiFi.softAP(never_gonna[0].c_str());

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // reply to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html; charset=utf-8", responseHTML);
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
  
  static unsigned long last_update_time = 0;
  if (millis() - last_update_time > update_interval) {
    static int current_line = 0;
    current_line = (current_line + 1) % (sizeof(never_gonna) / sizeof(String));
    Serial.println("Setting SSID to '" + never_gonna[current_line] + "'.");
    WiFi.softAP(never_gonna[current_line].c_str());
    last_update_time = millis();
  }
  delay(1000);
}

///created by @n4bi10p///