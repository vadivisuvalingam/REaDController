/*********************************************************************
*
* Example program: 
*    STCgenerateSingleTriggeredPulse.c
*
* Description: 
*    Generates a single digital pulse 1 ms LOW and 100 ms HIGH using
*     general purpose counter 0 upon a trigger (for devices with the
*     DAQ-STC counter/timer) NOTE: To make this example work on the
*     devices with a TIO-ASIC, you may have to change the line names,
*     such as ND_PFI_8 to ND_IO_LINE_39.
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    PLSTRN, 1PT
*
* List of key parameters: 
*    ulGpctrNum, ulLOWcount, ulHIGHcount, ulDone
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
*     GPCTR_Change_Parameter, Select_Signal, GPCTR_Watch, NIDAQYield
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Your digital pulse will be on the GPCTR0_OUT pin. Connect your
*     digital trigger pulse to the PFI9/GPCTR0_GATE pin. Connect the
*     ground reference to the 'digital ground' pin.
*
*    [For further I/O connection details, please refer to your hardware
*     User Manual.]
*
*    [For further details on how to run this example, please refer to
*     the NI-DAQ Examples On-Line Help (NIDAQEx.HLP).]
*
*********************************************************************/
/*
 * Includes: 
 */

#include "nidaqex.h"


/*
 * Main: 
 */

void main(void)
{
    /*
     * Local Variable Declarations: 
     */

    i16 iStatus = 0;
    i16 iRetVal = 0;
    i16 iDevice = 1;
    u32 ulGpctrNum = ND_COUNTER_0;
    u32 ulLOWcount = 100;
    u32 ulHIGHcount = 10000;
    u32 ulDone = ND_NO;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control",
     iIgnoreWarning);

    iStatus = GPCTR_Set_Application(iDevice, ulGpctrNum,
     ND_SINGLE_TRIG_PULSE_GNR);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Set_Application",
     iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_SOURCE,
     ND_INTERNAL_100_KHZ);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_GATE,
     ND_PFI_9);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/GATE", iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_COUNT_1,
     ulLOWcount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/COUNT2", iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_COUNT_2,
     ulHIGHcount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/COUNT2", iIgnoreWarning);

    /* To output a counter pulse, you must call Select_Signal. */

    iStatus = Select_Signal(iDevice, ND_GPCTR0_OUTPUT,
     ND_GPCTR0_OUTPUT, ND_LOW_TO_HIGH);

    iRetVal = NIDAQErrorHandler(iStatus,
     "Select_Signal/GPCTR0_OUTPUT-Enable", iIgnoreWarning);

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_PROGRAM);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM",
     iIgnoreWarning);

    printf(" Apply your trigger pulse to PFI9 now. The rising edge will arm and the second falling edge will gate in the value.\n");

    /* Loop until operation is done. */

    do {


        iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_DONE, &ulDone);
        

        iRetVal = NIDAQYield(iYieldON);

    } while ((ulDone == ND_NO) && (iStatus == 0));


    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/DONE",
     iIgnoreWarning);

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset GPCTR. */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    /* Disconnect GPCTR0_OUTPUT. */

    /* Note that the following Select_Signal call will cause the
     output to be high impedance which will most likely bring the logic
     level HIGH if there is a pull-up resistor on this pin. (Check your
     hardware user manual.)  If you do not want this behavior, comment out
     the next line. */

    iStatus = Select_Signal(iDevice, ND_GPCTR0_OUTPUT, ND_NONE,
     ND_DONT_CARE);

    printf(" Single triggered pulse has been generated!\n");


}

/* End of program */
