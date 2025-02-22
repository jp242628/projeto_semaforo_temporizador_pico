# Projeto de Controle de LEDs com Temporizador e Botão

Este projeto implementa um controle de LEDs utilizando um temporizador e um botão em uma placa Pico W. O código foi desenvolvido em C e utiliza as bibliotecas padrão do Pico W para manipulação de GPIO e temporizadores.

## Funcionamento

1. **Clique no botão (pushbutton):**
   - Os três LEDs serão ligados.
   - A partir da primeira rotina de atraso, ocorrerá uma mudança de estado para dois LEDs ligados e, em seguida, apenas um.

2. **Temporizador do alarme:**
   - Ajustado para um atraso de 3 segundos (3.000ms) entre os estados de acionamento dos LEDs.

3. **Mudança de estado dos LEDs:**
   - Implementada em funções de callback do temporizador.

4. **Botão:**
   - Só pode alterar o estado dos LEDs quando o último LED for desligado.
   - Durante a execução das rotinas de temporização, o botão não pode iniciar uma nova chamada da função callback.

5. **Debounce do botão:**
   - Implementada uma rotina em software para atenuação do efeito bouncing no botão.

   ## Instruções de Uso

   ### Configuração do Hardware

   1. Conecte os LEDs aos pinos GPIO 11, 12 e 13 da placa Pico W.
   2. Conecte o botão ao pino GPIO 5 da placa Pico W.

   ### Compilação e Upload

   1. **Clone o repositório:**
      ```sh
      git clone https://github.com/jp242628/projeto_semaforo_temporizador_pico.git
      ```

   2. **Navegue até o diretório do projeto:**
      ```sh
      cd temporizador_leds_botao
      ```

   3. **Compile e carregue o código no Raspberry Pi Pico W utilizando o ambiente de desenvolvimento de sua preferência.**

   ### Execução

   1. Pressione o botão conectado ao GPIO 5.
   2. Observe que todos os LEDs acendem inicialmente.
   3. Após 3 segundos, o LED azul (GPIO 11) apaga.
   4. Após mais 3 segundos, o LED vermelho (GPIO 12) apaga.
   5. Após mais 3 segundos, o LED verde (GPIO 13) apaga.
   6. Durante a sequência, o botão não pode iniciar uma nova chamada da função callback.
   7. Após a sequência, o botão pode ser pressionado novamente para reiniciar o ciclo.

## Código Fonte

O código com a função principal está em `temporizador_leds_botao.c`.