@echo off
:: 设置目标 exe 文件的原始路径
set ORIGINAL_EXE_PATH="D:\Pacman-master\PACMAN\Debug\main.exe"
set RENAMED_EXE_NAME="PacMan.exe"
set CURRENT_DIR=%cd%

:: 输出当前操作信息
echo Moving main.exe from %ORIGINAL_EXE_PATH% to current directory: %CURRENT_DIR%...

:: 检查目标 exe 文件是否存在于原始路径
if exist %ORIGINAL_EXE_PATH% (
    echo File found, proceeding with move operation...

    :: 将目标 exe 文件移动到当前目录
    move "%ORIGINAL_EXE_PATH%" "%CURRENT_DIR%\main.exe"
    if %errorlevel% neq 0 (
        echo Error: Failed to move the file. Exiting script...
        pause
        exit /b
    )

    echo File moved successfully. Renaming to PacMan.exe...

    :: 在当前目录中将 main.exe 重命名为 PacMan.exe
    ren "%CURRENT_DIR%\main.exe" %RENAMED_EXE_NAME%
    if %errorlevel% neq 0 (
        echo Error: Failed to rename the file. Exiting script...
        pause
        exit /b
    )

    echo File renamed successfully. Deleting original file if it still exists...

    :: 检查原始目录是否还存在 main.exe，如果存在则删除（防止移动失败）
    if exist %ORIGINAL_EXE_PATH% (
        del "%ORIGINAL_EXE_PATH%"
        echo Original file deleted.
    ) else (
        echo Original file not found in original directory, it was moved successfully.
    )

    echo Launching the new executable: PacMan.exe...
    start "" "%CURRENT_DIR%\%RENAMED_EXE_NAME%"

    echo Program launched successfully.

) else (
    echo Error: File not found at %ORIGINAL_EXE_PATH%. Please check if the path is correct.
)

:: 暂停脚本，防止窗口自动关闭
pause
