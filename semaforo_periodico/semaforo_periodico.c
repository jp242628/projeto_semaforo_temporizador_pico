#include <stdio.h> // Biblioteca para entrada e saída padrão
#include "pico/stdlib.h" // Biblioteca do Pico para funções padrão
#include "hardware/gpio.h" // Biblioteca do Pico para controle dos pinos GPIO
#include "hardware/timer.h" // Biblioteca do Pico para controle dos temporizadores

// Definição dos pinos dos LEDs
#define LED_VERMELHO_PIN 11 // Pino GP11 (LED vermelho)
#define LED_AMARELO_PIN 12 // Pino GP12 (LED amarelo)
#define LED_VERDE_PIN 13 // Pino GP13 (LED verde)

// Variáveis globais para controle do estado do semáforo
volatile uint8_t estado_semaforo = 0; // 0: vermelho, 1: amarelo, 2: verde

// Função de callback para o temporizador periódico
bool callback_temporizador_repetitivo(struct repeating_timer *t) {
    switch (estado_semaforo) {
        case 0:
            // Estado vermelho: apaga vermelho, acende amarelo
            gpio_put(LED_VERMELHO_PIN, 0); // LED vermelho apagado
            gpio_put(LED_AMARELO_PIN, 1); // LED amarelo aceso
            gpio_put(LED_VERDE_PIN, 0); // LED verde apagado
            estado_semaforo = 1; // Próximo estado é amarelo
            break;
        case 1:
            // Estado amarelo: apaga amarelo, acende verde
            gpio_put(LED_VERMELHO_PIN, 0); // LED vermelho apagado
            gpio_put(LED_AMARELO_PIN, 0); // LED amarelo apagado
            gpio_put(LED_VERDE_PIN, 1); // LED verde aceso
            estado_semaforo = 2; // Próximo estado é verde
            break;
        case 2:
            // Estado verde: apaga verde, acende vermelho
            gpio_put(LED_VERMELHO_PIN, 1); // LED vermelho aceso
            gpio_put(LED_AMARELO_PIN, 0); // LED amarelo apagado
            gpio_put(LED_VERDE_PIN, 0); // LED verde apagado
            estado_semaforo = 0; // Próximo estado é vermelho
            break;
    }
    return true; // Continua o temporizador
}

int main() {
    // Inicialização do SDK
    stdio_init_all();

    // Configuração dos pinos dos LEDs como saída
    gpio_init(LED_VERMELHO_PIN); // Inicializa o pino do LED vermelho
    gpio_init(LED_AMARELO_PIN); // Inicializa o pino do LED amarelo
    gpio_init(LED_VERDE_PIN); // Inicializa o pino do LED verde
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT); // Configura o pino do LED vermelho como saída
    gpio_set_dir(LED_AMARELO_PIN, GPIO_OUT); // Configura o pino do LED amarelo como saída
    gpio_set_dir(LED_VERDE_PIN, GPIO_OUT);  // Configura o pino do LED verde como saída

    // Inicializa o semáforo com o LED vermelho aceso
    gpio_put(LED_VERMELHO_PIN, 1); // LED vermelho aceso
    gpio_put(LED_AMARELO_PIN, 0); // LED amarelo apagado
    gpio_put(LED_VERDE_PIN, 0); // LED verde apagado

    // Configuração do temporizador periódico
    struct repeating_timer temporizador; // Estrutura para armazenar o temporizador
    add_repeating_timer_ms(3000, callback_temporizador_repetitivo, NULL, &temporizador); // Temporizador de 3 segundos

    // Loop infinito
    while (true) {
        // Imprime uma mensagem a cada segundo
        printf("Estado do semáforo: %d\n", estado_semaforo); // 0: vermelho, 1: amarelo, 2: verde
        sleep_ms(1000); // Aguarda 1 segundo
    }
}