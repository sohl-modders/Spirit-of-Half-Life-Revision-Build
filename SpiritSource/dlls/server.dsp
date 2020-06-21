# Microsoft Developer Studio Project File - Name="server" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=server - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "server.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "server.mak" CFG="server - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "server - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "server - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/GoldSrc/dlls", ELEBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "server - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\release_server"
# PROP BASE Intermediate_Dir ".\release_server"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\release_server"
# PROP Intermediate_Dir ".\release_server"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /G5 /MT /W3 /O2 /I "..\dlls" /I "..\engine" /I "..\common" /I "..\pm_shared" /I "..\game_shared" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /FD /c
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /def:".\server.def"
# SUBTRACT LINK32 /profile /map /debug
# Begin Custom Build - Custom Build in progress
TargetDir=.\release_server
InputPath=.\release_server\server.dll
SOURCE="$(InputPath)"

"..\..\..\cl_dlls\server.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetDir)\server.dll "..\..\..\cl_dlls\server.dll"

# End Custom Build

!ELSEIF  "$(CFG)" == "server - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "server___Win32_Debug"
# PROP BASE Intermediate_Dir "server___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\debug_server"
# PROP Intermediate_Dir ".\debug_server"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MT /W3 /O1 /I "..\dlls" /I "..\engine" /I "..\common" /I "..\pm_shared" /I "..\game_shared" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "QUIVER" /D "VOXEL" /D "QUAKE2" /D "VALVE_DLL" /YX /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /G5 /MT /W3 /Gm /ZI /Od /I "..\dlls" /I "..\engine" /I "..\common" /I "..\pm_shared" /I "..\game_shared" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /Fr /FD /c
# SUBTRACT CPP /WX /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o".\debug_server/server.bsc"
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386 /def:".\server.def" /out:".\debug_server/server.dll"
# SUBTRACT BASE LINK32 /profile /map /debug
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386 /def:".\server.def"
# SUBTRACT LINK32 /profile /map
# Begin Custom Build - Custom Build in progress
TargetDir=.\debug_server
InputPath=.\debug_server\server.dll
SOURCE="$(InputPath)"

"..\..\..\cl_dlls\server.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetDir)\server.dll "..\..\..\cl_dlls\server.dll"

# End Custom Build

!ENDIF 

# Begin Target

# Name "server - Win32 Release"
# Name "server - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\aflock.cpp
# End Source File
# Begin Source File

SOURCE=.\agrunt.cpp
# End Source File
# Begin Source File

SOURCE=.\airtank.cpp
# End Source File
# Begin Source File

SOURCE=.\alias.cpp
# End Source File
# Begin Source File

SOURCE=.\animating.cpp
# End Source File
# Begin Source File

SOURCE=.\animation.cpp
# End Source File
# Begin Source File

SOURCE=.\apache.cpp
# End Source File
# Begin Source File

SOURCE=.\barnacle.cpp
# End Source File
# Begin Source File

SOURCE=.\barney.cpp
# End Source File
# Begin Source File

SOURCE=.\bigmomma.cpp
# End Source File
# Begin Source File

SOURCE=.\bloater.cpp
# End Source File
# Begin Source File

SOURCE=.\bmodels.cpp
# End Source File
# Begin Source File

SOURCE=.\bullsquid.cpp
# End Source File
# Begin Source File

SOURCE=.\buttons.cpp
# End Source File
# Begin Source File

SOURCE=.\cbase.cpp
# End Source File
# Begin Source File

SOURCE=.\client.cpp
# End Source File
# Begin Source File

SOURCE=.\combat.cpp
# End Source File
# Begin Source File

SOURCE=.\controller.cpp
# End Source File
# Begin Source File

SOURCE=.\crossbow.cpp
# End Source File
# Begin Source File

SOURCE=.\crowbar.cpp
# End Source File
# Begin Source File

SOURCE=.\defaultai.cpp
# End Source File
# Begin Source File

SOURCE=.\doors.cpp
# End Source File
# Begin Source File

SOURCE=.\effects.cpp
# End Source File
# Begin Source File

SOURCE=.\egon.cpp
# End Source File
# Begin Source File

SOURCE=.\explode.cpp
# End Source File
# Begin Source File

SOURCE=.\flyingmonster.cpp
# End Source File
# Begin Source File

