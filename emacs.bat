@ECHO OFF
for /f "delims=" %%i in ('wsl wslpath -a .') do set CURRENT_PATH=%%i
start wt wsl emacs %CURRENT_PATH%
