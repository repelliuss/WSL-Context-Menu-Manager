@echo off

set /p launch_command="What is the launch command in WSL?: "
for /f "tokens=1" %%i in ("%launch_command%") do set app=%%i

if not [%app%] == [] (

   set /p is_gui="Is this a GUI app? (y/n): "
   set term_launch=cmd
   set /p term_launch="What is your terminal launch command? (default: cmd): "
   set /p open_file="Do you want to launch all files with it? (y/n): "
   set /p open_background="Do you want to open it on current directory? (y/n): "
) else (
   echo No launch command, terminating...
   pause
   exit /B
)

if not [%open_file%] == [y] if NOT [%open_background%] == [y] (

   echo No operation needed, terminating...
   pause
   exit /B
)

if EXIST ".\\icons\\%app%.ico" set with_icon=y

set display_number=0
if [%is_gui%] == [y] (
   set /p display_number="What is the display number? (default: 0): "
)

bin\\add_builder.exe %cd%\, %launch_command%, %app%, %is_gui%, %term_launch%, %open_file%, %open_background%, %display_number%, %with_icon%,

if not %ERRORLEVEL% == 0 (
   echo Files couldn't be builded, terminating...
   pause
   exit /B
)

reg import context-menu.reg
pause
