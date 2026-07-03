# Robô Paragon - Modelo OBR

Código de exemplo de um robô feito pelos instrutores do projeto.

## main.ino

Código principal do robô.

O código é organizado em etapas bem definidas para evitar confusão e permitir edições rápidas ao saber onde procurar cada funcionalidade.

No topo, priorizamos as variáveis editadas com mais frequência. Pois assim diminuimos a chance de confusão ao editar o código.

1. Definição de variáveis
  1.1. Definição de variáveis de calibração (vão ser copiadas do código de calibração à cada corrida na pista).
  1.2. Definição de variáveis para ajuste manual (vão ser ajustadas manualmente de forma corriqueira).
  1.3. Definição dos pinos conectados no Arduino (esses são alterados com menos frequência, somente quando a eletrônica é alterada).
  1.4. Definição de variáveis globais atualizadas apenas pelo código, sem ajustes manuais.
2. Setup (Inicialização dos componentes - padrão do Arduino)
  2.1. Inicialização dos componentes eletrônicos (motores, sensores, etc.).
  2.2. Armazena calibração dos sensores de cor.
3. Loop principal (Estrutura de controle do robô)
  3.1. Detecta obstáculos com o ultrassom.
  3.2. Detecta linha preta com os sensores infravermelhos de forma condicional.
  3.3. Detecta encruzilhadas.
    3.3.1. Detecta marcação verde com os sensores de cor para saber qual caminho tomar.
  3.4. Detecta curvas simples.
  3.5. Detecta linha reta com o controlador PID.

## calibration.ino

Código para calibrar os sensores.