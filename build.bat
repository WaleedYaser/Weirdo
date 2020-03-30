@echo off

SETLOCAL

REM TODO(Waleed): find better name
set PROJECT_DIR=%~dp0
set OUTPUT_DIR=%PROJECT_DIR%build\

REM cleanup
rmdir /S /Q %OUTPUT_DIR%

call "%PROJECT_DIR%kuro\build.bat"
call "%PROJECT_DIR%playground\build.bat"

ENDLOCAL
