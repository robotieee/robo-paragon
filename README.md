# Robô Paragon - Modelo OBR

Código de exemplo de um robô feito pelos instrutores do projeto.

## principal.ino

Código principal do robô.

O código é organizado em etapas bem definidas para evitar confusão e permitir edições rápidas ao saber onde procurar cada funcionalidade.

No topo, priorizamos as variáveis editadas com mais frequência. Pois assim diminuimos a chance de confusão ao editar o código.

1. Definição de variáveis
  - Definição de variáveis de calibração (vão ser copiadas do código de calibração à cada corrida na pista).
  - Definição de variáveis para ajuste manual (vão ser ajustadas manualmente de forma corriqueira).
  - Definição dos pinos conectados no Arduino (esses são alterados com menos frequência, somente quando a eletrônica é alterada).
  - Definição de variáveis globais atualizadas apenas pelo código, sem ajustes manuais.
2. Setup (Inicialização dos componentes - padrão do Arduino)
  - Inicialização dos componentes eletrônicos (motores, sensores, etc.).
  - Armazena calibração dos sensores de cor.
3. Loop principal (Estrutura de controle do robô)
  - Detecta obstáculos com o ultrassom.
  - Detecta linha preta com os sensores infravermelhos de forma condicional.
  - Detecta encruzilhadas.
    - Detecta marcação verde com os sensores de cor para saber qual caminho tomar.
  - Detecta curvas simples.
  - Detecta linha reta com o controlador PID.

## calibrar.ino

Código para calibrar os sensores.