# Microsoft Developer Studio Project File - Name="client" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=client - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "client.mak" CFG="client - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "client - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "client - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/GoldSrc/client", HGEBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "client - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\release_client"
# PROP BASE Intermediate_Dir ".\release_client"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\release_client"
# PROP Intermediate_Dir ".\release_client"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\utils\vgui\include" /I "..\engine" /I "..\common" /I "..\pm_shared" /I "..\dlls" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "CLIENT_DLL" /FD /c
# SUBTRACT CPP /Fr /YX
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib winmm.lib ../utils/vgui/lib/vgui.lib wsock32.lib opengl32.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386
# SUBTRACT LINK32 /map
# Begin Custom Build
TargetDir=.\release_client
InputPath=.\release_client\client.dll
SOURCE="$(InputPath)"

"..\..\..\cl_dlls\client.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetDir)\client.dll "..\..\..\cl_dlls\client.dll"

# End Custom Build

!ELSEIF  "$(CFG)" == "client - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "client___Win32_Debug"
# PROP BASE Intermediate_Dir "client___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\debug_client"
# PROP Intermediate_Dir ".\debug_client"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /O2 /I "..\utils\vgui\include" /I "..\engine" /I "..\common" /I "..\pm_shared" /I "..\dlls" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "CLIENT_DLL" /YX /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W3 /Gm /GX /ZI /Od /I "..\utils\vgui\include" /I "..\engine" /I "..\common" /I "..\pm_shared" /I "..\dlls" /D "WIN32" /D "DEBUG" /D "_WINDOWS" /D "CLIENT_DLL" /Fr /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib winmm.lib ../utils/vgui/lib/vgui.lib wsock32.lib opengl32.lib /nologo /subsystem:windows /dll /machine:I386 /out:".\debug_client\client.dll"
# SUBTRACT BASE LINK32 /map
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib winmm.lib ../utils/vgui/lib/vgui.lib wsock32.lib opengl32.lib /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386
# SUBTRACT LINK32 /map
# Begin Custom Build
TargetDir=.\debug_client
InputPath=.\debug_client\client.dll
SOURCE="$(InputPath)"

"..\..\..\cl_dlls\client.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetDir)\client.dll "..\..\..\cl_dlls\client.dll"

# End Custom Build

!ENDIF 

# Begin Target

# Name "client - Win32 Release"
# Name "client - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Group "hl"

# PROP Default_Filter "*.CPP"
# Begin Source File

SOURCE=.\ev_hldm.cpp
# End Source File
# Begin Source File

SOURCE=..\common\interface.cpp
# End Source File
# Begin Source File

SOURCE=.\mp3.cpp
# End Source File
# Begin Source File

SOURCE=.\rain.cpp
# End Source File
# Begin Source File

SOURCE=..\game_shared\vgui_scrollbar2.cpp
# End Source File
# Begin Source File

SOURCE=..\game_shared\vgui_slider2.cpp
# End Source File
# Begin Source File

SOURCE=..\game_shared\voice_banmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\game_shared\voice_status.cpp
# End Source File
# Begin Source File

SOURCE=..\game_shared\voice_vgui_tweakdlg.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ammo.cpp
# End Source File
# Begin Source File

SOURCE=.\ammo_secondary.cpp
# End Source File
# Begin Source File

SOURCE=.\ammohistory.cpp
# End Source File
# Begin Source File

SOURCE=.\battery.cpp
# End Source File
# Begin Source File

SOURCE=.\cdll_int.cpp
# End Source File
# Begin Source File

SOURCE=.\death.cpp
# End Source File
# Begin Source File

SOURCE=.\demo.cpp
# End Source File
# Begin Source File

SOURCE=.\entity.cpp
# End Source File
# Begin Source File

SOURCE=.\ev_common.cpp
# End Source File
# Begin Source File

SOURCE=.\events.cpp
# End Source File
# Begin Source File

SOURCE=.\flashlight.cpp
# End Source File
# Begin Source File

SOURCE=.\GameStudioModelRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\geiger.cpp
# End Source File
# Begin Source File

SOURCE=.\health.cpp
# End Source File
# Begin Source File

SOURCE=.\hud.cpp
# End Source File
# Begin Source File

SOURCE=.\hud_msg.cpp
# End Source File
# Begin Source File

SOURCE=.\hud_redraw.cpp
# End Source File
# Begin Source File

SOURCE=.\hud_servers.cpp
# End Source File
# Begin Source File

SOURCE=.\hud_spectator.cpp
# End Source File
# Begin Source File

SOURCE=.\hud_update.cpp
# End Source File
# Begin Source File

SOURCE=.\in_camera.cpp
# End Source File
# Begin Source File

SOURCE=.\input.cpp
# End Source File
# Begin Source File

SOURCE=.\inputw32.cpp
# End Source File
# Begin Source File

SOURCE=.\menu.cpp
# End Source File
# Begin Source File

SOURCE=.\message.cpp
# End Source File
# Begin Source File

SOURCE=.\overview.cpp

!IF  "$(CFG)" == "client - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "client - Win32 Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\parsemsg.cpp
# End Source File
# Begin Source File

SOURCE=.\particlemgr.cpp
# End Source File
# Begin Source File

SOURCE=.\particlemsg.cpp
# End Source File
# Begin Source File

SOURCE=.\particlesys.cpp
# End Source File
# Begin Source File

SOURCE=..\pm_shared\pm_debug.c
# End Source File
# Begin Source File

SOURCE=..\pm_shared\pm_math.c
# End Source File
# Begin Source File

SOURCE=..\pm_shared\pm_shared.c
# End Source File
# Begin Source File

