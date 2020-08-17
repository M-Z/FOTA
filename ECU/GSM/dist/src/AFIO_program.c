#include "AFIO_config.h"
#include "AFIO_init.h"
#include "AFIO_register.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

void AFIO_vidinit(void) {

  AFIO_EVCR = 0x00000000;

  AFIO_MAPR |=
      ((AFIO_SPI1CFG) | (AFIO_I2C1CFG << 1) | (AFIO_USART1CFG << 2) |
       (AFIO_USART2CFG << 3) | (AFIO_USART3CFG << 4) | (AFIO_TIM1CFG << 6) |
       (AFIO_TIM2CFG << 8) | (AFIO_TIM3CFG << 10) | (AFIO_TIM4CFG << 12) |
       (AFIO_CANCFG << 13) | (AFIO_PD01CFG << 15) | (AFIO_TIM5CFG << 16) |
       (AFIO_ADC1CFG << 17) | (AFIO_ADC1_RegularCFG << 18) |
       (AFIO_ADC2CFG << 19) | (AFIO_ADC2_RegularCFG << 20) |
       (AFIO_SWJ_CFG << 24));

  AFIO_EXTICR1 |= ((AFIO_EXTI0CFG) | (AFIO_EXTI1CFG << 4) |
                   (AFIO_EXTI2CFG << 8) | (AFIO_EXTI3CFG << 12));
  AFIO_EXTICR2 |= ((AFIO_EXTI4CFG) | (AFIO_EXTI5CFG << 4) |
                   (AFIO_EXTI6CFG << 8) | (AFIO_EXTI7CFG << 12));
  AFIO_EXTICR3 |= ((AFIO_EXTI8CFG) | (AFIO_EXTI9CFG << 4) |
                   (AFIO_EXTI10CFG << 8) | (AFIO_EXTI11CFG << 12));
  AFIO_EXTICR4 |= ((AFIO_EXTI12CFG) | (AFIO_EXTI13CFG << 4) |
                   (AFIO_EXTI14CFG << 8) | (AFIO_EXTI15CFG << 12));

  AFIO_MAPR2 |=
      ((AFIO_TIM9CFG << 5) | (AFIO_TIM10CFG << 6) | (AFIO_TIM11CFG << 7) |
       (AFIO_TIM13CFG << 8) | (AFIO_TIM14CFG << 9) | (AFIO_NADVCFG << 10));
}
