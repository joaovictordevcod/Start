#include <Servo.h>

Servo servoMotor;

const int pinoUmidade = A0;   // Sensor de umidade
const int pinoServo = 7;      // Servo motor
const int pinoBuzzer = 11;    // Buzzer

int valorUmidade = 0;

// Defina os limites de umidade (ajuste conforme necessário)
const int limiteMinimo =20;   // Qualquer valor acima disso já indica umidade
const int limiteAlto = 150;     // Acima disso o buzzer será acionado

void setup() {
  Serial.begin(9600);
  servoMotor.attach(pinoServo);
  pinMode(pinoBuzzer, OUTPUT);

  servoMotor.write(0);  // Posição inicial do servo
  digitalWrite(pinoBuzzer, LOW);
}

void loop() {
  valorUmidade = analogRead(pinoUmidade);
  Serial.print("Umidade: ");
  Serial.println(valorUmidade);

  if (valorUmidade > limiteMinimo) {
    // Há umidade — mover o servo
    servoMotor.write(90);   // Move o servo para 90°
  } else {
    servoMotor.write(0);    // Sem umidade — posição inicial
  }

  if (valorUmidade > limiteAlto) {
    // Umidade muito alta — aciona o buzzer
    digitalWrite(pinoBuzzer, HIGH);
  } else {
    digitalWrite(pinoBuzzer, LOW);
  }

  delay(500);  // Aguarda meio segundo antes da próxima leitura
}
