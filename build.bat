@echo off

call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd" -arch=amd64

SETLOCAL

REM TODO(Waleed): find better name
set PROJECT_DIR=%~dp0
set OUTPUT_DIR=%PROJECT_DIR%build\

REM cleanup
REM rmdir /S /Q %OUTPUT_DIR%

call "%PROJECT_DIR%zero\build.bat"
call "%PROJECT_DIR%kuro\build.bat"
call "%PROJECT_DIR%playground\build.bat"

ENDLOCAL
