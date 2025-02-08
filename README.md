# RP2040-Servo-PWM

## Descrição do Projeto

Este projeto implementa o controle de um **servomotor** utilizando **Modulação por Largura de Pulso (PWM)** no microcontrolador **RP2040**. O código é desenvolvido em **C**, utilizando o **Pico SDK**, e testado no simulador **Wokwi**.

Além do controle de posição do servo entre **0°**, **90°** e **180°**, o projeto também inclui um experimento com a **BitDogLab**, onde um **LED RGB** será analisado para entender os efeitos do PWM na intensidade luminosa.

---

## Requisitos para este projeto

Para rodar este projeto, você precisará de:

- **Microcontrolador**: Raspberry Pi Pico W (simulado no Wokwi)
- **Ambiente de Desenvolvimento**: VS Code + Pico SDK
- **Linguagem**: C
- **Compilador**: arm-none-eabi-gcc
- **Simulador**: Wokwi
- **Bibliotecas**:
  - `pico/stdlib.h` – Funções padrão do Pico SDK
  - `hardware/pwm.h` – Controle do módulo PWM do RP2040

---

## Instalação e Uso

1. **Clone o repositório**

   ```bash
   git clone https://github.com/hsantosdias/RP2040-Servo-PWM.git
   cd RP2040-Servo-PWM
   ```
2. **Compile e envie para o RP2040 utilizando o VS Code + Pico SDK.**


3. **Execute no simulador Wokwi**

   - Abra [Wokwi](https://wokwi.com)
   - Faça upload do código-fonte
   - Execute a simulação e observe o movimento do servomotor
4. **Experimento com LED RGB**

   - Após rodar o código no **BitDogLab**, observe como o PWM altera a luminosidade do LED RGB.

---

## Configuração do PWM

O projeto utiliza o **módulo PWM** do **RP2040** com os seguintes parâmetros:

- **Frequência**: 50Hz *(Período de 20ms)*
- **Ciclo de trabalho** para posições do servo:
  - **180°** → 2400µs (12%)
  - **90°** → 1470µs (7.35%)
  - **0°** → 500µs (2.5%)
- **Movimentação suave**: Incrementos de **±5µs** a cada **10ms**

---

## Estrutura do Código

```
RP2040-Servo-PWM

├── RP2040-Servo-PWM.c
├── CMakeLists.txt
├── wokwi.toml
├── README.md
├── .gitignore
```

---

## Resultados

### Simulação no Wokwi

A simulação no **Wokwi** demonstra a movimentação do **servomotor** entre **0°**, **90°** e **180°**, respeitando os tempos de espera configurados.

### Experimento com LED RGB

Na **BitDogLab**, deve-se observar que a variação do **Duty Cycle** do **PWM** alterará  diretamente a intensidade luminosa do LED RGB, demonstrando a relação entre **PWM e potência fornecida**.

---

## Link do Vídeo

