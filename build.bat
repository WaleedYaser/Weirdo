@echo off

REM TODO(Waleed): find better namae
set PROJECT_DIR=%~dp0
set OUTPUT_DIR=%PROJECT_DIR%build\

REM cleanup
rmdir /S /Q %OUTPUT_DIR%

call "%PROJECT_DIR%engine\build.bat"
REM TODO(Waleed): find a way for variable leak
set PROJECT_DIR=%~dp0
call "%PROJECT_DIR%playground\build.bat"
