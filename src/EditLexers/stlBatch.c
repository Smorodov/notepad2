#include "EditLexer.h"
#include "EditStyleX.h"

static KEYWORDLIST Keywords_Batch = {{
//++Autogenerated -- start of section automatically generated
"assoc break call cd chdir cls cmdextversion color copy "
"date defined del dir disabledelayedexpansion disableextensions do "
"echo echo. else enabledelayedexpansion enableextensions endlocal equ erase errorlevel exist exit for ftype geq goto gtr "
"if in leq lss md mkdir mklink move neq not nul path pause popd prompt pushd rd rem ren rename rmdir "
"set setlocal shift start time title type ver verify vol "

, // 1 system commands
"active add append arp assign at atmadm attach-vdisk attrib attributes auditpol autochk autoconv autofmt automount "
"bcdboot bcdedit bdehdcfg begin bitsadmin bootcfg "
"cacls certreq certutil change chcp chglogon chgport chgusr chkdsk chkntfs choice cipher clean cleanmgr clip "
"cmd cmdkey cmstp comp compact convert cprofile create cscript "
"dcgpofix defrag delete detach detail dfsdiag dfsrmig "
"diantz diskcomp diskcopy diskpart diskperf diskraid diskshadow dispdiag dnscmd doskey driverquery "
"edit end eventcreate eventquery eventtriggers exec expand expose extend extract "
"fc filesystems find findstr finger flattemp fondue forfiles format freedisk fsutil ftp fveupdate "
"getmac gettype gpfixup gpresult gpt gpupdate graftabl help helpctr hostname "
"icacls import inactive inuse ipconfig ipxroute irftp jetpack klist ksetup ktmutil ktpass "
"label list load lodctr logman logoff lpq lpr "
"macfile makecab manage mapadmin merge mmc mode more mount mountvol mqbkup mqsvc mqtgsvc msdt msg msiexec msinfo32 mstsc "
"nbtstat net netcfg netsh netstat nfsadmin nfsshare nfsstat nlbmgr nslookup ntbackup ntcmdprompt ntfrsutl "
"offline online openfiles "
"pagefileconfig pathping pbadmin pentnt perfmon ping pnpunattend pnputil powershell "
"print prncnfg prndrvr prnjobs prnmngr prnport prnqctl pubprn pushprinterconnections pwlauncher "
"qappsrv qprocess query quser qwinsta "
"rcp rdpsign recover refsutil reg regini regsvr32 relog remove repair replace rescan reset retain revert rexec risetup "
"robocopy route rpcinfo rpcping rsh rundll32 rwinsta "
"san sc schtasks scwcmd secedit select serverceipoptin servermanagercmd serverweroptin setx sfc "
"shadow showmount shrink shutdown simulate sort subcommand subst sxstrace sysocmgr systeminfo "
"takeown tapicfg taskkill tasklist tcmsetup telnet tftp timeout tlntadmn tpmtool tpmvscmgr tracerpt tracert tree "
"tscon tsdiscon tsecimp tskill tsprof typeperf tzutil "
"unexpose uniqueid unlodctr verifier vssadmin "
"waitfor wbadmin wdsutil wecutil wevtutil where whoami winnt winnt32 winpop winrs winsat wmic writer wscript xcopy "

, // 2 upper case keywords / commands
"ASSOC ATTRIB BCDEDIT BREAK "
"CACLS CALL CD CHCP CHDIR CHKDSK CHKNTFS CLS CMD CMDEXTVERSION COLOR COMP COMPACT CONVERT COPY CmdExtVersion "
"DATE DEFINED DEL DIR DISABLEDELAYEDEXPANSION DISABLEEXTENSIONS DISKPART DO DOSKEY DRIVERQUERY "
"DisableDelayedExpansion DisableExtensions "
"ECHO ECHO. ELSE ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS ENDLOCAL EQU ERASE ERRORLEVEL EXIST EXIT "
"EnableDelayedExpansion EnableExtensions EndLocal ErrorLevel Evntcmd "
"FC FIND FINDSTR FOR FORMAT FSUTIL FTYPE GEQ GOTO GPRESULT GRAFTABL GTR HELP ICACLS IF IN LABEL LEQ LSS "
"MD MKDIR MKLINK MODE MORE MOVE NEQ NOT NUL OPENFILES PATH PAUSE POPD PRINT PROMPT PUSHD "
"RD RECOVER REM REN RENAME REPLACE RMDIR ROBOCOPY "
"SC SCHTASKS SET SETLOCAL SHIFT SHUTDOWN SORT START SUBST SYSTEMINFO SetLocal TASKKILL TASKLIST TIME TITLE TREE TYPE "
"VER VERIFY VOL WMIC XCOPY "

, // 3 environment variables
"ALLUSERSPROFILE APPDATA AllUsersProfile AppData "
"CMDCMDLINE COMPUTERNAME CmdCmdLine ComSpec CommonProgramFiles CommonProgramFiles(x86) CommonProgramW6432 ComputerName "
"DriverData ExitCode ExitCodeAscii HIGHESTNUMANODENUMBER HOMEDRIVE HOMEPATH HighestNumaNodeNumber HomeDrive HomePath "
"LOCALAPPDATA LOGONSERVER LocalAppData LogonServer NUMBER_OF_PROCESSORS OS "
"PATHEXT PROCESSOR_ARCHITECTURE PROCESSOR_IDENTIFIER PROCESSOR_LEVEL PROCESSOR_REVISION PSModulePath PUBLIC "
"ProgramData ProgramFiles ProgramFiles(x86) ProgramW6432 "
"RANDOM Random SESSIONNAME SessionName SystemDrive SystemRoot TEMP TMP "
"USERDOMAIN USERDOMAIN_ROAMINGPROFILE USERNAME USERPROFILE UserDomain UserDomain_RoamingProfile UserName UserProfile "
"WINDIR __APPDIR__ __AppDir__ __CD__ random windir "

, // 4 command options
"ABOVENORMAL AFFINITY BELOWNORMAL EOF HIGH LOW MAX MIN NODE NORMAL REALTIME SEPARATE SHARED WAIT "
"abovenormal addenctypeattr addfile addfileset addfilewithranges addhosttorealmmap addkdc addkpasswd addrealmflags addsw "
"affinity alert alias all analyze and api ascii autounlock "
"backup basic bde behavior bell belownormal binary bye "
"cache cancel catalog cfg changekey changepassword changepin class clear close "
"compare complete config configure context counter "
"d2 dbg1394 debug default delenctypeattr deleteurl delhosttorealmmap delims delkdc delkpasswd delrealmflags device "
"dirty disable disconnect discover disk disks display domain driveinfo drivergroup drivergroupfilter driverpackage "
"dumpstate dynamic "
"efi ems enable enableanalyticchannel environmental eof eol examples export extended file forcerecovery fsinfo "
"generaterollback get getaclflags getbytestotal getbytestransferred "
"getclientcertificate getcompletiontime getconfigurationflags getcreationtime getcustomheaders "
"getdescription getdisplayname getenctypeattr geterror geterrorcount getexpirationtime getfilestotal getfilestransferred "
"gethelpertokenflags gethelpertokensid gethttpmethod getieproxy getlimit "
"getmaxdownloadtime getminretrydelay getmodificationtime "
"getnoprogresstimeout getnotifycmdline getnotifyflags getnotifyinterface getowner "
"getpeercachingflags getpriority getproxybypasslist getproxylist getproxyusage "
"getreplydata getreplyfilename getreplyprogress getsecurityflags getstate gettemporaryname getvalidationstate glob group "
"hardlink hash high id image imagegroup info ise items job keypackage "
"lcd listfiles listrealmflags literal lock logical logon low ls lserver "
"makecustomheaderswriteonly mapuser max mbr mdelete mdir mem metadata mfmedia mget min mirror mls monitor mput msr "
"multicasttransmission "
"namespace newdriveletter node normal nowrap objectid off on open option "
"partition peercaching peers port primary printui process protectors providers put pwd querytype quiet quit quota quote "
"raid raw rawreturn realtime recovery recurse recv register "
"remotehelp removeclientcertificate removecredentials removerealm repairservice reparsepoint replaceremoteprefix "
"resize resource resourcesacl restart restore resume retry rmsw rollback root "
"save search send separate server session setaclflag setclientcertificatebyid setclientcertificatebyname "
"setcomputerpassword setconfigurationflags setcredentials setcustomheaders setdescription setdisplayname "
"setenctypeattr setexpirationtime sethelpertoken sethelpertokenflags sethttpmethod setidentifier setieproxy setlimit "
"setmaxdownloadtime setminretrydelay setnoprogresstimeout setnotifycmdline setnotifyflags "
"setpeercachingflags setpriority setproxysettings setrealm setrealmflags setreplyfilename setsecurityflags "
"setvalidationstate shadows shadowstorage shared simple size skip sparse srchlist status stop stripe suspend "
"sysrecovery systemstatebackup systemstaterecovery "
"takeownership target termserver testdcs testdfsconfig testdfsintegrity testreferral testsites tiering tokens tpm "
"trace transaction transfer transform transportserver "
"unload unlock unset update upgrade usebackq user usn util "
"validate variables vc vdisk verbose version versions view volume wait wim wipefreespace wrap writers ws2008 "

, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
//--Autogenerated -- end of section automatically generated
}};

