#define NUM_PADS 12  
const int piezoPins[NUM_PADS] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};

const int padThresholds[NUM_PADS] = {10, 1023, 1023, 1023, 1023, 1023, 
                                    1023, 1023, 1023, 1023, 1023, 1023};

unsigned long lastHitTime[NUM_PADS] = {0};
const int debounceTime = 50;  // Reduzi o debounce para 50ms
const int peakDetectionWindow = 20;  // Janela de detecção mais curta para resposta rápida
int peakValue[NUM_PADS] = {0};
bool hitDetected[NUM_PADS] = {false};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < NUM_PADS; i++) {
    pinMode(piezoPins[i], INPUT);
  }
}

void loop() {
  for (int i = 0; i < NUM_PADS; i++) {
    int piezoValue = analogRead(piezoPins[i]);

    // Se detectar uma batida acima do threshold e não estiver em debounce
    if (piezoValue > padThresholds[i]) {
      if (!hitDetected[i] && millis() - lastHitTime[i] > debounceTime) {
        peakValue[i] = piezoValue;  
        hitDetected[i] = true;  // Marca que uma batida foi detectada
        lastHitTime[i] = millis();
        Serial.println(peakValue[i]);
      }
    } else {
      // Reset da detecção após a janela de tempo
      if (hitDetected[i] && millis() - lastHitTime[i] > peakDetectionWindow) {
        hitDetected[i] = false;
        peakValue[i] = 0;  // Reseta o valor do pico para a próxima batida
      }
    }
  }
}
