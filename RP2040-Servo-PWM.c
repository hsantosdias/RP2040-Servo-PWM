#include <stdio.h> // Biblioteca padrão de E/S (printf, scanf, etc.) 
#include <stdint.h> // Biblioteca para tipos inteiros (uint8_t, uint16_t, uint32_t, etc.) 
#include <stdbool.h> // Biblioteca para tipos booleanos (true, false)
#include "pico/stdlib.h" // Biblioteca padrão do Pico (necessária para usar funções de I/O) 
#include "hardware/pwm.h"

#define SERVO_PIN 22       // GPIO onde o servo está conectado
#define LED_PIN 12         // GPIO onde o LED RGB está conectado
#define PWM_FREQ 50        // Frequência do PWM em Hz (50Hz = 20ms)
#define PWM_WRAP 20000     // Período do PWM em unidades de 1µs (20ms)
#define SERVO_MIN_US 500   // Largura de pulso mínima para 0 graus (500µs)
#define SERVO_MAX_US 2400  // Largura de pulso máxima para 180 graus (2400µs)
#define DELAY_MS 10        // Atraso para movimentação suave do servo

// Função para configurar o PWM no pino especificado
void pwm_setup(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    pwm_set_clkdiv(slice, 125.0f); // Divisor de clock para 1MHz (125MHz / 125 = 1MHz)
    pwm_set_wrap(slice, PWM_WRAP - 1); // Define o período do PWM
    pwm_set_enabled(slice, true);  // Habilita o PWM
}

// Função para definir a posição do servo em graus
void set_servo_angle(uint gpio, uint angle) {
    if (angle > 180) angle = 180; // Garante que o ângulo não passe de 180°
    uint pulse_us = SERVO_MIN_US + ((SERVO_MAX_US - SERVO_MIN_US) * angle) / 180;
    uint slice = pwm_gpio_to_slice_num(gpio);
    uint channel = pwm_gpio_to_channel(gpio);
    pwm_set_chan_level(slice, channel, pulse_us);
}

int main() {
    stdio_init_all(); // Inicializa a comunicação serial (USB)

    // Configura o PWM para o servo na GPIO 22
    pwm_setup(SERVO_PIN);

    // Configura o LED RGB na GPIO 12
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Movimentos iniciais do servo
    printf("Movendo o servo para 180 graus\n");
    set_servo_angle(SERVO_PIN, 180);
    gpio_put(LED_PIN, 1);
    sleep_ms(5000);

    printf("Movendo o servo para 90 graus\n");
    set_servo_angle(SERVO_PIN, 90);
    gpio_put(LED_PIN, 0);
    sleep_ms(5000);

    printf("Movendo o servo para 0 graus\n");
    set_servo_angle(SERVO_PIN, 0);
    gpio_put(LED_PIN, 1);
    sleep_ms(5000);

    // Movimentação periódica do servo entre 0 e 180 graus
    printf("Iniciando movimentação periódica do servo\n");
    while (true) {
        sleep_ms(1000);
    }

    return 0;
}