static EDITSTYLE Styles_Batch[] = {
	EDITSTYLE_DEFAULT,
	{ SCE_BAT_WORD, NP2StyleX_Keyword, L"bold; fore:#FF8000" },
	{ SCE_BAT_COMMAND, NP2StyleX_Command, L"bold; fore:#0080FF" },
	{ SCE_BAT_COMMENT, NP2StyleX_Comment, L"fore:#008000" },
	{ SCE_BAT_STRINGDQ, NP2StyleX_DoubleQuotedString, L"fore:#008080" },
	{ SCE_BAT_STRINGSQ, NP2StyleX_SingleQuotedString, L"fore:#C08000" },
	{ SCE_BAT_STRINGBT, NP2StyleX_Backticks, L"fore:#F08000" },
	{ SCE_BAT_ESCAPE, NP2StyleX_EscapeSequence, L"fore:#FF0000" },
	{ SCE_BAT_VARIABLE, NP2StyleX_Variable, L"fore:#003CE6; back:#FFF1A8" },
	{ SCE_BAT_OPERATOR, NP2StyleX_Operator, L"fore:#B000B0" },
	{ MULTI_STYLE(SCE_BAT_LABEL, SCE_BAT_LABEL_LINE, 0, 0), NP2StyleX_Label, L"fore:#C80000; back:#F4F4F4; eolfilled" },
};

EDITLEXER lexBatch = {
	SCLEX_BATCH, NP2LEX_BATCH,
	SCHEME_SETTINGS_DEFAULT,
	EDITLEXER_HOLE(L"Batch File", Styles_Batch),
	L"bat; cmd",
	&Keywords_Batch,
	Styles_Batch
};
