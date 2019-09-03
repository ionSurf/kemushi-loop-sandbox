#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include "SPIFFS.h"
  #include <HTTPClient.h>
  #include <SD.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include "AudioFileSourceSPIFFS.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2SNoDAC.h"

// To run, set your ESP8266 build to 160MHz, and include a SPIFFS of 512KB or greater.
// Use the "Tools->ESP8266/ESP32 Sketch Data Upload" menu to write the MP3 to SPIFFS
// Then upload the sketch normally.  

// pno_cs from https://ccrma.stanford.edu/~jos/pasp/Sound_Examples.html

AudioGeneratorMP3     *mp3;
AudioFileSourceSPIFFS *file;
AudioOutputI2SNoDAC   *out;
AudioFileSourceID3    *id3;

String tracks[ 10 ] = {
    "/pno-cs.mp3",
    "/alma_h001.mp3",
    "/alma_h002.mp3",
    "/alma_h003.mp3",
    "/alma_m001.mp3",
    "/alma_m002.mp3",
    "/alma_m003.mp3",
    "/alma_l001.mp3",
    "/alma_l002.mp3",
    "/alma_l003.mp3"
};

bool  soundTickerFlag = false;

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string) {
  (void)cbData;
  Serial.printf("ID3 callback for: %s = '", type);

  if (isUnicode) {
    string += 2;
  }
  
  while (*string) {
    char a = *(string++);
    if (isUnicode) {
      string++;
    }
    Serial.printf("%c", a);
  }
  Serial.printf("'\n");
  Serial.flush();
}

void init_audio( int trackIndex = 0 ) {
  file  = new AudioFileSourceSPIFFS( tracks[ trackIndex ].c_str() );
  id3   = new AudioFileSourceID3(file);
  id3->RegisterMetadataCB(MDCallback, (void*)"ID3TAG");
  out   = new AudioOutputI2SNoDAC(0);
  mp3   = new AudioGeneratorMP3();
  mp3->begin(file, out);
}

void setup_audio() {
  WiFi.mode(WIFI_OFF); 
  Serial.begin(115200);
  vTaskDelay(1000);
  SPIFFS.begin(true);
}

void loop_audio() {
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  } else {
    mp3->stop();
    Serial.printf("MP3 done\n");
    soundsTicker.detach();
    soundTickerFlag = false;
  }
}