SOURCE=.\func_break.cpp
# End Source File
# Begin Source File

SOURCE=.\func_tank.cpp
# End Source File
# Begin Source File

SOURCE=.\game.cpp
# End Source File
# Begin Source File

SOURCE=.\gamerules.cpp
# End Source File
# Begin Source File

SOURCE=.\gargantua.cpp
# End Source File
# Begin Source File

SOURCE=.\gauss.cpp
# End Source File
# Begin Source File

SOURCE=.\genericmonster.cpp
# End Source File
# Begin Source File

SOURCE=.\ggrenade.cpp
# End Source File
# Begin Source File

SOURCE=.\globals.cpp
# End Source File
# Begin Source File

SOURCE=.\glock.cpp
# End Source File
# Begin Source File

SOURCE=.\gman.cpp
# End Source File
# Begin Source File

SOURCE=.\h_ai.cpp
# End Source File
# Begin Source File

SOURCE=.\h_battery.cpp
# End Source File
# Begin Source File

SOURCE=.\h_cine.cpp
# End Source File
# Begin Source File

SOURCE=.\h_cycler.cpp
# End Source File
# Begin Source File

SOURCE=.\h_export.cpp
# End Source File
# Begin Source File

SOURCE=.\handgrenade.cpp
# End Source File
# Begin Source File

SOURCE=.\hassassin.cpp
# End Source File
# Begin Source File

SOURCE=.\headcrab.cpp
# End Source File
# Begin Source File

SOURCE=.\healthkit.cpp
# End Source File
# Begin Source File

SOURCE=.\hgrunt.cpp
# End Source File
# Begin Source File

SOURCE=.\hornet.cpp
# End Source File
# Begin Source File

SOURCE=.\hornetgun.cpp
# End Source File
# Begin Source File

SOURCE=.\houndeye.cpp
# End Source File
# Begin Source File

SOURCE=.\ichthyosaur.cpp
# End Source File
# Begin Source File

SOURCE=.\islave.cpp
# End Source File
# Begin Source File

SOURCE=.\items.cpp
# End Source File
# Begin Source File

SOURCE=.\leech.cpp
# End Source File
# Begin Source File

SOURCE=.\lights.cpp
# End Source File
# Begin Source File

SOURCE=.\locus.cpp
# End Source File
# Begin Source File

SOURCE=.\maprules.cpp
# End Source File
# Begin Source File

SOURCE=.\monstermaker.cpp
# End Source File
# Begin Source File

SOURCE=.\monsters.cpp
# End Source File
# Begin Source File

SOURCE=.\monsterstate.cpp
# End Source File
# Begin Source File

SOURCE=.\mortar.cpp
# End Source File
# Begin Source File

SOURCE=.\movewith.cpp
# End Source File
# Begin Source File

SOURCE=.\mp5.cpp
# End Source File
# Begin Source File

SOURCE=.\multiplay_gamerules.cpp
# End Source File
# Begin Source File

SOURCE=.\nihilanth.cpp
# End Source File
# Begin Source File

SOURCE=.\nodes.cpp
# End Source File
# Begin Source File

SOURCE=.\osprey.cpp
# End Source File
# Begin Source File

SOURCE=.\pathcorner.cpp
# End Source File
# Begin Source File

SOURCE=.\plane.cpp
# End Source File
# Begin Source File

SOURCE=.\plats.cpp
# End Source File
# Begin Source File

SOURCE=.\player.cpp
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

SOURCE=.\python.cpp
# End Source File
# Begin Source File

SOURCE=.\rat.cpp
# End Source File
# Begin Source File

SOURCE=.\roach.cpp
# End Source File
# Begin Source File

SOURCE=.\rpg.cpp
# End Source File
# Begin Source File

SOURCE=.\satchel.cpp
# End Source File
# Begin Source File

SOURCE=.\schedule.cpp
# End Source File
# Begin Source File

SOURCE=.\scientist.cpp
# End Source File
# Begin Source File

SOURCE=.\scripted.cpp
# End Source File
# Begin Source File

SOURCE=.\shotgun.cpp
# End Source File
# Begin Source File

SOURCE=.\singleplay_gamerules.cpp
# End Source File
# Begin Source File

SOURCE=.\skill.cpp
# End Source File
# Begin Source File

