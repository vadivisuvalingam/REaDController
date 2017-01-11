/************************************************************************
 * TITLE:       NIDAQEx.c
 *              Supporting code module for NI-DAQ Examples
 *
 *              == L A B  W I N D O W S / C V I   V E R S I O N ==
 *
 * DESCR:       This code module contains several supplemental functions
 *              that can be used with NI-DAQ functions, such as:
 *
 *                NIDAQPlotWaveform(...) - to graph a waveform
 *                NIDAQMakeBuffer(...) - to make a data buffer
 *                NIDAQDelay(...) - to place a short delay
 *                NIDAQErrorHandler(...) - to handle NI-DAQ errors
 *                NIDAQYield(...) - to allow other system events
 *                NIDAQMean(...) - to calculate mean value of an array
 *                NIDAQWaitForKey(...) - to wait for user to hit key
 *
 * Copyright (c) 1997, National Instruments Corp.  All rights reserved.
 ************************************************************************/

/*
 * Includes
 */
#include "NIDAQEx.h"

/*
 * Function definitions
 */

/************************************************************************
 * FUNCTION:    NIDAQPlotWaveform
 *
 * DESCR:       Plots a waveform onto a graph on a separate window with
 *              a "Return" button on it.
 *
 * INPUTS:      (void *) pvBuffer - address of buffer
 *              NOTE: Make sure you typecast the buffer ptr to (void*)!
 *              (u32) ulType - datatype of data
 *              (u32) ulNumPts - number of datapts in pBuffer
 *
 * OUTPUTS:     (nidaqExRetType) <return>  0 if success
 *                             other error codes come from YGraphPopup
 ************************************************************************/
nidaqExRetType WINAPI NIDAQPlotWaveform(void *pvBuffer, u32 ulNumPts, u32 ulType)
{
	return YGraphPopup("Data plot", pvBuffer, (i32)ulNumPts, (i32)ulType);
}


/************************************************************************
 * FUNCTION:    NIDAQMakeBuffer
 *
 * DESCR:       Makes a databuffer for doing output operations.
 *              The output depends on the datatype selected.
 *
 * INPUTS:      (void *) pvBuffer - address of preallocated mem buffer
 *              NOTE: You must typecast the buffer ptr to (void*)!
 *              (u32) ulNumPts - number of datapts in pBuffer
 *              (u32) ulType - datatype of data (this is to allow
 *                            compatibility with C)
 *                   * if WFM_DATA_U8  - ramp (0 to 255)
 *                   * if WFM_DATA_I16 - 10 period sqwv (0 - 2047)
 *                   * if WFM_DATA_F64 - 10 period sinewave (0 - 4.99)
 *                   * if WFM_DATA_U32 - NOT SUPPORTED!  (error)
 *
 * OUTPUTS:     (nidaqExRetType) <return>  0 if success, or
 *                   NIDAQEX_INVALID_BUFFER
 *                   NIDAQEX_INVALID_NUMPTS
 *                   NIDAQEX_INVALID_TYPE
 *              (void *) pvBuffer - address of buffer, with data
 ************************************************************************/
nidaqExRetType WINAPI NIDAQMakeBuffer(void* pvBuffer, u32 ulNumPts, u32 ulType)
{
   u32 ulStep   = 0,   /* # of points in a period (step)      */
       ulIndex  = 0,   /* index into the data array           */
       ulOffset = 0;   /* 2nd offset ptr into the data array  */
   f64 dAmpl   = WFM_F64_AMPL / 2.0,
       dOffset = WFM_F64_AMPL / 2.0;

   if (ulNumPts == 0)
      return (NIDAQEX_INVALID_NUMPTS);

   else if (pvBuffer == NULL)
      return (NIDAQEX_INVALID_BUFFER);

   else
   {
      if (ulNumPts > (WFM_MIN_PTS_IN_PERIOD * WFM_PERIODS))
         ulStep = ulNumPts / WFM_PERIODS;   /* #pts in each of 10 periods */
      else
	      ulStep = WFM_MIN_PTS_IN_PERIOD;  /* if buffer is small, alternate */

      switch (ulType)
      {
         case (WFM_DATA_U8):
            /* datatype is u8 */
            for (ulIndex = 0; ulIndex < ulNumPts; ulIndex++)
               *((u8*)pvBuffer + ulIndex) =
                                       (u8)(ulIndex % WFM_U8_MODULO);
            break;

         case (WFM_DATA_I16):
            /* datatype is i16 */
            for (ulIndex = 0; ulIndex < ulNumPts; ulIndex += ulStep)
            {
               for (ulOffset = 0; ulOffset < ulStep; ulOffset++)
                  if (ulOffset < ulStep / 2)
                     *((i16*)pvBuffer + ulIndex + ulOffset) = 0;
                  else
                     *((i16*)pvBuffer + ulIndex + ulOffset) =
                                                  (i16)WFM_I16_AMPL;
            }
            break;

         case (WFM_DATA_F64):
            /* datatype is f64 */
            for (ulIndex = 0; ulIndex < ulNumPts; ulIndex++)
            {
                  *((f64*)pvBuffer + ulIndex) =
                      (f64)sin((f64)ulIndex/(f64)ulStep * (f64)WFM_2PI)
                               * dAmpl + dOffset;
            }
            break;

         default: /* invalid type! */
            return (NIDAQEX_INVALID_TYPE);
      }
   }
   return (NoError);
}
/************************************************************************
 * SUBROUTINE:  NIDAQDelay
 *
 * DESCR:       Places a delay for a while.
 *
 * INPUTS:      (f64) dSec - delay in seconds
 *
 * OUTPUTS:     (nidaqExRetType) <return>  0..
 ************************************************************************/
