/**************************************************************
 * Robô Paragon - Código Principal
 *
 * Código usado no robô Paragon como exemplo competitivo para os alunos do
 * projeto ROBOTIEEE.
 **************************************************************/

// * Inclusão de bibliotecas * //
// (Reutiliza ódigos feitos por outras pessoas que facilitam a programação)

#include <Ultrasonic.h>
#include <compkit.h>

// * Definição de variáveis que guardam a calibração dos sensores * //

// Distância do ultrassom para desviar de obstáculos
int distancia_cm = 10;
// Valor do sensor infravermelho para detectar linha preta
int cali_infra_preto = 250;
// Calibração do sensor de cor para verde
color_sensor caliVerde = {120, 600, 120, 100};
// Calibração do sensor de cor para vermelho
color_sensor caliVermelho = {600, 120, 120, 100};
// Calibração do sensor de cor para branco
color_point caliBranco = {600, 600, 600, 100};
// Calibração do sensor de cor para preto
color_point caliPreto = {120, 120, 120, 100};

// * Definição de variáveis para ajuste manual * //

// PID
float kp = 0.1;
float kd = 0.01;
int velocidade = 100;

// Curvas
int delay_curva_esquerda = 1000;
int delay_curva_direita = 1000;
int delay_meia_volta = 2000;
int vel_esquerda = 100;
int vel_direita = 100;

// Delay para sair da situação de encruzilhada
int delay_linha_reta = 1000;

// * Definição dos pinos conectados no Arduino * //

// Sensores infravermelhos (detectam a linha preta)
int infra1 = A0;
int infra2 = A1;
int infra3 = A2;
int infra4 = A3;
int infra5 = A4;

// Motores (controlam a direção do robô)
int motor_dir_frente = 10;
int motor_dir_tras = 11;
int motor_esq_frente = 12;
int motor_esq_tras = 13;

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
// Motor controller (controla a velocidade de dois motores, da biblioteca
// compkit)
motor_controller motores(motor_esq_frente, motor_esq_tras, motor_dir_frente,
                         motor_dir_tras);

// * Definição de variáveis globais * //

// Erro anterior do controlador PID
float erro_anterior = 0;

// Indices que representam as cores calibradas
int verde;
int vermelho;
int branco;
int preto;

// Setup - roda uma vez ao ligar o robô para configurar os sensores e os motores
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

