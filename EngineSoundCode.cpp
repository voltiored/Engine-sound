#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>

#define SENSOR_PIN 2 // Pin del sensor de movimiento
#define RX_PIN 10    // Pin RX del DFPlayer Mini
#define TX_PIN 11    // Pin TX del DFPlayer Mini

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Crea un objeto de SoftwareSerial para comunicarse con el DFPlayer Mini
DFPlayerMini_Fast myMP3;                 // Crea un objeto DFPlayerMini_Fast para controlar el módulo de reproducción de audio

bool movimientoDetectado = false;

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  mySerial.begin(9600); // Inicializa la comunicación serial con el DFPlayer Mini
  if (!myMP3.begin(mySerial)) {
    Serial.println(F("Error al inicializar el DFPlayer Mini"));
    while (true);
  }
}

void loop() {
  if (digitalRead(SENSOR_PIN) == HIGH) { // Si se detecta movimiento
    if (!movimientoDetectado) {          // Si el movimiento no se había detectado anteriormente
      reproducirAudio();                 // Reproducir el archivo de audio
      movimientoDetectado = true;        // Establecer que se ha detectado movimiento
    }
  } else {                               // Si no se detecta movimiento
    if (movimientoDetectado) {           // Si el movimiento había sido detectado anteriormente
      detenerAudio();                    // Detener la reproducción de audio
      movimientoDetectado = false;       // Establecer que ya no se detecta movimiento
    }
  }
}

void reproducirAudio() {
  myMP3.play(1); // Reproduce el archivo de audio con el número de track 1
  delay(100);    // Pequeña pausa para asegurar la reproducción
}

void detenerAudio() {
  myMP3.stop(); // Detiene la reproducción de audio
}
