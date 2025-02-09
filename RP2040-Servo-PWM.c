#include <stdio.h> // Biblioteca padrão de E/S (printf, scanf, etc.)  
#include <stdint.h> // Biblioteca para tipos inteiros (uint8_t, uint16_t, uint32_t, etc.) 
#include <stdbool.h> // Biblioteca para tipos booleanos (true, false) 
#include "pico/stdlib.h" // Biblioteca padrão do Pico (necessária para usar funções de I/O) 
#include "hardware/pwm.h" // Biblioteca para controle de PWM (necessária para usar funções de PWM) 

#define SERVO_PIN 20       // GPIO onde o servo está conectado 
#define LED_PIN 12         // GPIO onde o LED RGB está conectado
#define PWM_FREQ 50        // Frequência do PWM em Hz (50Hz = 20ms)
#define PWM_WRAP 20000     // Período do PWM em unidades de 1µs (20ms)
#define SERVO_MIN_US 500   // Largura de pulso mínima para 0 graus (500µs)
#define SERVO_MAX_US 2400  // Largura de pulso máxima para 180 graus (2400µs)
#define DELAY_MS 15        // Atraso para movimentação suave do servo (10ms)

// Função para configurar o PWM no pino especificado
void pwm_setup(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM); // Define a função do pino como PWM (hardware)
    uint slice = pwm_gpio_to_slice_num(gpio); // Obtém o número do slice do PWM para o pino especificado
    pwm_set_clkdiv(slice, 125.0f); // Divisor de clock para 1MHz (125MHz / 125 = 1MHz) 
    pwm_set_wrap(slice, PWM_WRAP - 1); // Define o período do PWM (20ms) 
    pwm_set_enabled(slice, true);  // Habilita o PWM no slice especificado 
}

// Função para definir a posição do servo em graus
void set_servo_angle(uint gpio, uint angle) {
    if (angle > 180) angle = 180; // Garante que o ângulo não passe de 180°
    if (angle < 0) angle = 0;     // Garante que o ângulo não seja negativo
    // Calcula a largura de pulso em microssegundos (500µs a 2400µs para 0° a 180°)
    uint pulse_us = SERVO_MIN_US + ((SERVO_MAX_US - SERVO_MIN_US) * angle) / 180;
    // Define a largura de pulso para o servo na GPIO especificada 
    uint slice = pwm_gpio_to_slice_num(gpio);
    // Obtém o canal do PWM para a GPIO especificada 
    uint channel = pwm_gpio_to_channel(gpio);
    // Define o nível do canal do PWM para a largura de pulso calculada
    pwm_set_chan_level(slice, channel, pulse_us);
}

// Função para definir o brilho do LED RGB (0-255)
void set_led_brightness(uint gpio, uint brightness) {
    // Define o nível do canal do PWM para o brilho especificado (0-255)
    uint slice = pwm_gpio_to_slice_num(gpio);
    // Obtém o canal do PWM para a GPIO especificada
    uint channel = pwm_gpio_to_channel(gpio);
    // Define o nível do canal do PWM para o brilho especificado (0-255)
    pwm_set_chan_level(slice, channel, brightness);
}

// Função principal do programa 
int main() {

    stdio_init_all(); // Inicializa a comunicação serial (USB) para depuração

    // Configura o PWM para o led na GPIO 12    
    pwm_setup(LED_PIN);  // Configura o LED como PWM na GPIO 12
    // Configura o PWM para o servo na GPIO 20 
    pwm_setup(SERVO_PIN);

    // Movimentos iniciais do servo e do LED RGB
    printf("Movendo o servo para 180 graus\n");
    // Define a posição do servo para 180 graus
    set_servo_angle(SERVO_PIN, 180);
    // Define o brilho do LED RGB para 200 (máximo)
    set_led_brightness(LED_PIN, 200); // Brilho máximo
    sleep_ms(5000); // Atraso de 5 segundos

    // Movimentos iniciais do servo e do LED RGB
    printf("Movendo o servo para 90 graus\n");
    set_servo_angle(SERVO_PIN, 90); // Define a posição do servo para 90 graus
    set_led_brightness(LED_PIN, 0); // Brilho mínimo (LED desligado)
    sleep_ms(5000); // Atraso de 5 segundos

    // Movimentos iniciais do servo e do LED RGB 
    printf("Movendo o servo para 0 graus\n");
    set_servo_angle(SERVO_PIN, 0); // Define a posição do servo para 0 graus
    set_led_brightness(LED_PIN, 100); // Brilho máximo 
    sleep_ms(5000); // Atraso de 5 segundos

    // Movimentação periódica do servo entre 0 e 180 graus
    printf("Iniciando movimentação periódica do servo\n");
 
    // Loop infinito para movimentação periódica do servo entre 0 e 180 graus 
    while (true) {
        for (uint angle = 0; angle <= 180; angle++) {
            // Define a posição do servo para o ângulo atual
            set_servo_angle(SERVO_PIN, angle);
            // Define o brilho do LED RGB conforme o ângulo do servo (0-180)
            set_led_brightness(LED_PIN, ((180 - angle) * PWM_WRAP) / 180); // Diminui brilho conforme ângulo aumenta
            sleep_ms(DELAY_MS);
        }
        for (uint angle = 180; angle > 0; angle--) {
            // Define a posição do servo para o ângulo atual
            set_servo_angle(SERVO_PIN, angle);
            // Define o brilho do LED RGB conforme o ângulo do servo (0-180)
            set_led_brightness(LED_PIN, ((180 - angle) * PWM_WRAP) / 180); // Aumenta brilho conforme ângulo diminui
            sleep_ms(DELAY_MS);
        }
    }

    return 0;
}
