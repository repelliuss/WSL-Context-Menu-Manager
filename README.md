# Context Menu Manager for WSL
> Bothered to open WSL everytime?

## Table of Contents
* [General Info](#general-info)
* [Features](#features)
* [How to Get](#how-to-get)
* [How to Use](#how-to-use)
  * [To add to context menu](#to-add-to-context-menu)
  * [To delete from context menu](#to-delete-from-context-menu)
  * [Using Custom Icon](#using-custom-icon)
  * [About Environment Variables](#about-environment-variables)

<p align="center"><img src="https://media.giphy.com/media/YquZK48hAghQYdd2UB/source.gif" width="477" height="422" /></p>
<p align="center"> <i>Adding Vim to Context Menu</i> </p>

<p align="center"><img src="https://media.giphy.com/media/kH6H6fjrpNSvvMIInf/source.gif" width="477" height="422" /></p>
<p align="center"> <i>Deleting Vim from Context Menu</i> </p>

<p align="center"><img src="https://media.giphy.com/media/kFBvGEm63Vf0RKiFrx/source.gif" width="477" height="422" /></p>
<p align="center"> <i>Adding Emacs to Context Menu</i> </p>

## General Info
&nbsp;&nbsp;&nbsp;&nbsp;WSL Context Menu Manager utilizes Windows' context menu for Linux tools with the ease of use. Although Windows specifies that file performance across the Windows and Linux operating systems is faster with WSL 1, some may still want to achieve that usability with WSL 2.

## Features
- Opening all files
- Opening current directory
- Custom icons in the context menu
- GUI application support for WSL 2
- Environment variables support
- Custom launch arguments

## How to Get

1. You can clone repository to your local and begin to use. There you can compile `.cpp` files in `bin` folder yourself if you want.
2. You can also get clean version by [clicking here!](https://github.com/repelliuss/WSL-Context-Menu-Manager/releases/latest)

## How to Use

&nbsp;&nbsp;&nbsp;&nbsp; Before adding any tool to your context menu, decide where to put *WSL Context Menu Manager*. Don't change the directory name or location without deleting all the tools. You can always manually delete though.

### To add to context menu

1. Run `add_to_context_menu.bat`. 
1. It will ask for admin privileges to manage registries in the system from Command Prompt. You'll be able to view context of last added registry. You can check the general content of constructed register in the screenshot down below.
1. Answer the questions appropriately.

#### First Question: What is the launch command in WSL?
&nbsp;&nbsp;&nbsp;&nbsp;The idea behind this, take the launch command user gave and append launch path with a blank space at the end. Creating a generic script for all the tools is hard. My assumption is, tools are capable of undestanding the string all alone at the end of launch command.

&nbsp;&nbsp;&nbsp;&nbsp;If your tool doesn't understand the path at the end, you may need to use a specific command line option. Use that option at the end of your launch command. Leave its value empty because launch path will be appended to end of your launch command.

&nbsp;&nbsp;&nbsp;&nbsp;You can always go to the `scripts` folder and edit the script of your tool manually to meet your needs.

#### Second Question: Is this a GUI app?
&nbsp;&nbsp;&nbsp;&nbsp; If you use a X Server for your app, you need to answer with `y`. Otherwise it shouldn't matter. 

<p align="center"><img src="https://i.imgur.com/O5YBK94.png">
<p align="center"> <i>Possible Adding Scenario</i> </p>

<p align="center"><img src="https://i.imgur.com/ah7N7KN.png">
<p align="center"> <i>General Content of Constructed Register</i> </p>

### To delete from context menu
1. Run `delete_from_context_menu.bat`. 
2. It will ask for admin privileges to manage registries in the system from Command Prompt.
3. Answer the questions appropriately.

Answer to the first question `What is the app name you want to delete?:` should be identical to the first word of launch command you wrote while adding to context menu.

<p align="center"><img src="https://i.imgur.com/a1oQ4Ox.png">
<p align="center"> <i>Possible Deleting Scenario</i> </p>

### Using custom icon
* Put your `.ico` file to `icons` folder in this way: `XXX.ico`. XXX is the name of the app you are going to give while adding that app to context menu. XXX must be identical with your answer.
* You must do this before adding to context menu.
* Sometimes if you replace your new `.ico` file with the existed name, Windows shows the old icon. You need to run this code `ie4uinit.exe -show` or you can restart your computer.

### About Environment Variables

&nbsp;&nbsp;&nbsp;&nbsp;WSL doesn't see your exported variables within the outer terminal. Which means you can't launch your app in Linux with the command line arguments, as you normally do in Linux if you exported some variable for it, while starting WSL.

&nbsp;&nbsp;&nbsp;&nbsp;If you export something to launch, then follow these instructions.

1. Open `Edit environment variables for your account` in Windows.
* If you're exporting your variable to your `PATH` variable,
  1. Add an environment variable named `WSLPATH` to Windows.
  2. Set its value to what you want to export in Linux.
  3. If you want to export multiple values to your `PATH`, seperate them with `:`.
* If you're exporting a variable,
  1. Add an environment variable named `WSLEXPORT`.
  2. Set its value to what you want to export in Linux.
  3. If you want to export multiple values to your `PATH`, seperate them with ` `, blank space.

<p align="center"><img src="https://i.imgur.com/1IjCU7R.png">
<p align="center"> <i>Environment Variables</i> </p>
