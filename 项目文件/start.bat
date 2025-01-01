@echo off
:: 设置目标 exe 文件名
set EXE_NAME="PacMan.exe"

:: 检查当前目录中是否存在目标 exe 文件
if exist "%EXE_NAME%" (
    
    echo Launching the executable...

    :: 启动当前目录中的 PacMan.exe
    start "" "%cd%\%EXE_NAME%"

    echo Program launched successfully.
) else (
    echo Error: %EXE_NAME% not found in the current directory. Please check if the file exists.
)

