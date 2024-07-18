Example: bare-metal_app_template_nucleo-f401re

 Description:
 Bare Metal - Event-Triggered Systems (ETS)
 App - retarget_printf_to_Console
 Project for STM32 Project (STM32CubeIDE Version: 1.14.1)

  SystemCoreClock     => 84MHz (11.90476nS)
  SysTick Rate Hertz  => 1000 ticks per second (1mS)

  app.c (app.h)
   Endless loops, which execute tasks with fixed computing time. This 
   sequential execution is only deviated from when an interrupt event occurs.

  logger.h (logger.c)
   Utilities for Retarget "printf" to Console

  dwt.h
   Utilities for Mesure "clock cycle" and "execution time" of code
  
  Special connection requirements:
   There are no special connection requirements for this example.

Build procedures:
Visit the Getting started with STM32: STM32 step-by-step at 
"https://wiki.st.com/stm32mcu/wiki/STM32StepByStep:Getting_started_with_STM32_:_STM32_step_by_step"
to get started building STM32 Projects.