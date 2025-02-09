#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22   // GPIO do servo
#define WRAP_VALUE 20000  // Período de 20ms para 50Hz
#define CLK_DIV 64.0  // Divisor do clock para ajustar a frequência

// Função para definir a posição do servo via PWM
void set_servo_position(uint slice, uint channel, uint16_t pulse_width) {
    pwm_set_chan_level(slice, channel, pulse_width);
}

int main() {
    stdio_init_all();
    
    // Configurar GPIO 22 como saída PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    
    // Obter o slice e o canal do PWM
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    uint channel = pwm_gpio_to_channel(SERVO_PIN);

    // Configurar o PWM
    pwm_set_clkdiv(slice, CLK_DIV);  // Define o divisor do clock
    pwm_set_wrap(slice, WRAP_VALUE); // Define o valor do wrap para 20ms
    pwm_set_enabled(slice, true);    // Ativa o PWM

    while (1) {
        // Enviar o servo para 180 graus (~2400µs de pulso)
        set_servo_position(slice, channel, 2400);
        sleep_ms(500);

        // Enviar o servo para 0 graus (~500µs de pulso)
        set_servo_position(slice, channel, 500);
        sleep_ms(500);

        // Enviar o servo para 90 graus (~1470µs de pulso)
        set_servo_position(slice, channel, 1470);
        sleep_ms(500);
    }
}