SOURCE=.\sound.cpp
# End Source File
# Begin Source File

SOURCE=.\soundent.cpp
# End Source File
# Begin Source File

SOURCE=.\spectator.cpp
# End Source File
# Begin Source File

SOURCE=.\squadmonster.cpp
# End Source File
# Begin Source File

SOURCE=.\squeakgrenade.cpp
# End Source File
# Begin Source File

SOURCE=.\subs.cpp
# End Source File
# Begin Source File

SOURCE=.\talkmonster.cpp
# End Source File
# Begin Source File

SOURCE=.\teamplay_gamerules.cpp
# End Source File
# Begin Source File

SOURCE=.\tempmonster.cpp
# End Source File
# Begin Source File

SOURCE=.\tentacle.cpp
# End Source File
# Begin Source File

SOURCE=.\triggers.cpp
# End Source File
# Begin Source File

SOURCE=.\tripmine.cpp
# End Source File
# Begin Source File

SOURCE=.\turret.cpp
# End Source File
# Begin Source File

SOURCE=.\util.cpp
# End Source File
# Begin Source File

SOURCE=..\game_shared\voice_gamemgr.cpp
# End Source File
# Begin Source File

SOURCE=.\weapons.cpp
# End Source File
# Begin Source File

SOURCE=.\world.cpp
# End Source File
# Begin Source File

SOURCE=.\xen.cpp
# End Source File
# Begin Source File

SOURCE=.\zombie.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\activity.h
# End Source File
# Begin Source File

SOURCE=.\activitymap.h
# End Source File
# Begin Source File

SOURCE=.\animation.h
# End Source File
# Begin Source File

SOURCE=.\basemonster.h
# End Source File
# Begin Source File

SOURCE=.\cbase.h
# End Source File
# Begin Source File

SOURCE=.\cdll_dll.h
# End Source File
# Begin Source File

SOURCE=.\client.h
# End Source File
# Begin Source File

SOURCE=.\decals.h
# End Source File
# Begin Source File

SOURCE=.\defaultai.h
# End Source File
# Begin Source File

SOURCE=.\doors.h
# End Source File
# Begin Source File

SOURCE=.\effects.h
# End Source File
# Begin Source File

SOURCE=..\engine\eiface.h
# End Source File
# Begin Source File

SOURCE=.\enginecallback.h
# End Source File
# Begin Source File

SOURCE=.\explode.h
# End Source File
# Begin Source File

SOURCE=.\extdll.h
# End Source File
# Begin Source File

SOURCE=.\flyingmonster.h
# End Source File
# Begin Source File

SOURCE=.\func_break.h
# End Source File
# Begin Source File

SOURCE=.\gamerules.h
# End Source File
# Begin Source File

SOURCE=.\hornet.h
# End Source File
# Begin Source File

SOURCE=.\items.h
# End Source File
# Begin Source File

SOURCE=.\locus.h
# End Source File
# Begin Source File

SOURCE=.\monsterevent.h
# End Source File
# Begin Source File

SOURCE=.\monsters.h
# End Source File
# Begin Source File

SOURCE=.\movewith.h
# End Source File
# Begin Source File

SOURCE=.\nodes.h
# End Source File
# Begin Source File

SOURCE=.\plane.h
# End Source File
# Begin Source File

SOURCE=.\player.h
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

SOURCE=.\saverestore.h
# End Source File
# Begin Source File

SOURCE=.\schedule.h
# End Source File
# Begin Source File

SOURCE=.\scripted.h
# End Source File
# Begin Source File

SOURCE=.\scriptevent.h
# End Source File
# Begin Source File

SOURCE=.\skill.h
# End Source File
# Begin Source File

SOURCE=.\soundent.h
# End Source File
# Begin Source File

SOURCE=.\spectator.h
# End Source File
# Begin Source File

SOURCE=.\squadmonster.h
# End Source File
# Begin Source File

SOURCE=.\talkmonster.h
# End Source File
# Begin Source File

SOURCE=.\teamplay_gamerules.h
# End Source File
# Begin Source File

SOURCE=.\trains.h
# End Source File
# Begin Source File

SOURCE=.\util.h
# End Source File
# Begin Source File

SOURCE=.\vector.h
# End Source File
# Begin Source File

SOURCE=.\weapons.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
