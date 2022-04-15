/**
 * @file main.cpp
 * @author Arthur Cabral Lemos (cabraltec02@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <Arduino.h>
#include "./models/pad.cpp"
#include "./tests/test.h"

/* ======================================= PADS CONFIG ======================================= */

Pad pads[] = {
	/*     CHIMBAL      */ {/*pinAnalog*/ 0, /*minVibration*/ 10, /*volumeControl*/ 1.5},
	/*      BUMBO       */ {/*pinAnalog*/ 1, /*minVibration*/ 20, /*volumeControl*/ 3.0},
	/*      CAIXA       */ {/*pinAnalog*/ 2, /*minVibration*/ 10, /*volumeControl*/ 1.8},
	/*       TOM        */ {/*pinAnalog*/ 3, /*minVibration*/ 20, /*volumeControl*/ 1.8},
	/*      TOM 2       */ {/*pinAnalog*/ 4, /*minVibration*/ 20, /*volumeControl*/ 1.8},
	/*      SURDO       */ {/*pinAnalog*/ 5, /*minVibration*/ 10, /*volumeControl*/ 1.8},
	/*  PRATO (ATAQUE)  */ {/*pinAnalog*/ 6, /*minVibration*/ 20, /*volumeControl*/ 1.5},
	/* PRATO (CONDUÇÃO) */ {/*pinAnalog*/ 7, /*minVibration*/ 20, /*volumeControl*/ 1.5},
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
	//loopTeste(NUMBER_PADS);
}