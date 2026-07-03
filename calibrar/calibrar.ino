/**************************************************************
 * Robô Paragon - Código de Calibração
 *
 * Código de exemplo competitivo para os alunos e
 * instrutores do projeto ROBOTIEEE.
 **************************************************************/

// * Inclusão de bibliotecas * //
// (Reutiliza ódigos feitos por outras pessoas que facilitam a programação)

#include <Ultrasonic.h>
#include <compkit.h>

// * Definição dos pinos conectados no Arduino * //

// Sensores infravermelhos (detectam a linha preta)
int infra1 = A0;
int infra2 = A1;
int infra3 = A2;
int infra4 = A3;
int infra5 = A4;

// Ultrassom (detecta distância de obstáculos)
int ultrasonic_trig = 12;
int ultrasonic_echo = 13;

// Sensores de cor (detectam a cor de marcações na pista)
int cor_esquerda_in = A6;
int cor_direita_in = A7;
int led_vermelho = 14;
int led_verde = 15;
int led_azul = 16;

// * Definição dos sensores que utilizam biblioteca * //

// Ultrassom (detecta distância de obstáculos)
Ultrasonic ultrasonic(ultrasonic_trig, ultrasonic_echo);
// Sensores de cor (detectam a cor de marcações na pista)
color_sensor<4> sensorCorEsquerda(cor_esquerda_in, led_vermelho, led_verde,
                                  led_azul);
color_sensor<4> sensorCorDireita(cor_direita_in, led_vermelho, led_verde,
                                 led_azul);

// Setup - roda uma vez ao ligar o robô para configurar os sensores e a
// comunicação serial
void setup() {
  // Configuração da comunicação serial
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
}
