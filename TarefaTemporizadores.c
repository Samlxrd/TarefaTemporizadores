#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição de constantes
#define LED_RED 13
#define LED_BLUE 12
#define LED_GREEN 11
#define BUTTON 5

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

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

}