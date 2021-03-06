/*********************************************************************
*
* Example program: 
*    STCsinglePeriodMeasure.c
*
* Description: 
*    Takes one measurement of the period of a digital pulse train using
*     general purpose counter 0 (for devices with the DAQ-STC
*     counter/timer) NOTE: To make this example work on the devices
*     with a TIO-ASIC, you may have to change the line names, such as
*     ND_PFI_8 to ND_IO_LINE_39.
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    PERM, INTTIM, 1PT
*
* List of key parameters: 
*    ulGpctrNum, ulCount, ulArmed
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
*     GPCTR_Change_Parameter, GPCTR_Watch, NIDAQYield
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your digital pulse train signal to the PFI9/GPCTR0_GATE
*     pin. Connect the ground reference to the 'digital ground' pin.
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
    u32 ulCount = 0;
    u32 ulArmed = ND_YES;
    i32 ulTCReached = ND_NO;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control",
     iIgnoreWarning);

    iStatus = GPCTR_Set_Application(iDevice, ulGpctrNum,
     ND_SINGLE_PERIOD_MSR);

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

    /* Load initial count. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_INITIAL_COUNT, ulCount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/INITCOUNT", iIgnoreWarning);

    printf(" Apply your digital pulse train to PFI9 now.\n");

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_PROGRAM);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM",
     iIgnoreWarning);

    /* Loop until 'ulGpctrNum' is no longer armed. */

    do {


        iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_ARMED,
         &ulArmed);

        iRetVal = NIDAQYield(iYieldON);

    } while ((ulArmed == ND_YES) && (iStatus == 0));


    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/ARMED",
     iIgnoreWarning);

    iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_COUNT, &ulCount);
    

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/COUNT",
     iIgnoreWarning);

    iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_TC_REACHED,
     &ulTCReached);

    if (ulTCReached == ND_YES) {


        printf(" Counter reached terminal count! - The count may be incorrect.\n");

    }
    else {

        printf(" The period in between pulses (in 10uSec ticks) was %lu\n", ulCount);

    }


    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset GPCTR. */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);


}

/* End of program */
