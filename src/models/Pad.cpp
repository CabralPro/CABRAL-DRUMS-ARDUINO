#include <Arduino.h>

struct Pad
{
  int minVibration,
      pinAnalog,
      maxRangeVibration,
      lastBeatTime = 0,
      lastBeat = 0,
      lastReady = 0,
      countCatchInterval = 0,
      countVibrationStopInterval = 0,
      volumeBeat = 0;

  Pad(int _minVibration, int _pinAnalog, int _maxRangeVibration = 800)
      : minVibration(_minVibration),
        maxRangeVibration(_maxRangeVibration),
        pinAnalog(_pinAnalog){};

  void play()
  {
    this->volumeBeat = map(this->lastBeat, 0, this->maxRangeVibration, 0, 127);
    Serial.print(String(this->pinAnalog) + "-" + this->volumeBeat + "/");
    // Serial.println(String(this->pinAnalog) + "-" + String(this->lastBeat));
  }

  void clearPad()
  {
    this->countCatchInterval = 0;
    this->countVibrationStopInterval = 0;
    this->lastBeat = 0;
    this->lastReady = 0;
  }
  
};