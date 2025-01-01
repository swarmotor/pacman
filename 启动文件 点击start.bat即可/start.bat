@echo off
:: 设置目标 exe 文件名以及路径
set EXE_PATH="D:\Pacman-master\map\PacMan.exe"

:: 检查目标目录中是否存在目标 exe 文件
if exist "%EXE_PATH%" (
    echo Launching the executable...

    :: 启动目标目录中的 PacMan.exe
    start "" "%EXE_PATH%"

    echo Program launched successfully.
) else (
    echo Error: %EXE_PATH% not found. Please check if the file exists.
)


