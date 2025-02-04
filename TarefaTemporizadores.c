#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição de constantes
#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13

void setup();

int main()
{
    setup();

    while(true) {
        
    }

    return 0;
}

// Inicialização e configuração das portas digitais
void setup() {
    stdio_init_all();

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
}