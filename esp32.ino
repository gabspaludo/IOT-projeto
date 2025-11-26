#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int LIMITE_PORTA = 10;

#define TRIGGER_PIN 33
#define ECHO_PIN 25

long duration;
int distance;
bool estaAberta = false;
bool ultimoEstadoAberta = false;

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_GABRIEL_MARCELO_GONCALVES");
  Serial.println("Bluetooth iniciado. Pronto para parear.");
}

void loop() {
  duration = readUltrasonicDistance(TRIGGER_PIN, ECHO_PIN);
  distance = duration * 0.0343 / 2;

  if (distance > LIMITE_PORTA) {
    estaAberta = true;
  } else {
    estaAberta = false;
  }

  if (estaAberta != ultimoEstadoAberta) {

    if (estaAberta) {
      SerialBT.println("ABERTA");
      Serial.println("Mudou para: ABERTA");
    } else {
      SerialBT.println("FECHADA");
      Serial.println("Mudou para: FECHADA");
    }

    ultimoEstadoAberta = estaAberta;

    delay(300);
  }

  delay(100);
}
