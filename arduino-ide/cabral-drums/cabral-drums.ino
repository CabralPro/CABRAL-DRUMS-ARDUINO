/**
 * @file main.cpp
 * @author Arthur Cabral Lemos (cabraltec02@gmail.com)
 * @brief
 * @version 0.2
 * @date 2022-03-18
 *
 * @copyright Copyright (c) 2022
 *
 */


struct Pad
{
  int pinAnalog,
    minVibration,
    beat = 0,
    countCatchInterval = 0;

  float volumeControl = 1.0;

  char buffer[6];

  Pad(int _pinAnalog, int _minVibration, float _volumeControl)
    : minVibration(_minVibration),
      volumeControl(_volumeControl),
      pinAnalog(_pinAnalog){};

  void play()
  {
    this->beat = constrain(this->beat * this->volumeControl, 5, 128);

    snprintf(this->buffer, sizeof(this->buffer), "%d-%03d", this->pinAnalog, this->beat);
    //snprintf(this->buffer, sizeof(this->buffer) + 16, "!!! TESTE !!! %d-%03d\n", this->pinAnalog, this->beat);

    Serial.print(this->buffer);
  }

  void clearPad()
  {
    this->countCatchInterval = 0;
    this->beat = 0;
  }

};

/* ======================================= PADS CONFIG ======================================= */

Pad pads[] = {
  /*     CHIMBAL      */ {/*pinAnalog*/ 0, /*minVibration*/ 10, /*volumeControl*/ 0.5},
  /*      BUMBO       */ {/*pinAnalog*/ 1, /*minVibration*/ 20, /*volumeControl*/ 1.0},
  /*      CAIXA       */ {/*pinAnalog*/ 2, /*minVibration*/ 10, /*volumeControl*/ 0.5},
  /*       TOM        */ {/*pinAnalog*/ 3, /*minVibration*/ 20, /*volumeControl*/ 0.5},
  /*      TOM 2       */ {/*pinAnalog*/ 4, /*minVibration*/ 20, /*volumeControl*/ 0.5},
  /*      SURDO       */ {/*pinAnalog*/ 5, /*minVibration*/ 10, /*volumeControl*/ 0.5},
  /*  PRATO (ATAQUE)  */ {/*pinAnalog*/ 6, /*minVibration*/ 20, /*volumeControl*/ 0.5},
  /* PRATO (CONDUCAO) */ {/*pinAnalog*/ 7, /*minVibration*/ 20, /*volumeControl*/ 0.5},
};

/* ======================================= PADS CONFIG ======================================= */



/* ======================================= GERAL CONFIG ====================================== */

const int CAPTURE_INTERVAL_BEAT = 2;
const unsigned long SPEED_SERIAL = 460800;

/* ======================================= GERAL CONFIG ====================================== */


void setup()
{
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

      if (reader > pads[i].beat)
        pads[i].beat = reader;

      if (pads[i].countCatchInterval == CAPTURE_INTERVAL_BEAT)
        pads[i].play();
    }
    else if (pads[i].countCatchInterval > 0)
    {
      pads[i].clearPad();
    }
  }
}

void loop()
{
  loopMain();
}

