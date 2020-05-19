@echo OFF
set launch_path=%1
for /f "delims=" %%i in ('wsl wslpath -a %launch_path%') do set launch_path=%%i
start wt wsl emacs "%launch_path%"
