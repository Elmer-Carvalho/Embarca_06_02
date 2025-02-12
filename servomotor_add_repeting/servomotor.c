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
struct repeating_timer timer;
void setup();
void set_duty_cycle(float duty_cycle);
bool toggle_state(repeating_timer_t *timer);

int main()
{
    stdio_init_all();
    setup();

    add_repeating_timer_ms(DELAY, toggle_state, NULL, &timer);

    while (true) {}
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

bool toggle_state(repeating_timer_t *timer) {
    static int state = 0;
    static float current_duty_cycle = DUTY_CYCLE_3;

    cancel_repeating_timer(timer); // Cancela qualquer timer anterior antes de criar um novo

    switch (state) {
        case 0:
            set_duty_cycle(DUTY_CYCLE_1);
            state++;
            add_repeating_timer_ms(PAUSE, toggle_state, NULL, timer);
            break;
        case 1:
            set_duty_cycle(DUTY_CYCLE_2);
            state++;
            add_repeating_timer_ms(PAUSE, toggle_state, NULL, timer);
            break;
        case 2:
            set_duty_cycle(DUTY_CYCLE_3);
            state++;
            add_repeating_timer_ms(PAUSE, toggle_state, NULL, timer);
            break;
        case 3:
            if (current_duty_cycle >= DUTY_CYCLE_1) { state++; }  // Verifica se o Duty Cycle atingiu 12% e muda para o estado de decremento
            else {
                current_duty_cycle = current_duty_cycle + STEP; // Incremento no Duty Cycle
                set_duty_cycle(current_duty_cycle);
            }
            add_repeating_timer_ms(DELAY, toggle_state, NULL, timer);
            break;

        case 4:
            if (current_duty_cycle <= DUTY_CYCLE_3) { state--; }  // Verifica se o Duty Cycle atingiu 2,5% e muda para o estado de incremento.
            else {
                current_duty_cycle = current_duty_cycle - STEP; // Decremento no Duty Cycle
                set_duty_cycle(current_duty_cycle);
            }
            add_repeating_timer_ms(DELAY, toggle_state, NULL, timer);
            break;
        default:
            break;
    }
    return true;
}
