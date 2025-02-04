#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição de constantes
#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13

void setup();
bool repeating_timer_callback(struct repeating_timer *t);

int main()
{
    setup();

    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback a cada 3 segundos.
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Iniciando o programa com o led vermelho aceso
    gpio_put(LED_RED, 1);

    while(true) {
        sleep_ms(1000);
        printf("Passou 1 segundo\n");
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

// Função de callback que será chamada repetidamente pelo temporizador
// O tipo bool indica que a função deve retornar verdadeiro ou falso para continuar ou parar o temporizador.
bool repeating_timer_callback(struct repeating_timer *t)
{
    if (gpio_get(LED_RED)) {
        gpio_put(LED_RED, 0);
        gpio_put(LED_GREEN, 0);
        gpio_put(LED_YELLOW, 1);
    }

    else if (gpio_get(LED_YELLOW)) {
        gpio_put(LED_RED, 0);
        gpio_put(LED_YELLOW, 0);
        gpio_put(LED_GREEN, 1);
    } 
    
    else {
        gpio_put(LED_YELLOW, 0);
        gpio_put(LED_GREEN, 0);
        gpio_put(LED_RED, 1);
    }

    printf("Altera o sinal\n");

    return true;
}