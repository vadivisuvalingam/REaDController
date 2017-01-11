# Microsoft Developer Studio Project File - Name="READ Test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=READ Test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "READ Test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "READ Test.mak" CFG="READ Test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "READ Test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "READ Test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "READ Test - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "C:\Program Files\National Instruments\Ni-daq\Include\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "READ Test - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "Ni-daq\Include\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "READ Test - Win32 Release"
# Name "READ Test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChargeDeviceIncrement.cpp
# End Source File
# Begin Source File

SOURCE=.\DataList.cpp
# End Source File
# Begin Source File

SOURCE=.\DevicePositions.cpp
# End Source File
# Begin Source File

SOURCE=.\DevWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ExperimentName.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralSummary.cpp
# End Source File
# Begin Source File

SOURCE=.\JazPath.cpp
# End Source File
# Begin Source File

SOURCE=.\LightMeterScalingCalculator.cpp
# End Source File
# Begin Source File

SOURCE=.\Modified_LightMeterScalingCalculator.cpp
# End Source File
# Begin Source File

SOURCE=.\MotorSpeed.cpp
# End Source File
# Begin Source File

SOURCE=.\NIBoard.cpp
# End Source File
# Begin Source File

SOURCE=".\READ Test.cpp"
# End Source File
# Begin Source File

SOURCE=".\READ Test.rc"
# End Source File
# Begin Source File

SOURCE=".\READ TestDlg.cpp"
# End Source File
# Begin Source File

SOURCE=.\READProbeCalibrationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\READScannerLightCalibration.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplesGridFloat.cpp
# End Source File
# Begin Source File

SOURCE=.\SamplesGridInteger.cpp
# End Source File
# Begin Source File

SOURCE=.\SequenceFloat.cpp
# End Source File
# Begin Source File

SOURCE=.\SequenceInteger.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TestProgressIndicator.cpp
# End Source File
# Begin Source File

SOURCE=.\TestRunEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\TestSequence.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChargeDeviceIncrement.h
# End Source File
# Begin Source File

SOURCE=.\DataList.h
# End Source File
# Begin Source File

SOURCE=.\DevicePositions.h
# End Source File
# Begin Source File

SOURCE=.\DevWnd.h
# End Source File
# Begin Source File

SOURCE=.\ExperimentName.h
# End Source File
# Begin Source File

SOURCE=.\GeneralSummary.h
# End Source File
# Begin Source File

SOURCE=.\JazPath.h
# End Source File
# Begin Source File

SOURCE=.\LightMeterScalingCalculator.h
# End Source File
# Begin Source File

SOURCE=.\Modified_LightMeterScalingCalculator.h
# End Source File
# Begin Source File

SOURCE=.\MotorSpeed.h
# End Source File
# Begin Source File

SOURCE=.\NIBoard.h
# End Source File
# Begin Source File

SOURCE=".\READ Test.h"
# End Source File
# Begin Source File

SOURCE=".\READ TestDlg.h"
# End Source File
# Begin Source File

SOURCE=.\READProbeCalibrationDlg.h
# End Source File
# Begin Source File

SOURCE=.\READScannerLightCalibration.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SampleInformation.h
# End Source File
# Begin Source File

SOURCE=.\SamplesGridFloat.h
# End Source File
# Begin Source File

SOURCE=.\SamplesGridInteger.h
# End Source File
# Begin Source File

SOURCE=.\SequenceFloat.h
# End Source File
# Begin Source File

SOURCE=.\SequenceInteger.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TestProgressIndicator.h
# End Source File
# Begin Source File

SOURCE=.\TestRunEngine.h
# End Source File
# Begin Source File

SOURCE=.\TestSequence.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\illustration2.bmp
# End Source File
# Begin Source File

SOURCE=".\res\READ Test.ico"
# End Source File
# Begin Source File

SOURCE=".\res\READ Test.rc2"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=".\Ni-daq\Lib\nidaq32.lib"
# End Source File
# Begin Source File

SOURCE=".\Ni-daq\Lib\nidex32.lib"
# End Source File
# End Target
# End Project
