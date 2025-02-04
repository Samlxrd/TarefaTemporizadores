#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição de constantes
#define LED_BLUE 11     // Pinos R,G,B definidos de acordo com a simulação no Wokwi, e não a placa bitdoglab.
#define LED_RED 12
#define LED_GREEN 13
#define BUTTON_PIN 5

bool led_active = 0;
bool led_on = 0;

void setup();
int64_t turn_off_callback(alarm_id_t id, void *user_data);

int main()
{
    setup();

    while(true) {
        if (!gpio_get(BUTTON_PIN) && !led_active) {
            sleep_ms(50); // Delay de 50ms para debounce

            if (!gpio_get(BUTTON_PIN)) {
                
                // Liga os 3 leds (R, G, B).
                gpio_put(LED_RED, true);
                gpio_put(LED_GREEN, true);
                gpio_put(LED_BLUE, true);

                // Define 'led_active' como true para indicar que algum LED está aceso.
                led_active = true;

                // Agenda um alarme para desligar o LED após 3 segundos (3000 ms).
                // A função 'turn_off_callback' será chamada após esse tempo.
                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            }
        }

        sleep_ms(50); // Pequeno atraso para reduzir uso de cpu 
    }

    return 0;
}

// Inicialização e configuração das portas digitais
void setup() {
    stdio_init_all();

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

}

// Função de callback para desligar o LED após o tempo programado.
int64_t turn_off_callback(alarm_id_t id, void *user_data) {

    // Desliga o led azul na primeira chamada
    if (gpio_get(LED_BLUE))
    {
        gpio_put(LED_BLUE, 0);
        return 3000000; // Atraso de 3s em microssegundos para o próximo alarme
    }

    // Desliga o led vermelho na segunda chamada
    else if (gpio_get(LED_RED))
    {
        gpio_put(LED_RED, 0);
        return 3000000; // Atraso de 3s em microssegundos para o próximo alarme
    }

    else {
    
    // Desliga o último led que está aceso, no caso, o verde.
    gpio_put(LED_GREEN, 0);

    // Atualiza o estado de 'led_active' para falso, indicando que acabou a rotina de apagar os leds.
    led_active = false;

    // Retorna 0 para indicar que o alarme não deve se repetir.
    return 0;

    }
}