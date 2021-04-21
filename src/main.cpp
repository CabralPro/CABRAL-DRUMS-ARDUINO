#include <Arduino.h>
#include "./models/Pad.cpp"
#include "./tests/test.h"

Pad pads[8] = {
    /* CHIMBAL          */ {/*minVibration*/ 30, /*pinAnalog*/ 0, /*volumeControl*/ 350}, 
    /* BUMBO            */ {/*minVibration*/ 30, /*pinAnalog*/ 1, /*volumeControl*/ 150},
    /* CAIXA            */ {/*minVibration*/ 30, /*pinAnalog*/ 2, /*volumeControl*/ 350},
    /* TOM              */ {/*minVibration*/ 50, /*pinAnalog*/ 3, /*volumeControl*/ 350},
    /* TOM 2            */ {/*minVibration*/ 50, /*pinAnalog*/ 4, /*volumeControl*/ 350},
    /* SURDO            */ {/*minVibration*/ 30, /*pinAnalog*/ 5, /*volumeControl*/ 350},
    /* PRATO (ATAQUE)   */ {/*minVibration*/ 50, /*pinAnalog*/ 6, /*volumeControl*/ 350},
    /* PRATO (CONDUÇÃO) */ {/*minVibration*/ 50, /*pinAnalog*/ 7, /*volumeControl*/ 350},
};

/* GERAL CONFIG */
const int CAPTURE_INTERVAL_BEAT = 10;
const int VIBRATION_STOP_INTERVAL = 5;
const int MIN_RANGE_FAST_BEAT = 10;
/* GERAL CONFIG */

void setup()
{
  const unsigned long SPEED_SERIAL = 115200;
  Serial.begin(SPEED_SERIAL);
}

int reader;
const int NUMBER_PADS = sizeof(pads) / sizeof(pads[0]);

void loopMain()
{

  for (int i = 0; i < NUMBER_PADS; i++)
  {
    reader = analogRead(i);

    if (reader > pads[i].minVibration)
    {
      pads[i].countCatchInterval++;
      pads[i].countVibrationStopInterval = 0;

      if (reader > pads[i].lastBeat)
        pads[i].lastBeat = reader;

      // captura batidas antes do termino da vibração da batida anterior
      if (pads[i].countCatchInterval > CAPTURE_INTERVAL_BEAT && reader > (pads[i].lastReady + MIN_RANGE_FAST_BEAT))
      {
        pads[i].countCatchInterval = 0;
        pads[i].lastBeat = reader;
      }

      if (pads[i].countCatchInterval == CAPTURE_INTERVAL_BEAT)
        pads[i].play();

      pads[i].lastReady = reader;
    }
    else if (pads[i].countCatchInterval > 0)
    {
      pads[i].countVibrationStopInterval++;

      if (pads[i].countVibrationStopInterval == VIBRATION_STOP_INTERVAL)
      {
        if (pads[i].countCatchInterval < CAPTURE_INTERVAL_BEAT)
          pads[i].play();

        pads[i].clearPad();
      }
    }

  }
  
}

void loop()
{
  loopMain();
  // loopTeste(1);
}