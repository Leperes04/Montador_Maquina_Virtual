🛠️ Toolchain de Processamento de Sinais e Execução (Montador, Ligador e Simulador)
Este projeto consiste no desenvolvimento de um ecossistema completo para a tradução e execução de programas escritos em linguagem Assembly para uma arquitetura de processador específica. O projeto demonstra o fluxo de transformação de código humano para código de máquina e sua posterior execução em um ambiente controlado (Simulador).

🏗️ Componentes do Projeto
1. Montador (montador.cpp)
Responsável por traduzir o código Assembly para código de máquina (opcodes e endereços).

Processamento em dois passos: Realiza a leitura inicial para construção da Tabela de Símbolos (labels e endereços) e a geração subsequente do arquivo objeto.

Gerenciamento de Memória: Realiza a alocação de variáveis definidas (diretiva WORD) e o mapeamento de instruções para seus respectivos endereços.

Tradução de Mnemônicos: Converte instruções como ADD, SUB, BEQ, e registradores (R0, R1, R2) em representações numéricas prontas para o simulador.

2. Ligador (Ligador.c)
Ferramenta projetada para unificar múltiplos arquivos objeto gerados pelo montador.

Resolução de Símbolos: (Em desenvolvimento) Responsável por ajustar os endereços de memória e unir diferentes módulos de código e dados em um único executável final.

Relocação: Ajusta as referências de endereços para que o código possa ser carregado corretamente na memória.

3. Simulador (Simulador.cpp)
Ambiente de execução que emula o comportamento do hardware.

Ciclo de Instrução: Implementa a lógica de busca, decodificação e execução via um sistema de PC (Program Counter) e registradores.

Unidade Lógica e Aritmética (ULA): Suporte a operações aritméticas, movimentação de dados (MV, ST), entrada/saída (IN, OUT) e controle de fluxo (BR, BEQ, BGT, BLT).

Gerenciamento de Dados: Simula a memória de dados e a memória de instruções de forma separada.

🚀 Tecnologias e Conceitos Aplicados
Linguagens: C e C++.

Arquitetura de Computadores: Mapeamento de memória, registradores, opcodes e endereçamento.

Engenharia de Software: Manipulação de arquivos, estruturas de dados (structs), parsing de tokens e lógica de compiladores/montadores.

📋 Como funciona o fluxo?
1. O código Assembly é escrito em um arquivo de texto.

2. O Montador lê o código, gera a tabela de labels e exporta um arquivo numérico (saidaCerta.txt).

3. O Simulador carrega esse arquivo para a memória virtual e executa as instruções passo a passo, exibindo os estados dos registradores e os resultados na saída padrão.
