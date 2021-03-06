/*********************************************************************
*
* Example program: 
*    WFMsingleBufRegenerate.c
*
* Description: 
*    Repeatedly outputs a waveform from one analog output channel,
*     using internal timing (uses high-level NI-DAQ functions)
*
* Example Category: 
*    AO
*
* Example Task Types: 
*    BUF, 1CH, BURST, SYNC, INTTIM, INTTRIG
*
* List of key parameters: 
*    ulIterations, ulItersDone
*
*    [Since variables are hardcoded, there is no guarantee that this
*     program will work for your setup.  This example is simply
*     presented as a code snippet of how you can use NI-DAQ functions
*     to perform a task.]
*
* List of NI-DAQ Functions used in this example: 
*    NIDAQMakeBuffer, WFM_Scale, NIDAQErrorHandler, WFM_Op, WFM_Check,
*     WFM_Group_Control, AO_VWrite
*
*    [NOTE: For further details on each NI-DAQ function, please refer
*     to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
*
* Pin Connection Information: 
*    The analog output signal will be available at AO channel 0. The
*     default analog output mode for the DAQ device will be used.
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
    i16 iNumChans = 1;
    i16 iChan = 0;
    static i16 piChanVect[1] = {0};
    static f64 pdBuffer[5000] = {0};
    static i16 piBuffer[5000] = {0};
    u32 ulCount = 5000;
    u32 ulIterations = 10;
    f64 dUpdateRate = 5000.0;
    i16 iWFMstopped = 0;
    u32 ulItersDone = 0;
    u32 ulItersToDo = 10;
    u32 ulPtsDone = 0;
    i16 iIgnoreWarning = 0;
    i16 iYieldON = 1;

    iStatus = NIDAQMakeBuffer(pdBuffer, ulCount, WFM_DATA_F64);

    if (iStatus == 0) {


        /* If buffer was made correctly, then output it. */

        printf(" A %lu point waveform should be output %lu times at a rate of %lf updates/sec.\n", ulCount, ulIterations, dUpdateRate);

        iStatus = WFM_Scale(iDevice, iChan, ulCount, 1.0, pdBuffer,
         piBuffer);

        iRetVal = NIDAQErrorHandler(iStatus, "WFM_Scale",
         iIgnoreWarning);

        /* NOTE FOR DSA devices... DSA devices can format samples in a
         left-justified format in 32-bit data words. This means that the most
         significant bits of the data word contain the bits generated by the
         converter. When allocating data buffers, be sure to account for the
         32-bit data width. Even though a number of DAQ/SCAN/WFM functions are
         declared to accept pointers to 16-bit data buffers, you should pass
         pointers to 32-bit data buffers. */
        

        /* Also for DSA devices, remember to call AO_Change_Parameter
         to enable the analog output. */

        iStatus = WFM_Op(iDevice, iNumChans, piChanVect, piBuffer,
         ulCount, ulIterations, dUpdateRate);

        iRetVal = NIDAQErrorHandler(iStatus, "WFM_Op",
         iIgnoreWarning);

        if (iStatus == 0) {


            if (ulIterations > 0) {


                printf(" The waveform generation is done!\n");

            }
            else {

                /* HINT: if you set 'ulIterations' to 0, WFM_Op will
                 simply start the waveform generation and return control to the
                 program. In that case, after WFM_Op, you must call WFM_Check to find
                 out the current waveform generation status, and
                 WFM_Group_Control/CLEAR to stop the waveform. */
                

                while (ulItersDone < ulItersToDo) {

                    

                    iStatus = WFM_Check(iDevice, iChan, &iWFMstopped,
                     &ulItersDone, &ulPtsDone);

                    iRetVal = NIDAQErrorHandler(iStatus, "WFM_Check",
                     iIgnoreWarning);
                    

                }


                /* CLEANUP - Don't check for errors on purpose. */
                

                /* Turn off WFM group. */

                iStatus = WFM_Group_Control(iDevice, 1, 0);
                

                /* Set output at 0 volts. */

                iStatus = AO_VWrite(iDevice, iChan, 0.0);
                

            }


        }


    }
    else {

        printf(" The buffer was not made correctly. Check the parameters for NIDAQMakeBuffer.\n");

    }



}

/* End of program */
