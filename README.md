# RP2040-Servo-PWM

## Descrição do Projeto

Este projeto implementa o controle de um **servomotor** utilizando **Modulação por Largura de Pulso (PWM)** no microcontrolador **RP2040**. O código é desenvolvido em **C**, utilizando o **Pico SDK**, e testado no simulador **Wokwi**.

Além do controle de posição do servo entre **0°**, **90°** e **180°**, o projeto também inclui um experimento com a **BitDogLab**, onde um **LED RGB** será analisado para entender os efeitos do PWM na intensidade luminosa. O brilho do LED diminui à medida que o ângulo do servo aumenta e aumenta quando o ângulo diminui.

---

## Configuração do Ambiente Instalação e Uso


1. **Instale o SDK do Raspberry Pi Pico:**

   - Siga o guia oficial para configuração: [Guia do Raspberry Pi Pico](https://www.raspberrypi.com/documentation/microcontrollers/)
2. **Clone o repositório do projeto:**

   ```bash
   git clone https://github.com/hsantosdias/RP2040-Servo-PWM.git
   cd RP2040-Servo-PWM
   ```
3. **Compile o código:**

   - Certifique-se de que o SDK está instalado e funcionando corretamente no VSCode.

   ```bash
   Usando a extensão do Raspberry `Pi Pico Visual Studio Code extension`
   Siga os seguintes passos:
   1. Clean CMake (Para garantir que o projetos sera compilado do zero)
   2. Compile Project (Compilação dos binarios)
   3. Run Project [USB] (Compila e copia o firmaware para placa automaticamente)
   ```
4. **Carregue o binário no Pico:**

   - Conecte o Pico ao computador no modo bootloader.
   - Copie o arquivo `.uf2` (Depois de compilado, copiar o ./build/RP2040-Servo-PWM.uf2  para a Raspberry em modo bootsel).

5. **Execute no simulador Wokwi**

   - Abra [Simulador Wokwi](https://wokwi.com/projects/422365413208901633 "ACesso ao simulador")
   - Faça upload do código-fonte
   - Execute a simulação e observe o movimento do servomotor

6. **Experimento com LED RGB**

   - Após rodar o código no **BitDogLab**, observe como o PWM altera a luminosidade do LED RGB de acordo com o ângulo do servo.



## Funcionalidades Implementadas

* **Controle de Servo Motor**: Movimento entre 0°, 90° e 180°.
* **Movimento Suave**: A movimentação do servo ocorre gradualmente para simular um comportamento realista.
* **Controle de LED RGB**: O brilho do LED varia de acordo com o ângulo do servo.
* **Loop Contínuo**: Após os movimentos iniciais, o servo oscila continuamente entre 0° e 180°.

---

## Requisitos do Projeto

Os requisitos definidos para esta atividade são:

1) **Configuração do PWM**:

   - Definir a frequência do PWM em **50Hz** *(período de 20ms)* na **GPIO 22**.
   - Configurar o ciclo ativo do PWM para movimentar o servomotor corretamente.
2) **Movimentação Inicial**:

   - **180°** → Pulso de **2400µs** (12% Duty Cycle). Aguardar **5 segundos**.
   - **90°** → Pulso de **1470µs** (7.35% Duty Cycle). Aguardar **5 segundos**.
   - **0°** → Pulso de **500µs** (2.5% Duty Cycle). Aguardar **5 segundos**.
3) **Movimentação Periódica**:

   - Criar uma rotina que movimente o servo entre **0° e 180°** de forma **suave**, com incrementos de **±5µs** e um atraso de **10ms** entre ajustes.
4) **Experimento com LED RGB**:

   - Implementar um **controle de brilho** no **LED RGB (GPIO 12)** baseado na posição do servo.
   - **Quanto maior o ângulo do servo, menor o brilho do LED**.
   - **Quanto menor o ângulo do servo, maior o brilho do LED**.

## Requisitos Atingidos

### Requisito 1 - Frequência de PWM para 50Hz (Período de 20ms)

```
#define PWM_FREQ 50        // Frequência do PWM em Hz (50Hz = 20ms)
#define PWM_WRAP 20000     // Período do PWM em unidades de 1µs (20ms)
```

### **Requisito 2 - Servo para 180° (2400µs) e aguardar 5s**

