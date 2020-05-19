@echo OFF
for /f "delims=" %%i in ('wsl wslpath -a .') do set launch_path=%%i
start wt wsl emacs %launch_path%
