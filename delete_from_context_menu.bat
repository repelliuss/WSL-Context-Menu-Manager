@echo off

    IF "%PROCESSOR_ARCHITECTURE%" EQU "amd64" (
>nul 2>&1 "%SYSTEMROOT%\SysWOW64\cacls.exe" "%SYSTEMROOT%\SysWOW64\config\system"
) ELSE (
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"
)

if '%errorlevel%' NEQ '0' (
    echo Requesting administrative privileges...
    goto UACPrompt
) else ( goto gotAdmin )

:UACPrompt
    echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
    set params= %*
    echo UAC.ShellExecute "cmd.exe", "/c ""%~s0"" %params:"=""%", "", "runas", 1 >> "%temp%\getadmin.vbs"

    "%temp%\getadmin.vbs"
    del "%temp%\getadmin.vbs"
    exit /B

:gotAdmin
    pushd "%CD%"
    CD /D "%~dp0"

set /p app="What is the app name you want to delete?: "

if not [%app%] == [] (
   set /p open_file="Do you want to remove launching from all files? (y/n): "
   set /p open_background="Do you want to remove opening it from current directory? (y/n): "
) else (
   echo No app name, terminating...
   pause
   exit /B
)

if not [%open_file%] == [y] if NOT [%open_background%] == [y] (

   echo No operation needed, terminating...
   pause
   exit /B
)

bin\\delete_builder.exe %app%, %open_file%, %open_background%,

if not %ERRORLEVEL% == 0 (
   echo Files couldn't be builded, terminating...
   pause
   exit /B
)

deleter_script.bat