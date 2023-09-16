#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"
#include <EEPROM.h>
#define I2S_DOUT 12
#define I2S_BCLK 14
#define I2S_LRC 27
#define volumeControl 35
#define channelUp 33
#define channelDown 32
#define EEPROM_SIZE 10
#define eeprom_address 9

Audio audio;

const int stationCount =6;
String stations[stationCount] = {"https://lhttp.qingting.fm/live/20013/64k.mp3", 
                                  "https://lhttp.qingting.fm/live/5055/64k.mp3", 
                                  "https://lhttp.qingting.fm/live/4938/64k.mp3", 
                                  "https://lhttp.qingting.fm/live/4944/64k.mp3",  
                                  "https://lhttp.qingting.fm/live/20012/64k.mp3", 
                                  "https://lhttp.qingting.fm/live/1163/64k.mp3"};

int lastRead = -200;
int currStation;
unsigned long pushTime =0;
String ssid =    "xxxxxx";
String password = "xxxxxx";
IPAddress dns1(8, 8, 8, 8);
IPAddress dns2(8, 8, 4, 4);
void setup() {
  Serial.begin(115200);
  
  EEPROM.begin(EEPROM_SIZE);
  int tmp= EEPROM.read(eeprom_address);
  Serial.println("Read current station from EEPROM");
  Serial.println(tmp);
  if (tmp>stationCount)
  {
    currStation=0;
  }
  else
  {
    currStation = tmp;
  }
  

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid.c_str(), password.c_str());
  
  while (WiFi.status() != WL_CONNECTED) delay(1500);
  WiFi.config(WiFi.localIP(), WiFi.gatewayIP(), WiFi.subnetMask(), dns1);
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(2); // 0...21
  setStation();
  pinMode(channelUp, INPUT_PULLUP);
  pinMode(channelDown, INPUT_PULLUP);
}


void setStation ()
{

  while (audio.connecttohost(stations[currStation].c_str())==false)
  {
    Serial.println("try again");
    delay(200);
  }
 
}

void loop()
{
  audio.loop();

  int Push_button_state_up = digitalRead(channelUp);
  int Push_button_state_down = digitalRead(channelDown);
  int volume_read = analogRead(volumeControl);
  if (abs(volume_read -lastRead) > 200)
  {
    int newVolume =(volume_read+400)/200;
    audio.setVolume(newVolume); 
    lastRead = volume_read;   
  }
  Serial.println(volume_read);
  if (((Push_button_state_up == LOW)||(Push_button_state_down == LOW)) && (millis()-pushTime>2000)) {
      pushTime=millis();
      if (Push_button_state_up == LOW)
      {
         currStation += 1;
         if (currStation>=stationCount)
        {
          currStation =0;
        }
      }
      else
      {
        currStation -= 1;
        if (currStation<0)
        {
          currStation = stationCount-1;
        }
      }
      EEPROM.write(eeprom_address, currStation);
      EEPROM.commit();
      Serial.print("Change to station: ");
      Serial.println(currStation);
      setStation();
  }
}
