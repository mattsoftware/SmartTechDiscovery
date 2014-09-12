// Read a DHT22 and display the temperature and humidity on a Freetronics DMD
// More info: google them, mate.
// DavidTangye@gctechspace.org

#include <TimerOne.h>
#include <SPI.h>

#include <DMD.h>
const int DISPLAYS_ACROSS = 1;
const int DISPLAYS_DOWN = 1;
DMD dmd(DISPLAYS_ACROSS,DISPLAYS_DOWN);

#define DHTPIN 2
#define DHTTYPE DHT22
#include "DHT.h"
DHT dht(DHTPIN, DHTTYPE);

#include "Arial_black_16.h"
#include "SystemFont5x7.h"
const int charSizeX = 7;
const int line2Yposn = 9;
const int leftMargin = 1;

const String textToScroll = "Gold Coast TechSpace ";
const int scrollStepMillis = 30;

const int showTextMillis = 1000;
const int showTempMillis = 3000;
const int showHumidMillis = 3000;


void ScanDMD() {
  dmd.scanDisplayBySPI();
}


void setup(void) {
  dht.begin();
  Timer1.initialize(5000);
  Timer1.attachInterrupt(ScanDMD);
}


void scrolltheText(String dispString) {
  dmd.clearScreen( true );
  dmd.selectFont( Arial_Black_16 );
  char newString[256];
  int sLength = dispString.length();
  dispString.toCharArray( newString, sLength+1 );
  dmd.drawMarquee(newString,sLength,( 32*DISPLAYS_ACROSS )-1 , 0 );
  long startMillis=millis();
  long timerMillis=startMillis;
  boolean ret=false;
  while(!ret) {
    if ( ( timerMillis + scrollStepMillis ) < millis() ) {
      ret=dmd.stepMarquee( -1 , 0 );
      timerMillis=millis();
    }
  }
}

void loop(void) {
float readInFloat;
char readInChars[6];

  scrolltheText(textToScroll);
  delay(showTextMillis);

  dmd.selectFont(System5x7);
  dmd.drawString(1,0,"Temp ",5,GRAPHICS_NORMAL);

  readInFloat = dht.readTemperature();
// Debug: readInFloat = 23.45;
  if (isnan(readInFloat)) {
    dmd.drawString(leftMargin,line2Yposn," ??!",4,GRAPHICS_NORMAL);
  }
  else {
    dmd.drawString(leftMargin,0,"Temp ",5,GRAPHICS_NORMAL);
    dtostrf(readInFloat,5,2,readInChars);
    dmd.drawChar(leftMargin,line2Yposn,readInChars[0],GRAPHICS_NORMAL);
    dmd.drawChar(charSizeX * 1 + leftMargin,line2Yposn,readInChars[1],GRAPHICS_NORMAL);
    dmd.writePixel(charSizeX * 2 - 1 + leftMargin,15,GRAPHICS_NORMAL,1);
    dmd.drawChar(charSizeX * 2 + 1 + leftMargin,line2Yposn,readInChars[3],GRAPHICS_NORMAL);
    dmd.drawChar(charSizeX * 3 + 1 + leftMargin,line2Yposn,'c', GRAPHICS_NORMAL);
  }
  delay(showTempMillis);

  dmd.drawString(leftMargin,0,"Humid ",5,GRAPHICS_NORMAL);
  readInFloat = dht.readHumidity();
// Debug: readInFloat = 67.89;
  if (isnan(readInFloat)) {
    dmd.drawString(leftMargin,line2Yposn," ???!",5,GRAPHICS_NORMAL);
  }
  else {
    dtostrf(readInFloat,5,2,readInChars);
    dmd.drawChar(leftMargin,line2Yposn,readInChars[0],GRAPHICS_NORMAL);
    dmd.drawChar(charSizeX * 1 + leftMargin,line2Yposn,readInChars[1],GRAPHICS_NORMAL);
    dmd.drawChar(charSizeX * 2 + 1 + leftMargin,line2Yposn,readInChars[3],GRAPHICS_NORMAL);
    dmd.drawChar(charSizeX * 3 + 1 + leftMargin,line2Yposn,'%', GRAPHICS_NORMAL);
  }
  delay(showHumidMillis);
}

