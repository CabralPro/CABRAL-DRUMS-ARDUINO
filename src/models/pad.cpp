/**
 * @file Pad.cpp
 * @author Arthur Cabral Lemos (cabraltec02@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <Arduino.h>

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