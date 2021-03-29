
#define BLYNK_PRINT Serial

float Lat,Lon,Speed;
#include <SoftwareSerial.h>
SoftwareSerial SwSerial(2, 3); // RX, TX
    
#include <BlynkSimpleSerialBLE.h>
#include <SoftwareSerial.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "s7u6aQrA19UyFrWbBRLzrWZxTQR546GY";

SoftwareSerial SerialBLE(2, 3); // RX, TX



BlynkTimer timer;
BLYNK_WRITE(V1) {
  GpsParam gps(param);

  // Print 6 decimal places for Lat, Lon
  Serial.print("Lat: ");
  Serial.println(gps.getLat(), 7);
 Lat = gps.getLat();

  Serial.print("Lon: ");
  Serial.println(gps.getLon(), 7);
   Lon = gps.getLon();

  // Print 2 decimal places for Alt, Speed
  Serial.print("Altitute: ");
  Serial.println(gps.getAltitude(), 2);

  Serial.print("Speed: ");
  Serial.println(gps.getSpeed(), 2);
  Speed = gps.getSpeed();

  Serial.println();
}

void SendToThingspeak(void)
{ Serial.println("Start sending....");
  Blynk.virtualWrite(V0, Lat,Lon,Speed);           
  Serial.println("StOPIN....");
}

void SendToBlynk(void)
{
  Serial.println("Senndddda");
  Blynk.virtualWrite(V2, Lat);
  Blynk.virtualWrite(V3, Lon);
  Blynk.virtualWrite(V4, Speed);
}



void setup()
{
  // Debug console
  Serial.begin(9600);

  SerialBLE.begin(9600);
  Blynk.begin(SerialBLE, auth); 

  Serial.println("Waiting for connections...");

  timer.setInterval(10000L, SendToThingspeak);
  timer.setInterval(5000L, SendToBlynk);
}

void loop()
{
  Blynk.run();
  timer.run();
  
}
