#include "config.h"
#include "WiFi.h"


char serverName[] = "api.pushingbox.com";
boolean lastConnected = false;  
int status = WL_IDLE_STATUS;     // the Wifi radio's status

WiFiClient client;

void setup() {
  Serial.begin(115200);
 
  // attempt to connect using WPA2 encryption:
  Serial.println("Attempting to connect to WPA network...");
  status = WiFi.begin(wifissid, wifipass);
  
  // if you're not connected, stop here:
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // if you are connected, print out info about the connection:
  else {
    Serial.println("Connected to network");
  }
}
 
void loop() {
  sendToPushingBox("Let's count stuff!");
  delay(15000);
}

//Function for sending the request to PushingBox
void sendToPushingBox(char devid[], char data[]){
  client.stop(); if(DEBUG){Serial.println("connecting...");}
  if(client.connect(serverName, 80)) { 
    if(DEBUG){Serial.println("connected");}
    if(DEBUG){Serial.println("sendind request");}
    
    Serial.println("connected");
    sprintf(postmsg,"GET /pushingbox?devid=%c&status=%d HTTP/1.1",devid,data);  // NOTE** In this line of code you can see where the temperature value is inserted into the wed address. It follows 'status=' Change that value to whatever you want to post.
    client.println(postmsg);
    client.println("Host: api.pushingbox.com");
    client.println("Connection: close");
    client.println();

    Serial.println(postmsg);
    Serial.println("Host: api.pushingbox.com");
    Serial.println("Connection: close");
    Serial.println();
    client.stop();
  } 
}
