VERSION 4.00
Begin VB.Form Form1
  Caption = "STCgenerateSquareWave"
  ClientHeight = 3195
  ClientLeft = 1140
  ClientTop = 1515
  ClientWidth = 6360
  Height = 3600
  Left = 1080
  LinkTopic = "Form1"
  ScaleHeight = 3195
  ScaleWidth = 6360
  Top = 1170
  Width = 6480
  Begin VB.CommandButton cmdExit
    Caption = "E&xit"
     Height = 615
     Left = 4680
     TabIndex = 2
     Top = 2520
     Width = 1575
  End
  Begin VB.CommandButton cmdDoOperation
     Caption = "&Do Operation"
     Height = 615
     Left = 2880
     TabIndex = 1
     Top = 2520
     Width = 1575
  End
  Begin VB.TextBox txtStatusBox
     Height = 2295
     Left = 120
     MultiLine = -1          'True
     ScrollBars = 2         'vertical
     TabIndex = 0
     Top = 120
     Width = 6135
  End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
' ********************************************************************
' 
'  Example Program:
'     STCgenerateSquareWave.FRM
' 
'  Description:
'     Generates a 1kHz square wave (digital pulse train) using general
'      purpose counter 0 and an internal 100kHz timebase. (for devices
'      with the DAQ-STC counter/timer) NOTE: To make this example work
'      on the devices with a TIO-ASIC, you may have to change the line
'      names, such as ND_PFI_8 to ND_IO_LINE_39.
' 
'  Example Category:
'     CTR
' 
'  Example Task Types:
'     PLSTRN
' 
'  List of key parameters:
'     ulGpctrNum, ulLOWcount, ulHIGHcount
' 
'     [Since variables are hardcoded, there is no guarantee that this
'      program will work for your setup.  This example is simply
'      presented as a code snippet of how you can use NI-DAQ functions
'      to perform a task.]
' 
'  List of NI-DAQ Functions used in this example:
'     GPCTR_Control, NIDAQErrorHandler, GPCTR_Set_Application,
'      GPCTR_Change_Parameter, Select_Signal, NIDAQWaitForKey
' 
'     [NOTE: For further details on each NI-DAQ function, please refer
'      to the NI-DAQ On-Line Help (NIDAQPC.HLP).]
' 
'  Pin Connection Information: 
'     Your digital pulse train will be on the GPCTR0_OUT pin. Connect
'      the ground reference to the 'digital ground' pin.
' 
'     [For further I/O connection details, please refer to your hardware
'      User Manual.]
' 
'     [For further details on how to run this example, please refer to
'      the NI-DAQ Examples On-Line Help (NIDAQEx.HLP).]
' 
' ********************************************************************
Option Explicit
Option Base 0
' 
' Constant for PrintText 
' 
Const LEN_PRINTTEXT = 4096 


' ************************************************************************
' SUBROUTINE:  PrintText
' DESCRIPTION: PrintText to desired TextBox (upto 4096 characters)
' INPUTS:      txtBox - TextBox to print on
'              strText - Text to print
' ************************************************************************
Sub PrintText(txtBox as TextBox, strText as string)

    txtBox.Text = Right$(txtBox.Text + strText$ + Chr$(13) + Chr$(10), LEN_PRINTTEXT)

    txtBox.SelStart = Len(CStr(txtBox.Text))

    DoEvents

End Sub


' ************************************************************************
' SUBROUTINE:  cmdExit_Click
' DESCRIPTION: Clean up and exit
' ************************************************************************
Sub cmdExit_Click()

    End

End Sub

' ************************************************************************
' SUBROUTINE:  Form_Load
' DESCRIPTION: Gets automatically called at startup
' ************************************************************************
Sub Form_Load()


End Sub


' ************************************************************************
' SUBROUTINE:  cmdDoOperation_Click
' DESCRIPTION: The main NI-DAQ operations are here
' ************************************************************************
Sub cmdDoOperation_Click()

    ' 
    '  Local Variable Declarations: 
    

    Dim iStatus As Integer
    Dim iRetVal As Integer
    Dim iDevice As Integer
    Dim ulGpctrNum As Long
    Dim ulLOWcount As Long
    Dim ulHIGHcount As Long
    Dim iIgnoreWarning As Integer

    iDevice% = 1
    ulGpctrNum& = ND_COUNTER_0
    ulLOWcount& = 50
    ulHIGHcount& = 50

    ' Temporarily disable buttons for protection from 'DoEvents'
    cmdDoOperation.Enabled = False
    cmdExit.Enabled = False

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control", iIgnoreWarning%)

    iStatus% = GPCTR_Set_Application(iDevice%, ulGpctrNum&, ND_PULSE_TRAIN_GNR)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Set_Application", iIgnoreWarning%)

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_SOURCE, ND_INTERNAL_100_KHZ)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/SOURCE", iIgnoreWarning%)

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_COUNT_1, ulLOWcount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/COUNT1", iIgnoreWarning%)

    iStatus% = GPCTR_Change_Parameter(iDevice%, ulGpctrNum&, ND_COUNT_2, ulHIGHcount&)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Change_Parameter/COUNT2", iIgnoreWarning%)

'     To output a counter pulse, you must call Select_Signal.

    iStatus% = Select_Signal(iDevice%, ND_GPCTR0_OUTPUT, ND_GPCTR0_OUTPUT, ND_LOW_TO_HIGH)

    iRetVal% = NIDAQErrorHandler(iStatus%, "Select_Signal/GPCTR0_OUTPUT-Enable", iIgnoreWarning%)

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_PROGRAM)

    iRetVal% = NIDAQErrorHandler(iStatus%, "GPCTR_Control/PROGRAM", iIgnoreWarning%)

    Call PrintText(txtStatusBox, "Square wave generation started... ")

'     HINT: If you don't see pulses at GPCTR0_OUTPUT, check your
'      connections.

    Call PrintText(txtStatusBox, "Hit any key to stop. ")

    iRetVal% = NIDAQWaitForKey(0.0)

'     CLEANUP - Don't check for errors on purpose.

'     Reset GPCTR.

    iStatus% = GPCTR_Control(iDevice%, ulGpctrNum&, ND_RESET)

'     Disconnect GPCTR0_OUTPUT.

'     Note that the following Select_Signal call will cause the output
'      to be high impedance which will most likely bring the logic level
'      HIGH if there is a pull-up resistor on this pin. (Check your
'      hardware user manual.)  If you do not want this behavior, comment
'      out the next line.

    iStatus% = Select_Signal(iDevice%, ND_GPCTR0_OUTPUT, ND_NONE, ND_DONT_CARE)

    Call PrintText(txtStatusBox, "Square wave generation done! ")


    ' Re-enable buttons
    cmdDoOperation.Enabled = True
    cmdExit.Enabled = True

End Sub


