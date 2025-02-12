#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/pwm.h"

#define PWM_PIN 22 // Pino 22 para ServoMotor
#define LED_PIN 12 // Pino 12 para LED
#define F_PWM 50 // Frequência de 50Hz
#define DUTY_CYCLE_1 12.0 // Porcentagem do Duty Cycle
#define DUTY_CYCLE_2 7.35 // Porcentagem do Duty Cycle
#define DUTY_CYCLE_3 2.5 // Porcentagem do Duty Cycle
#define STEP 0.025 // Porcentagem de incremento ou decremento do Duty Cycle

#define WRAP 9999 // Ideal para uma precisão de até 0,01
#define CLK_DIV 250 // Divisor de Clock


#define PAUSE 5000 // Pausa de 5 segundos
#define DELAY 10 // Delay entre os incrementos ou decrementos


//Protótipos
void setup();
void set_duty_cycle(float duty_cycle);
void toggle_state();

int main()
{
    stdio_init_all();
    setup();

    while (true) { toggle_state(); }
}

void setup() {
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM); // Configura o pino como PWM
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM); // Configura o pino como PWM

    uint slice_1 = pwm_gpio_to_slice_num(PWM_PIN); // Obtém o slice do PWM
    uint slice_2 = pwm_gpio_to_slice_num(LED_PIN); // Obtém o slice do PWM

    pwm_set_clkdiv(slice_1, CLK_DIV); // Define o divisor de clock como 250
    pwm_set_clkdiv(slice_2, CLK_DIV); // Define o divisor de clock como 250

    pwm_set_wrap(slice_1, WRAP); // Define o WRAP como 9.999
    pwm_set_wrap(slice_2, WRAP); // Define o WRAP como 9.999

    pwm_set_enabled(slice_1, true); // Habilita o PWM
    pwm_set_enabled(slice_2, true); // Habilita o PWM
}


void set_duty_cycle(float duty_cycle) {
    uint16_t int_duty_cycle = (uint16_t)((duty_cycle / 100) * WRAP); 
    pwm_set_gpio_level(PWM_PIN, int_duty_cycle); // Setando Duty Cycle para ServoMotor
    pwm_set_gpio_level(LED_PIN, int_duty_cycle); // Setando Duty Cycle para LED
}

void toggle_state() {
    static int state = 0;
    static float current_duty_cycle = DUTY_CYCLE_3;

    switch (state) {
        case 0:
            set_duty_cycle(DUTY_CYCLE_1);
            state++;
            sleep_ms(PAUSE);
            break;
        case 1:
            set_duty_cycle(DUTY_CYCLE_2);
            state++;
            sleep_ms(PAUSE);
            break;
        case 2:
            set_duty_cycle(DUTY_CYCLE_3);
            state++;
            sleep_ms(PAUSE);
            break;
        case 3:
            // Verifica se o Duty Cycle atingiu 12% e muda para o estado de decremento.
            if (current_duty_cycle >= DUTY_CYCLE_1) { state++; }
            else {
                current_duty_cycle = current_duty_cycle + STEP; // Incremento no Duty Cycle
                set_duty_cycle(current_duty_cycle);
            }
            sleep_ms(DELAY);
            break;
        case 4:
            // Verifica se o Duty Cycle atingiu 2,5% e muda para o estado de incremento.
            if (current_duty_cycle <= DUTY_CYCLE_3) { state--; }
            else {
                current_duty_cycle = current_duty_cycle - STEP; // Decremento no Duty Cycle
                set_duty_cycle(current_duty_cycle);
            }
            sleep_ms(DELAY);
            break;
        default:
            break;
    }
}
