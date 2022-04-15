/**
 * @file test.cpp
 * @author Arthur Cabral Lemos (cabraltec02@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <Arduino.h>
#include "test.h"
#include "./models/pad.cpp"

int readerTest;
int loopControl = 0;
int lastReaderTest = 0;

void loopTeste(int numberPads)
{
  for (int i = 0; i < numberPads; i++)
  {
    readerTest = analogRead(i);

    if (readerTest > 10)
    {
      Serial.println(String(i) + '-' + String(readerTest));
    }
  }
}