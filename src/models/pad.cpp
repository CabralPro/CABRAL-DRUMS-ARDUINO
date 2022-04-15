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

	Pad(int _pinAnalog, int _minVibration, float _volumeControl)
		: minVibration(_minVibration),
		  volumeControl(_volumeControl),
		  pinAnalog(_pinAnalog){};

	void play()
	{
		this->beat = this->beat * this->volumeControl;
		auto separator = "-";

		if (this->beat < 100)
			separator = "-0";
		else if (this->beat > 128)
			this->beat = 128;

		Serial.print(String(this->pinAnalog) + separator + String(this->beat));
		// Serial.println( String(this->pinAnalog) + separator + String(this->beat));
	}

	void clearPad()
	{
		this->countCatchInterval = 0;
		this->beat = 0;
	}
};