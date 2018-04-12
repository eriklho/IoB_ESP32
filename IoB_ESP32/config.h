#ifndef CONFIG_H
#define CONFIG_H

char wifissid[] = "WIFI_SSID";   //  your network SSID (name)
char wifipass[] = "WIFI_PASSWORD";    // your WPA network password
char devid[] = "Your pushingbox ID"; // https://www.pushingbox.com/ to find your pushingbox ID

const int ledpin = 2;
int ledstate = LOW;

// Debug mode
boolean DEBUG = true;


#endif
