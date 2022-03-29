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
	int minVibration,
			pinAnalog,
			maxRangeVibration,
			lastBeatTime = 0,
			lastBeat = 0,
			lastReady = 0,
			countCatchInterval = 0,
			countVibrationStopInterval = 0,
			volumeBeat = 0;

	Pad(int _pinAnalog, int _minVibration, int _maxRangeVibration = 800)
			: minVibration(_minVibration),
				maxRangeVibration(_maxRangeVibration),
				pinAnalog(_pinAnalog){};

	void play()
	{
		this->volumeBeat = map(this->lastBeat, 0, this->maxRangeVibration, 0, 127);
		auto separator = "-0";

		if(this->lastBeat < 100)
			separator = "-00";
		else if(this->lastBeat > 999)
			separator = "-";
		
		Serial.println( String(this->pinAnalog) + separator + String(this->lastBeat) );
	}

	void clearPad()
	{
		this->countCatchInterval = 0;
		this->countVibrationStopInterval = 0;
		this->lastBeat = 0;
		this->lastReady = 0;
	}
};