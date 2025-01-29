#define NUM_PADS 12
const int piezoPins[NUM_PADS] = { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11 };

const int padThresholds[NUM_PADS] = { 12, 1023, 1023, 1023, 1023, 1023,
                                      1023, 1023, 1023, 1023, 1023, 1023 };

unsigned long lastHitTime[NUM_PADS] = { 0 };
const int debounceTime = 50;
const int peakDetectionWindow = 20;
int peakValue[NUM_PADS] = { 0 };
bool hitDetected[NUM_PADS] = { false };

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < NUM_PADS; i++) {
    pinMode(piezoPins[i], INPUT);
  }
}

void loop() {
  unsigned long currentTime = millis();
  char buffer[10];

  for (int i = 0; i < NUM_PADS; i++) {
    int piezoValue = analogRead(piezoPins[i]);

    if (piezoValue > padThresholds[i]) {
      if (!hitDetected[i] && (currentTime - lastHitTime[i] > debounceTime)) {
        peakValue[i] = piezoValue;
        hitDetected[i] = true;
        lastHitTime[i] = currentTime;

        // play pad
        itoa(i, buffer, 10);
        int len = strlen(buffer);
        buffer[len] = '-';
        itoa(peakValue[i], buffer + len + 1, 10);
        buffer[len + strlen(buffer + len + 1)] = '\n';
        Serial.write(buffer, strlen(buffer));


      }
    } else {
      if (hitDetected[i] && (currentTime - lastHitTime[i] > peakDetectionWindow)) {
        hitDetected[i] = false;
        peakValue[i] = 0;
      }
    }
  }
}