// Loop - roda continuamente para controlar o robô
void loop() {
  // Leitura da distância do ultrassom
  distancia_cm = ultrasonic.read();

  // Verifica se existe um obstáculo à frente com distância menor que a
  // distância mínima de desvio
  if (distancia_cm < distancia_cm_obstaculo) {
    // Desvia do obstáculo fazendo uma curva para o lado definido
    // Comente a função para desviar para o lado desejado conforme a necessidade
    // da pista

    desvia_obstaculo_direita();
    // desvia_obstaculo_esquerda();
  }

  // Leitura do sensor infravermelho para detectar linha preta
  int infra_read1 = analogRead(infra1);
  int infra_read2 = analogRead(infra2);
  int infra_read3 = analogRead(infra3);
  int infra_read4 = analogRead(infra4);
  int infra_read5 = analogRead(infra5);

  if (infra_read1 < cali_infra_preto && infra_read2 < cali_infra_preto &&
      infra_read3 < cali_infra_preto && infra_read4 < cali_infra_preto) {
    // Detecta encruzilhada T(pelo caminho do meio) ou encruzilhada +

    // Leitura dos sensores de cor para detectar a cor da marcação na pista
    color_point cor_esquerda;
    sensorCorEsquerda.read(cor_esquerda);
    color_point cor_direita;
    sensorCorDireita.read(cor_direita);
    // Verifica qual a calibração mais próxima da cor atual
    int cor_atual_esquerda = sensorCorEsquerda.closest_color(cor_esquerda);
    int cor_atual_direita = sensorCorDireita.closest_color(cor_direita);

    if (cor_atual_esquerda == verde && cor_atual_direita == verde) {
      // Detecta meia volta
      motores.walk(-vel_esquerda, vel_direita);
      delay(delay_meia_volta);
    } else if (cor_atual_esquerda == verde) {
      // Detecta curva para a esquerda
      motores.walk(-vel_esquerda, vel_direita);
      delay(delay_curva_esquerda);
    } else if (cor_atual_direita == verde) {
      // Detecta curva para a direita
      motores.walk(vel_esquerda, -vel_direita);
      delay(delay_curva_direita);
    } else {
      // Detecta linha reta
      motores.walk(velocidade, velocidade);
      delay(delay_linha_reta);
    }

  } else if (infra_read1 > cali_infra_preto && infra_read2 > cali_infra_preto &&
             infra_read3 < cali_infra_preto && infra_read4 < cali_infra_preto &&
             infra_read5 < cali_infra_preto) {
    // Detecta encruzilhada T(pelo caminho da esquerda)
    // Descrição: Ambos sensores da direita e sensor da frente na linha

    // Leitura dos sensores de cor para detectar a cor da marcação na pista
    color_point cor_direita;
    sensorCorDireita.read(cor_direita);
    // Verifica qual a calibração mais próxima da cor atual
    int cor_atual_direita = sensorCorDireita.closest_color(cor_direita);

    if (cor_atual_direita == verde) {
      // Detecta curva para a direita
      motores.walk(vel_esquerda, -vel_direita);
      delay(delay_curva_direita);
    } else {
      // Detecta linha reta
      motores.walk(velocidade, velocidade);
      delay(delay_linha_reta);
    }

  } else if (infra_read1 < cali_infra_preto && infra_read2 < cali_infra_preto &&
             infra_read3 > cali_infra_preto && infra_read4 > cali_infra_preto &&
             infra_read5 < cali_infra_preto) {
    // Detecta encruzilhada T(pelo caminho da direita)
    // Descrição: Ambos sensores da esquerda e sensor da frente na linha

    // Leitura dos sensores de cor para detectar a cor da marcação na pista
    color_point cor_esquerda;
    sensorCorEsquerda.read(cor_esquerda);
    // Verifica qual a calibração mais próxima da cor atual
    int cor_atual_esquerda = sensorCorEsquerda.closest_color(cor_esquerda);

    if (cor_atual_esquerda == verde) {
      // Detecta curva para a esquerda
      motores.walk(-vel_esquerda, vel_direita);
      delay(delay_curva_esquerda);
    } else {
      // Detecta linha reta
      motores.walk(velocidade, velocidade);
      delay(delay_linha_reta);
    }

  } else if (infra_read1 < cali_infra_preto && infra_read2 < cali_infra_preto &&
             infra_read3 > cali_infra_preto && infra_read4 > cali_infra_preto) {
    // Detecta curva de 90 para a esquerda
    motores.walk(-vel_esquerda, vel_direita);
    delay(delay_curva_esquerda);
  } else if (infra_read1 > cali_infra_preto && infra_read2 > cali_infra_preto &&
             infra_read3 < cali_infra_preto && infra_read4 < cali_infra_preto) {
    // Detecta curva de 90 para a direita
    motores.walk(vel_esquerda, -vel_direita);
    delay(delay_curva_direita);
  } else {
    // Detecta linha reta

    float erro = (((infra_read1 * 2) + infra_read2) -
                  (infra_read3 + (infra_read4 * 2))) /
                 3;

    float pid = erro * kp + (erro - erro_anterior) * kd;
    erro_anterior = erro;

    motores.walk(velocidade + pid, velocidade - pid);
  }
}

void desvia_obstaculo_direita() {
  // TODO: Desvia do obstáculo

  // Vira para a direita
  // Avança para frente
  // Vira para a esquerda
  // Avança para frente
  // Vira para a esquerda
  // Avança para frente
  // Vira para a direita
}

void desvia_obstaculo_esquerda() {
  // TODO: Desvia do obstáculo

  // Vira para a esquerda
  // Avança para frente
  // Vira para a direita
  // Avança para frente
  // Vira para a direita
  // Avança para frente
  // Vira para a esquerda
}