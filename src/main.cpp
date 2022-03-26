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



/* ======================================= PADS CONFIG ======================================= */

Pad pads[8] = {
	/*     CHIMBAL      */ {/*pinAnalog*/ 0, /*minVibration*/ 30, /*volumeControl*/ 350},
	/*      BUMBO       */ {/*pinAnalog*/ 1, /*minVibration*/ 30, /*volumeControl*/ 150},
	/*      CAIXA       */ {/*pinAnalog*/ 2, /*minVibration*/ 30, /*volumeControl*/ 350},
	/*       TOM        */ {/*pinAnalog*/ 3, /*minVibration*/ 50, /*volumeControl*/ 350},
	/*      TOM 2       */ {/*pinAnalog*/ 4, /*minVibration*/ 50, /*volumeControl*/ 350},
	/*      SURDO       */ {/*pinAnalog*/ 5, /*minVibration*/ 30, /*volumeControl*/ 350},
	/*  PRATO (ATAQUE)  */ {/*pinAnalog*/ 6, /*minVibration*/ 50, /*volumeControl*/ 350},
	/* PRATO (CONDUÇÃO) */ {/*pinAnalog*/ 7, /*minVibration*/ 50, /*volumeControl*/ 350},
};

/* ======================================= PADS CONFIG ======================================= */




/* ======================================= GERAL CONFIG ====================================== */

const int CAPTURE_INTERVAL_BEAT = 10;
const int VIBRATION_STOP_INTERVAL = 5;
const int MIN_RANGE_FAST_BEAT = 10;

/* ======================================= GERAL CONFIG ====================================== */



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

			// CAPTURA BATIDAS ANTES DO TERMINO DA VIBRAÇÃO DA BATIDA ANTERIOR
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
}