#include <stdio.h> // Inclui a biblioteca padrão do C
#include "pico/stdlib.h" // Inclui a biblioteca de funções do Pico
#include "hardware/gpio.h" // Inclui a biblioteca de funções de GPIO
#include "hardware/timer.h" // Inclui a biblioteca de funções de temporizador

// Definição dos pinos
#define BOTAO_PIN 5 // Pino do botão
#define LED1_PIN 11 // Pino do LED 1 azul
#define LED2_PIN 12 // Pino do LED 2 vermelho
#define LED3_PIN 13 // Pino do LED 3 verde

// Variáveis globais para controle do estado
volatile bool botao_pressionado = false; // Variável de controle do botão
volatile bool temporizador_rodando = false; // Variável de controle do temporizador
volatile uint8_t estado = 0; // Variável de controle do estado

// Função de callback para o alarme (temporizador)
int64_t alarme_callback(alarm_id_t id, void *user_data) {
    printf("Estado atual: %d\n", estado); // Mensagem de depuração
    switch (estado) {
        case 0:
            // Primeiro estado: apaga o LED azul (LED1)
            gpio_put(LED1_PIN, 0); // Apaga o LED azul
            gpio_put(LED2_PIN, 1); // Mantém o LED vermelho aceso
            gpio_put(LED3_PIN, 1); // Mantém o LED verde aceso
            estado = 1; // Atualiza o estado
            break;
        case 1:
            // Segundo estado: apaga o LED vermelho (LED2)
            gpio_put(LED1_PIN, 0); // Mantém o LED azul apagado
            gpio_put(LED2_PIN, 0); // Apaga o LED vermelho
            gpio_put(LED3_PIN, 1); // Mantém o LED verde aceso
            estado = 2; // Atualiza o estado
            break;
        case 2:
            // Terceiro estado: apaga o LED verde (LED3)
            gpio_put(LED1_PIN, 0); // Mantém o LED azul apagado
            gpio_put(LED2_PIN, 0); // Mantém o LED vermelho apagado
            gpio_put(LED3_PIN, 0); // Apaga o LED verde
            estado = 0; // Volta para o primeiro estado
            temporizador_rodando = false; // Finaliza a sequência
            break;
    }

    // Configura um novo alarme para 3 segundos, se necessário
    if (temporizador_rodando) {
        add_alarm_in_ms(3000, alarme_callback, NULL, false); // Configura o alarme para 3 segundos
    }

    return 0; // Retorna 0 para parar o alarme atual
}

// Função de callback para o botão
void botao_callback(uint gpio, uint32_t events) {
    // Verifica se o botão foi pressionado e o temporizador não está rodando
    if (!temporizador_rodando && gpio == BOTAO_PIN) {
        botao_pressionado = true; // Atualiza a variável de controle
    }
}

// Função para debounce do botão
bool debounce_botao() {
    static uint32_t ultima_vez = 0; // Variável estática para armazenar o tempo da última vez
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time()); // Obtém o tempo atual em ms

    // Verifica se o tempo atual é maior que o tempo da última vez + 50ms
    if (tempo_atual - ultima_vez > 50) { // 50ms debounce time
        ultima_vez = tempo_atual; // Atualiza o tempo da última vez
        return true; // Retorna verdadeiro
    }
    return false; // Retorna falso
}

int main() {
    // Inicialização do SDK
    stdio_init_all();

    // Configuração dos pinos dos LEDs como saída
    gpio_init(LED1_PIN); // Inicializa o pino do LED azul
    gpio_init(LED2_PIN); // Inicializa o pino do LED vermelho
    gpio_init(LED3_PIN); // Inicializa o pino do LED verde
    gpio_set_dir(LED1_PIN, GPIO_OUT); // Configura o pino do LED azul como saída
    gpio_set_dir(LED2_PIN, GPIO_OUT); // Configura o pino do LED vermelho como saída
    gpio_set_dir(LED3_PIN, GPIO_OUT); // Configura o pino do LED verde como saída

    // Configuração do pino do botão como entrada
    gpio_init(BOTAO_PIN); // Inicializa o pino do botão
    gpio_set_dir(BOTAO_PIN, GPIO_IN); // Configura o pino do botão como entrada
    gpio_pull_up(BOTAO_PIN); // Habilita o resistor de pull-up interno

    // Configuração da interrupção do botão
    gpio_set_irq_enabled_with_callback(BOTAO_PIN, GPIO_IRQ_EDGE_FALL, true, &botao_callback);

    // Loop principal do programa
    while (true) {
        // Verifica se o botão foi pressionado e o temporizador não está rodando
        if (botao_pressionado && !temporizador_rodando && debounce_botao()) {
            // Inicia a sequência de temporização
            botao_pressionado = false; // Reseta a variável de controle
            temporizador_rodando = true; // Atualiza a variável de controle

            // Acende todos os LEDs inicialmente
            gpio_put(LED1_PIN, 1); // LED azul aceso
            gpio_put(LED2_PIN, 1); // LED vermelho aceso
            gpio_put(LED3_PIN, 1); // LED verde aceso

            // Configura o alarme para 3 segundos
            add_alarm_in_ms(3000, alarme_callback, NULL, false);
        }

        // Aguarda o próximo evento
        sleep_ms(100);
    }
}