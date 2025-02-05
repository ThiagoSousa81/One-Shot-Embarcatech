#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

/*
|============================================|
|                                            |
|               ThiagoSousa81                |
|      https://github.com/thiagosousa81      |
|                                            |
|============================================|
*/

// Usei o vídeo de exemplo para o funcionamento do código
// https://www.dropbox.com/scl/fi/7faa7ib6bjrxncr2dxnf7/2025-01-26-14-01-54.mkv?rlkey=wqvef7zpxpuwvz2joj6qucasd&dl=0

const uint LED_GREEN_PIN = 13;  // Define o pino GPIO 11 para o LED verde.
const uint LED_BLUE_PIN = 11;   // Define o pino GPIO 12 para o LED azul.
const uint LED_RED_PIN = 12;    // Define o pino GPIO 13 para o LED vermelho.
const uint BUTTON_PIN = 5;       // Define o pino GPIO 5 para ler o estado do botão.

bool led_active = false;         // Indica se os LEDs estão atualmente acesos.
int led_state = 0;               // Indica o estado atual dos LEDs (0: todos acesos, 1: verde e vermelho, 2: apenas verde).

// Função de callback para mudar o estado dos LEDs.
int64_t led_state_callback(alarm_id_t id, void *user_data) {
    switch (led_state) {
        case 0: // Todos os LEDs acesos
            gpio_put(LED_GREEN_PIN, true);
            gpio_put(LED_BLUE_PIN, true);
            gpio_put(LED_RED_PIN, true);
            led_state++; // Próximo estado
            break;
        case 1: // Desliga o LED azul
            gpio_put(LED_BLUE_PIN, false);
            led_state++; // Próximo estado
            break;
        case 2: // Desliga o LED vermelho
            gpio_put(LED_RED_PIN, false);
            led_state++; // Próximo estado
            break;
        case 3: // Desliga o LED verde
            gpio_put(LED_GREEN_PIN, false);
            led_active = false; // Todos os LEDs estão desligados
            return 0; // Para não repetir o alarme
    }
    
    // Agenda o próximo estado após 3 segundos (3000 ms).
    add_alarm_in_ms(3000, led_state_callback, NULL, false);
    return 0; // Para não repetir o alarme
}

int main() {
    stdio_init_all();

    // Configura os pinos dos LEDs como saída digital.
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_init(LED_BLUE_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);

    // Configura o pino do botão como entrada digital.
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Habilita o resistor pull-up interno.

    while (true) {
        // Verifica se o botão foi pressionado (nível baixo no pino) e se os LEDs não estão ativos.
        if (gpio_get(BUTTON_PIN) == 0 && !led_active) {
            // Adiciona um pequeno atraso para debounce.
            sleep_ms(50);

            // Verifica novamente o estado do botão após o debounce.
            if (gpio_get(BUTTON_PIN) == 0) {
                // Liga todos os LEDs e inicia a sequência.
                led_active = true; // Define que os LEDs estão ativos.
                led_state = 0; // Reseta o estado dos LEDs.
                //led_state_callback(0, NULL); // Chama a função de callback para iniciar a sequência.
                add_alarm_in_ms(3000, led_state_callback, NULL, false);
            }
        }

        // Introduz uma pequena pausa de 10 ms para reduzir o uso da CPU.
        sleep_ms(10);
    }

    // Retorno do programa para o sistema
    return 0;
}