nidaqExRetType WINAPI NIDAQDelay(f64 dSec)
{
   Delay(dSec);
   return (NoError);
}
/************************************************************************
 * SUBROUTINE:  NIDAQYield
 *
 * DESCR:       Allow other events to happen.
 *
 * INPUTS:      (i16) iYieldMode - 0: OFF, non-zero: ON
 *
 * OUTPUTS:     (nidaqExRetType) <return>  0
 ************************************************************************/
nidaqExRetType WINAPI NIDAQYield(i16 iYieldMode)
{
   if (iYieldMode)
   {
      ProcessSystemEvents();
   }
   return (NoError);
}
/************************************************************************
 * SUBROUTINE:  NIDAQErrorHandler
 *
 * DESCR:       Handles NI-DAQ errors and warnings.
 *              If there was an error, a dialog box will be displayed.
 *
 * INPUTS:      (i16) iStatus - status code returned from NI-DAQ function
 *              (char*) strFuncName - function name associated with status
 *              (i16) iIgnoreWarning - if 1, ignore positive status codes,
 *                                which are warnings and non-fatal.
 *
 * OUTPUTS:     (nidaqExRetType) <return>  return code from MessagePopup
 ************************************************************************/
nidaqExRetType WINAPI NIDAQErrorHandler(i16 iStatus, char *strFuncName, i16 iIgnoreWarning)
{
    char strMsg[255] = {0},
         strTitle[20] = {0};

    if (iStatus != NoError)
    {
       sprintf(strTitle, "NI-DAQ %s", (iStatus > 0)? "warning":"error");
       sprintf(strMsg,   "[%s] returned %s %d.\n\n",
                             strFuncName, strTitle, iStatus);
       if (((iStatus > 0) && !iIgnoreWarning) ||
           (iStatus < 0))
       {
          return MessagePopup(strTitle, strMsg);
       }
    }
    return (NoError);
}

/************************************************************************
 * SUBROUTINE:  NIDAQMean
 *
 * DESCR:       Compute arithmetic mean (average) of values in a buffer.
 *              This function does not rely on the analysis functions.
 *
 * INPUTS:      (void *) pvBuffer - address of data buffer
 *              NOTE: You must typecast the buffer ptr to (void*)!
 *              (u32) ulNumPts - number of datapts in pvBuffer
 *              (u32) ulType - datatype of data (this is to allow
 *                            compatibility with C)
 *                   * if WFM_DATA_U8
 *                   * if WFM_DATA_I16
 *                   * if WFM_DATA_F64
 *                   * if WFM_DATA_U32
 *
 * OUTPUTS:     (nidaqExRetType) <return>  0
 *              (f64*) dMean - arithmetic mean
 ************************************************************************/
nidaqExRetType WINAPI NIDAQMean(void* pvBuffer, u32 ulNumPts, u32 ulType, f64* dMean)
{
   u32 ulIndex;
   f64 dSum = 0.0,
       dTempMean = 0.0;

   if (ulNumPts == 0)
      return (NIDAQEX_INVALID_NUMPTS);

   else if (pvBuffer == NULL)
      return (NIDAQEX_INVALID_BUFFER);

   else
   {
      switch (ulType)
      {
         case (WFM_DATA_U8):
            /* datatype is u8 */
            for (ulIndex = 0; ulIndex < ulNumPts; ulIndex++)
               dSum = dSum + (f64)*((u8*)pvBuffer + ulIndex);
            break;

         case (WFM_DATA_I16):
            /* datatype is i16 */
            for (ulIndex = 0; ulIndex < ulNumPts; ulIndex++)
               dSum = dSum + (f64)*((i16*)pvBuffer + ulIndex);
            break;

         case (WFM_DATA_U32):
            /* datatype is u32 */
            for (ulIndex = 0; ulIndex < ulNumPts; ulIndex++)
               dSum = dSum + (f64)*((u32*)pvBuffer + ulIndex);
            break;

         case (WFM_DATA_F64):
            /* datatype is f64 */
            for (ulIndex = 0; ulIndex < ulNumPts; ulIndex++)
                  dSum = dSum + *((f64*)pvBuffer + ulIndex);
            break;

         default: /* invalid type! */
            return (NIDAQEX_INVALID_TYPE);
      }

      /* calculate arithmetic mean */
       dTempMean = dSum / (f64)ulNumPts;

      /* copy out to parameter list if dMean is allocated */
      if (dMean)
         *dMean = dTempMean;
   }
   return (NoError);
}
/************************************************************************
 * SUBROUTINE:  NIDAQWaitForKey
 *
 * DESCR:       Wait for a key hit until eternity or a timelimit.
 *              As a side effect, this function brings the stdio
 *              window to the front.
 * NOTE:        This function works only in the Standard I/O Window,
 *              not in windows created in the User Interface Library or
 *              in Windows Console Application windows.
 *
 * INPUTS:      (f64) dTimeLimit - max. # of seconds to wait
 *                   if <=0.0, then wait until key hit forever
 *
 * OUTPUTS:     (nidaqExRetType) <return>  0
 ************************************************************************/
nidaqExRetType WINAPI NIDAQWaitForKey(f64 dTimeLimit)
{
   double dTimeStart = Timer();
   do
   {
      if ((dTimeLimit > 0.0) &&
          ((Timer() - dTimeStart) > dTimeLimit))
         break;
   } while (!KeyHit());
   GetKey();

   return (NoError);
}

