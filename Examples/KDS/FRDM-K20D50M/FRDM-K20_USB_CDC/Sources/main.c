/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-K20_USB_CDC
**     Processor   : MK20DN128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-08-01, 15:38, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "UTIL1.h"
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDG.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "USB1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "USB0.h"
#include "CS1.h"
#include "WAIT1.h"
#include "LEDB.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "CLS1.h"
#include "XF1.h"
#include "MCUC1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
static uint8_t in_buffer[USB1_DATA_BUFF_SIZE];

static void CDC_Run(void) {
  int i;
  uint32_t val = 0;
  unsigned char buf[16];

  for(;;) {
    while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {
      /* device not enumerated */
      LEDR_Neg(); LEDG_Off();
      WAIT1_Waitms(10);
    }
    LEDR_Off(); LEDG_Neg();
    if (CDC1_GetCharsInRxBuf()!=0) {
      i = 0;
      while(   i<sizeof(in_buffer)-1
            && CDC1_GetChar(&in_buffer[i])==ERR_OK
           )
      {
        i++;
      }
      in_buffer[i] = '\0';
      (void)CDC1_SendString((unsigned char*)"echo: ");
      (void)CDC1_SendString(in_buffer);
      UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"val: ");
      UTIL1_strcatNum32u(buf, sizeof(buf), val);
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      (void)CDC1_SendString(buf);
      val++;
    } else {
      WAIT1_Waitms(10);
    }
  }
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  CDC_Run();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
