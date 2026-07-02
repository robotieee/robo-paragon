/**************************************************************
 * Robô Paragon - Código Principal
 *
 * Código usado no robô Paragon como exemplo competitivo para os alunos do
 * projeto ROBOTIEEE.
 *
 * Autor: Alexandre Hiroyuki Yamauchi
 **************************************************************/

// Inclusão de bibliotecas
// (Reutiliza ódigos feitos por outras pessoas que facilitam a programação)
#include <Ultrasonic.h>
#include <compkit.h>

// * Definição de variáveis que guardam a calibração dos sensores * //

// Distância do ultrassom para desviar de obstáculos
int distancia_cm = 0;
// Valor do sensor infravermelho para detectar linha preta
int infravermelho_preto = 0;
// Calibração do sensor de cor para verde
color_sensor caliVerde = {120, 600, 120, 100};
// Calibração do sensor de cor para vermelho
color_sensor caliVermelho = {600, 120, 120, 100};
// Calibração do sensor de cor para branco
color_point caliBranco = {600, 600, 600, 100};
// Calibração do sensor de cor para preto
color_point caliPreto = {120, 120, 120, 100};

// * Definição dos pinos conectados no Arduino * //

// Sensores infravermelhos (detectam a linha preta)
int infra1 = A0;
int infra2 = A1;
int infra3 = A2;
int infra4 = A3;

// Motores (controlam a direção do robô)
int motor_dir_frente = 10;
int motor_dir_tras = 11;
int motor_esq_frente = 12;
int motor_esq_tras = 13;

// Ultrassom (detecta distância de obstáculos)
int ultrasonic_trig = 12;
int ultrasonic_echo = 13;

// Sensores de cor (detectam a cor de marcações na pista)
int cor_esquerda_in = A4;
int cor_direita_in = A5;
int led_vermelho = 13;
int led_verde = 12;
int led_azul = 11;

// * Definição dos sensores que utilizam biblioteca * //

// Ultrassom (detecta distância de obstáculos)
Ultrasonic ultrasonic(ultrasonic_trig, ultrasonic_echo);
// Sensores de cor (detectam a cor de marcações na pista)
color_sensor<4> sensorCorEsquerda(cor_esquerda_in, led_vermelho, led_verde,
                                  led_azul);
color_sensor<4> sensorCorDireita(cor_direita_in, led_vermelho, led_verde,
                                 led_azul);

// * Definição de variáveis globais * //

// Ganhos do controlador PID
float kp = 0.1;
float ki = 0.01;
float kd = 0.01;
// Erro anterior do controlador PID
float erro_anterior = 0;

// Indices que representam as cores calibradas
int verde;
int vermelho;
int branco;
int preto;

void setup() {
  // Configuração dos pinos //

  pinMode(motor_dir_frente, OUTPUT);
  pinMode(motor_dir_tras, OUTPUT);
  pinMode(motor_esq_frente, OUTPUT);
  pinMode(motor_esq_tras, OUTPUT);

  // Calibração dos sensores de cor //

  // Cor 1
  verde = sensorCorEsquerda.add_color_point(caliVerde);
  verde = sensorCorDireita.add_color_point(caliVerde);

  // Cor 2
  vermelho = sensorCorEsquerda.add_color_point(caliVermelho);
  vermelho = sensorCorDireita.add_color_point(caliVermelho);

  // Cor 3
  branco = sensorCorEsquerda.add_color_point(caliBranco);
  branco = sensorCorDireita.add_color_point(caliBranco);

  // Cor 4
  preto = sensorCorEsquerda.add_color_point(caliPreto);
  preto = sensorCorDireita.add_color_point(caliPreto);
}

void loop() {}
