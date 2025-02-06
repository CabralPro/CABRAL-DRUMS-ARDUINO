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


const int bufferLenght = 7;


// Função para enviar os dados com formato fixo: "DD-DDD\n"
// Onde os dois primeiros dígitos (DD) são o número do pad (0 a 99)
// e os três dígitos (DDD) são o valor (0 a 999)
// Caso o valor seja maior que 999, ele é limitado a 999.
void sendHit(uint8_t pad, uint16_t value) {
  char buf[7];

  // Converte o número do pad para dois dígitos
  buf[0] = '0' + (pad / 10);  // dígito das dezenas
  buf[1] = '0' + (pad % 10);  // dígito das unidades

  // Caractere separador
  buf[2] = '-';

  // Converte o valor para três dígitos
  buf[3] = '0' + (value / 100);         // dígito das centenas
  buf[4] = '0' + ((value / 10) % 10);     // dígito das dezenas
  buf[5] = '0' + (value % 10);            // dígito das unidades

  // Quebra de linha
  buf[6] = '\n';

  // Envia os 7 caracteres via Serial
  Serial.write(buf, 7);
}


void loop() {
  unsigned long currentTime = millis();
  
  for (int i = 0; i < NUM_PADS; i++) {
    int piezoValue = analogRead(piezoPins[i]);

    if (piezoValue > padThresholds[i]) {
      if (!hitDetected[i] && (currentTime - lastHitTime[i] > debounceTime)) {
        peakValue[i] = piezoValue;
        hitDetected[i] = true;
        lastHitTime[i] = currentTime;

        // Envia o pad e o valor com a formatação "DD-DDD\n"
        sendHit(i, peakValue[i]);
      }
    } else {
      if (hitDetected[i] && (currentTime - lastHitTime[i] > peakDetectionWindow)) {
        hitDetected[i] = false;
        peakValue[i] = 0;
      }
    }
  }
}