SOURCE=.\saytext.cpp
# End Source File
# Begin Source File

SOURCE=.\status_icons.cpp
# End Source File
# Begin Source File

SOURCE=.\statusbar.cpp
# End Source File
# Begin Source File

SOURCE=.\studio_util.cpp
# End Source File
# Begin Source File

SOURCE=.\StudioModelRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\text_message.cpp
# End Source File
# Begin Source File

SOURCE=.\train.cpp
# End Source File
# Begin Source File

SOURCE=.\tri.cpp
# End Source File
# Begin Source File

SOURCE=.\util.cpp
# End Source File
# Begin Source File

SOURCE=..\game_shared\vgui_checkbutton2.cpp
# End Source File
# Begin Source File

SOURCE=.\vgui_ClassMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\vgui_ConsolePanel.cpp
# End Source File
# Begin Source File

SOURCE=.\vgui_ControlConfigPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\vgui_CustomObjects.cpp
# End Source File
# Begin Source File

SOURCE=..\game_shared\vgui_grid.cpp
# End Source File
# Begin Source File

SOURCE=..\game_shared\vgui_helpers.cpp
# End Source File
# Begin Source File

SOURCE=.\vgui_int.cpp
# End Source File
# Begin Source File

SOURCE=..\game_shared\vgui_listbox.cpp
# End Source File
# Begin Source File

SOURCE=..\game_shared\vgui_loadtga.cpp
# End Source File
# Begin Source File

SOURCE=.\vgui_MOTDWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\vgui_SchemeManager.cpp
# End Source File
# Begin Source File

SOURCE=.\vgui_ScorePanel.cpp
# End Source File
# Begin Source File

SOURCE=.\vgui_ServerBrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\vgui_SpectatorPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\vgui_TeamFortressViewport.cpp
# End Source File
# Begin Source File

SOURCE=.\vgui_teammenu.cpp
# End Source File
# Begin Source File

SOURCE=.\view.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ammo.h
# End Source File
# Begin Source File

SOURCE=.\ammohistory.h
# End Source File
# Begin Source File

SOURCE=.\camera.h
# End Source File
# Begin Source File

SOURCE=.\cl_dll.h
# End Source File
# Begin Source File

SOURCE=.\com_weapons.h
# End Source File
# Begin Source File

SOURCE=.\demo.h
# End Source File
# Begin Source File

SOURCE=.\ev_hldm.h
# End Source File
# Begin Source File

SOURCE=.\eventscripts.h
# End Source File
# Begin Source File

SOURCE=.\GameStudioModelRenderer.h
# End Source File
# Begin Source File

SOURCE=.\health.h
# End Source File
# Begin Source File

SOURCE=.\hud.h
# End Source File
# Begin Source File

SOURCE=.\hud_iface.h
# End Source File
# Begin Source File

SOURCE=.\hud_servers.h
# End Source File
# Begin Source File

SOURCE=.\hud_servers_priv.h
# End Source File
# Begin Source File

SOURCE=.\hud_spectator.h
# End Source File
# Begin Source File

SOURCE=.\in_defs.h
# End Source File
# Begin Source File

SOURCE=..\common\itrackeruser.h
# End Source File
# Begin Source File

SOURCE=.\kbutton.h
# End Source File
# Begin Source File

SOURCE=.\mp3.h
# End Source File
# Begin Source File

SOURCE=.\overview.h
# End Source File
# Begin Source File

SOURCE=.\parsemsg.h
# End Source File
# Begin Source File

SOURCE=.\particlemgr.h
# End Source File
# Begin Source File

SOURCE=.\particlesys.h
# End Source File
# Begin Source File

SOURCE=..\pm_shared\pm_debug.h
# End Source File
# Begin Source File

SOURCE=..\pm_shared\pm_defs.h
# End Source File
# Begin Source File

SOURCE=..\pm_shared\pm_info.h
# End Source File
# Begin Source File

SOURCE=..\pm_shared\pm_materials.h
# End Source File
# Begin Source File

SOURCE=..\pm_shared\pm_movevars.h
# End Source File
# Begin Source File

SOURCE=..\pm_shared\pm_shared.h
# End Source File
# Begin Source File

SOURCE=.\studio_util.h
# End Source File
# Begin Source File

SOURCE=.\StudioModelRenderer.h
# End Source File
# Begin Source File

SOURCE=.\util.h
# End Source File
# Begin Source File

SOURCE=.\util_vector.h
# End Source File
# Begin Source File

SOURCE=.\vgui_ConsolePanel.h
# End Source File
# Begin Source File

SOURCE=.\vgui_ControlConfigPanel.h
# End Source File
# Begin Source File

SOURCE=.\vgui_int.h
# End Source File
# Begin Source File

SOURCE=.\vgui_SchemeManager.h
# End Source File
# Begin Source File

SOURCE=.\vgui_ScorePanel.h
# End Source File
# Begin Source File

SOURCE=.\vgui_ServerBrowser.h
# End Source File
# Begin Source File

SOURCE=.\vgui_SpectatorPanel.h
# End Source File
# Begin Source File

SOURCE=.\vgui_TeamFortressViewport.h
# End Source File
# Begin Source File

SOURCE=.\view.h
# End Source File
# Begin Source File

SOURCE=..\game_shared\voice_banmgr.h
# End Source File
# Begin Source File

SOURCE=..\game_shared\voice_status.h
# End Source File
# Begin Source File

SOURCE=..\game_shared\voice_vgui_tweakdlg.h
# End Source File
# Begin Source File

SOURCE=.\wrect.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
