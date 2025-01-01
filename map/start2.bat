@echo off
:: 设置目标 exe 文件路径
set ORIGINAL_EXE_PATH="D:\Pacman-master\PACMAN\Debug\main.exe"
set RENAMED_EXE_PATH="PacMan.exe"

:: 模拟编译过程
echo Compiling the source code...
timeout /t 2 >nul
echo Compilation complete.

:: 模拟链接过程
echo Linking the object files...
timeout /t 2 >nul
echo Linking complete.

:: 检查目标 exe 文件是否存在
if exist %ORIGINAL_EXE_PATH% (
    echo Building project successful!
    echo Renaming the original executable to PacMan.exe...
    
    :: 将目标 exe 文件重命名为 PacMan.exe
    ren %ORIGINAL_EXE_PATH% %RENAMED_EXE_PATH%
    
    echo Copying the renamed executable to current directory...
    :: 将重命名后的文件复制到当前目录
    copy "%RENAMED_EXE_PATH%" "%cd%\%RENAMED_EXE_PATH%"
    
    echo Deleting the original executable...
    :: 删除原路径下的文件
    del "%ORIGINAL_EXE_PATH%"
    
    echo Launching the executable from current directory...

    :: 启动当前目录下的 PacMan.exe 文件
    start "" "%cd%\%RENAMED_EXE_PATH%"

    echo Program is running...

    :: 等待 3 秒以便查看程序启动过程，然后继续
    timeout /t 3 >nul

    echo Program executed successfully.
) else (
    echo File not found: %ORIGINAL_EXE_PATH%. Please check if the path is correct.
)

:: 停止脚本并等待用户按键，防止窗口自动关闭
pause
