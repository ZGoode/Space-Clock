#include "SevSeg.h"
#include <DS3231.h>
#include <Wire.h>

const int switchDST = 11;

boolean DST;

bool h12;
bool PM;

int hours;
int minutes;

String timeDisplay = "";

SevSeg sevseg;

DS3231 Clock;

void setup() {
  Wire.begin();

  pinMode(switchDST, INPUT);

  byte numDigits = 5;
  byte digitPins[] = {9, 5, 11, 13, 10};
  byte segmentPins[] = {8, 2, 4, 12, A0, 3, 6, 7};
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = false;
  bool leadingZeros = false;
  bool disableDecPoint = false;

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}

void loop() {
  sevseg.refreshDisplay();

  hours = Clock.getHour(h12, PM);
  minutes = Clock.getMinute();

  if (digitalRead(switchDST) == HIGH) {
    DST = true;
  } else {
    DST = false;
  }

  displayTime();
}

void displayTime() {
  char temp[6];
  String tempS;
  String AMPM;

//  if (DST) {
//    hours++;
//
//    if (hours > 24) {
//      hours = hours - 24;
//    }
//  }

  if (hours == 0) {
    hours = 12;
  }

  if (hours > 12) {
    AMPM = "P";
    hours = hours - 12;
  } else {
    AMPM = "A";
  }

  int h1 = hours / 10;
  int h2 = hours % 10;
  int m1 = minutes / 10;
  int m2 = minutes % 10;

  tempS.concat(h1);
  tempS.concat(h2);
  tempS.concat(m1);
  tempS.concat(m2);
  tempS.concat(AMPM);

  tempS.toCharArray(temp, 6);

  sevseg.setChars(temp);
}
