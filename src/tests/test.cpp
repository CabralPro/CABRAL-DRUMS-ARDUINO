#include <Arduino.h>
#include "test.h"

int readerTest;
int loopControl = 0;
int lastReaderTest = 0;

void loopTeste(int pin)
{
  readerTest = analogRead(pin);
  // if ((reader > 15 && reader > lastReaderTest * 0.7) || (loopControl < 500 && loopControl > 0))
  // if ((readerTest > 15 && readerTest))
  if (readerTest > 10)
  {
    Serial.println(readerTest);
    loopControl++;
    lastReaderTest = readerTest;
  }
}