@ECHO OFF
for /f "delims=" %%i in ('wsl wslpath -a .') do set CURRENT_PATH=%%i
start wt Ubuntu run emacs %CURRENT_PATH%
