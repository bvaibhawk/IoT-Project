#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

// Network parameters
const char* ssid     = "Vaibhaw";
const char* password = "vaibhaw@1007";
unsigned int field1 = 1;
unsigned int field2 = 2;
// ThingSpeak information
char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 1169180;
char* readAPIKey = "KPRJQMHG07TKHXTL";
float distance = 0;   
float temp = 0;
int toggle=LOW;
WiFiClient client;
float readTSData( long TSChannel,unsigned int TSField ){
    
  float data =  ThingSpeak.readFloatField( TSChannel, TSField, readAPIKey );
  Serial.println( " Data read from ThingSpeak: " + String( data, 9 ) );
  return data;

}
int connectWiFi(){
    
    while (WiFi.status() != WL_CONNECTED) {
      
        WiFi.begin( ssid, password );
        delay(2500);
        Serial.println("Connecting to WiFi");
    }
    
    Serial.println( "Connected" );
    ThingSpeak.begin( client );
}
void setup() {

Serial.begin(9600);
Serial.println("Start");
pinMode(D4,OUTPUT);
connectWiFi();

}
void loop(){
  distance = readTSData( channelID, field1);
temp = readTSData( channelID, field2);
if (distance<=50){
toggle=!toggle;
digitalWrite(D4,toggle);
}
if (toggle==HIGH && 30<=temp<50){
  analogWrite(D4,255);
}
if (toggle==HIGH && 0<temp<30){
  analogWrite(D4,150);
}

}
