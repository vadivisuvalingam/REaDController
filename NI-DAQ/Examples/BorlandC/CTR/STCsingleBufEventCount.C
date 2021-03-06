/*********************************************************************
*
* Example program: 
*    STCsingleBufEventCount.c
*
* Description: 
*    Counts the number of digital pulses that occur between consecutive
*     digital triggers on the gate input, using general purpose counter
*     0 and an internal 20MHz timebase. (for devices with the DAQ-STC
*     counter/timer) Regarding using your own timebase source for
*     buffered GPCTR operations, refer to the GPCTR_Set_Application
*     description in the NI-DAQ Function Reference Manual. NOTE: To
*     make this example work on the devices with a TIO-ASIC, you may
*     have to change the line names, such as ND_PFI_8 to ND_IO_LINE_39.
*
* Example Category: 
*    CTR
*
* Example Task Types: 
*    EVENTCNT, BUF
*
* List of key parameters: 
*    ulGpctrNum, pulBuffer, ulCount, ulArmed
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
*     GPCTR_Change_Parameter, GPCTR_Config_Buffer, GPCTR_Watch,
*     NIDAQYield
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    Connect your gating digital pulse train to the PFI9/GPCTR0_GATE
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
    static u32 pulBuffer[100] = {0};
    u32 ulCount = 100;
    u32 ulInitCount = 0;
    u32 ulArmed = ND_YES;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control",
     iIgnoreWarning);

    iStatus = GPCTR_Set_Application(iDevice, ulGpctrNum,
     ND_BUFFERED_EVENT_CNT);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Set_Application",
     iIgnoreWarning);

    /* If you want to use a different GPCTR source, change the last
     parameter in this function. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_SOURCE,
     ND_INTERNAL_20_MHZ);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning);

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum, ND_GATE,
     ND_PFI_9);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/GATE", iIgnoreWarning);

    /* Load initial count. */

    iStatus = GPCTR_Change_Parameter(iDevice, ulGpctrNum,
     ND_INITIAL_COUNT, ulInitCount);

    iRetVal = NIDAQErrorHandler(iStatus,
     "GPCTR_Change_Parameter/INITCOUNT", iIgnoreWarning);

    iStatus = GPCTR_Config_Buffer(iDevice, ulGpctrNum, 0, ulCount,
     pulBuffer);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Config_Buffer",
     iIgnoreWarning);

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_PROGRAM);

    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM",
     iIgnoreWarning);

    printf(" Apply your gating trigger pulse train to PFI9 now.\n");

    /* Loop until 'ulGpctrNum' is no longer armed. */

    do {


        iStatus = GPCTR_Watch(iDevice, ulGpctrNum, ND_ARMED,
         &ulArmed);

        iRetVal = NIDAQYield(iYieldON);

    } while ((ulArmed == ND_YES) && (iStatus == 0));


    iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/ARMED",
     iIgnoreWarning);

    printf(" Event count data is in 'pulBuffer'.\n");

    /* CLEANUP - Don't check for errors on purpose. */

    /* Reset GPCTR. */

    iStatus = GPCTR_Control(iDevice, ulGpctrNum, ND_RESET);

    printf(" GPCTR buffered event counting done!\n");


}

/* End of program */