```
printf("Movendo o servo para 180 graus\n");
set_servo_angle(SERVO_PIN, 180);
set_led_brightness(LED_PIN, 200); // Brilho máximo
sleep_ms(5000);
```

### **Requisito 3 - Servo para 90° (1470µs) e aguardar 5s**

```
printf("Movendo o servo para 90 graus\n");
set_servo_angle(SERVO_PIN, 90);
set_led_brightness(LED_PIN, 0); // Brilho mínimo
sleep_ms(5000);
```

### Requisito 4 - Servo para 0° (500µs) e aguardar 5s

```
printf("Movendo o servo para 0 graus\n");
set_servo_angle(SERVO_PIN, 0);
set_led_brightness(LED_PIN, 100); // Brilho médio
sleep_ms(5000);
```

### **Requisito 5 - Movimentação periódica do servo entre 0° e 180° (movimento suave)**

```
while (true) {
    for (uint angle = 0; angle <= 180; angle++) {
        set_servo_angle(SERVO_PIN, angle);
        set_led_brightness(LED_PIN, ((180 - angle) * PWM_WRAP) / 180); // Diminui brilho conforme ângulo aumenta
        sleep_ms(DELAY_MS);
    }
    for (uint angle = 180; angle > 0; angle--) {
        set_servo_angle(SERVO_PIN, angle);
        set_led_brightness(LED_PIN, ((180 - angle) * PWM_WRAP) / 180); // Aumenta brilho conforme ângulo diminui
        sleep_ms(DELAY_MS);
    }
}
```

### Requisito 6 - Experimento com LED RGB na BitDogLab

```
void set_led_brightness(uint gpio, uint brightness) {
    uint slice = pwm_gpio_to_slice_num(gpio);
    uint channel = pwm_gpio_to_channel(gpio);
    pwm_set_chan_level(slice, channel, brightness);
}
```

> E no  **loop principal** , o LED  **brilha mais quando o servo está em 0° e escurece em 180°** ,  **demonstrando o efeito do PWM no LED** .

---

## Configuração do PWM

O projeto utiliza o **módulo PWM** do **RP2040** com os seguintes parâmetros:

- **Frequência**: 50Hz *(Período de 20ms)*
- **Ciclo de trabalho** para posições do servo:
  - **180°** → 2400µs (12%)
  - **90°** → 1470µs (7.35%)
  - **0°** → 500µs (2.5%)
- **Movimentação suave**: Incrementos de **±1°** a cada **10ms**

---

## Estrutura do Código

```
RP2040-Servo-PWM
├── build/                   # Diretório para compilação
├── RP2040-Servo-PWM.c       # Código-fonte principal
├── CMakeLists.txt           # Configuração do CMake
├── wokwi.toml               # Configuração para simulação no Wokwi
├── diagram.json             # Fluxograma do projeto
├── README.md                # Documentação do projeto
├── pico_sdk_import.cmake    # Configuração do SDK
```

---

## Resultados

### Simulação no Wokwi

A simulação no **Wokwi** demonstra a movimentação do **servomotor** entre **0°**, **90°** e **180°**, respeitando os tempos de espera configurados. O brilho do LED RGB é ajustado de acordo com o ângulo do servo.

- Abra [Simulador Wokwi](https://wokwi.com/projects/422365413208901633 "ACesso ao simulador")

### Experimento com LED RGB

Na **BitDogLab**, deve-se observar que a variação do **Duty Cycle** do **PWM** altera diretamente a intensidade luminosa do LED RGB, demonstrando a relação entre **PWM e potência fornecida**.

---

## Dificuldades Encontradas

Durante o desenvolvimento, alguns desafios surgiram e foram superados:

1. **Configuração precisa do PWM**: Garantir que o período do PWM fosse **exatamente 20ms (50Hz)** para compatibilidade com o servo.
2. **Controle preciso do servo motor**: Ajustar os pulsos de PWM para garantir que o servo se movesse corretamente foi desafiador.
3. **Variação de brilho do LED**: Ajustar corretamente o **PWM do LED RGB** para sincronizar com o movimento do servo exigiu calibração.
4. **Configuração do ambiente de desenvolvimento**: Configurar corretamente o **Pico SDK** e o compilador **arm-none-eabi-gcc** levou algum tempo para evitar erros de compilação.

---

## Link do Vídeo

