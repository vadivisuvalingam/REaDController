/*********************************************************************
*
* Example program: 
*    STCgenerateRepeatedTriggeredPulse.c
*
* Description: 
*    Repeatedly generates a digtal pulse 1 ms LOW and 100 ms HIGH using
*     general purpose counter 0 upon every trigger.  This is different
*     from CSTC1tPl in that you don't have to rearm after each trigger.
*     (for devices with the DAQ-STC counter/timer) NOTE: To make this
*     example work on the devices with a TIO-ASIC, you may have to
*     change the line names, such as ND_PFI_8 to ND_IO_LINE_39.
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    PLSTRN, 1PT
*
* List of key parameters: 
*    ulGpctrNum, ulLOWcount, ulHIGHcount
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
*     GPCTR_Change_Parameter, Select_Signal, NIDAQWaitForKey
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Your digital pulses will be on the GPCTR0_OUT pin. Connect your
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
    i16 iIgnoreWarning = 0;

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control",
     iIgnoreWarning);

    iStatus = GPCTR_Set_Application(iDevice, ulGpctrNum,
     ND_RETRIG_PULSE_GNR);

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
     "GPCTR_Change_Parameter/COUNT1", iIgnoreWarning);

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

    printf(" Apply trigger pulses to PFI9 and you will see a pulse every time!\n");

    /* HINT: If you don't see pulses at GPCTR0_OUTPUT, check your
     connections. */

    printf(" Hit any key to stop.\n");

    iRetVal = NIDAQWaitForKey(0.0);

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

    printf(" Repeated triggered pulse generation done!\n");


}

/* End of program */
