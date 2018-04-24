#include "config.h"
#include "WiFi.h"
#include<Wire.h>


char serverName[] = "api.pushingbox.com";
boolean lastConnected = false;
int status = WL_IDLE_STATUS;     // the Wifi radio's status


const int MPU_addr=0x68; // I2C address of the MPU-6050



WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(ledpin,OUTPUT);

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

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {
  sendToPushingBox(devid,"Let's count stuff!");
  delay(15000);
  digitalWrite(ledpin,ledstate);
  ledstate != ledstate;
  int16_t x = readFromMPU(accelerometer_x);
}

//Function for sending the request to PushingBox
void sendToPushingBox(char devid[], char data[]){
	char postmsg [50];
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
int16_t readFromMPU(MPU MPU_value){
	int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

  	Wire.beginTransmission(MPU_addr);
  	Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  	Wire.endTransmission(false);
  	Wire.requestFrom(MPU_addr,14,true); // request a total of 14 registers

  	switch(MPU_value){
		case accelerometer_x:
		AcX=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
		return AcX;
		break;
		case accelerometer_y:
		AcY=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
		return AcY;
		break;
		case accelerometer_z:
		AcZ=Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
		return AcZ;
		break;
		case temperature:
		Tmp=Wire.read()<<8|Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
		return Tmp;
		break;
		case gyro_x:
		GyX=Wire.read()<<8|Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
		return GyX;
		break;
		case gyro_y:
		GyY=Wire.read()<<8|Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
		return GyY;
		break;
		case gyro_z:
		GyZ=Wire.read()<<8|Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
		return GyZ;
		break;
		default:
		return 99;
	  }

  }
