#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22  // GPIO do RP2040 onde o servo está conectado
#define PWM_FREQ 50   // Frequência do PWM para controle do servo
#define WRAP_VALUE 20000  // Valor do período (20ms) para 50Hz

void set_servo_position(uint slice, uint channel, uint16_t pulse_width) {
    pwm_set_chan_level(slice, channel, pulse_width);
}

int main() {
    stdio_init_all();
    
    // Configurar o pino como saída PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    
    // Obter o slice do PWM
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    uint channel = pwm_gpio_to_channel(SERVO_PIN);

    // Configurar o PWM para 50Hz
    pwm_set_clkdiv(slice, 64.0);  // Define o divisor do clock
    pwm_set_wrap(slice, WRAP_VALUE);  // Define o valor do wrap (20ms)
    pwm_set_enabled(slice, true);  // Ativa o PWM
    
    // Define o servo para -90 graus (~500µs de pulso)
    set_servo_position(slice, channel, 500);

    while (1) {
        // Define o servo para 0 graus (~1500µs de pulso)
        set_servo_position(slice, channel, 1500);
        
        sleep_ms(1000); // Mantém o programa rodando
    }
}
