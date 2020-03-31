@echo off

SETLOCAL

set PROJECT_NAME=playground
set PROJECT_DIR=%~dp0
set OUTPUT_DIR=%PROJECT_DIR%..\build\

set INCLUDE_DIRS=^
	/I %PROJECT_DIR%..\zero\include\^
	/I %PROJECT_DIR%..\kuro\include\

set LIBS=zero.lib

set SOURCE_FILES=%PROJECT_DIR%src\main.cpp

REM /MT  => compiles to create a multhreaded executable file using LIBCMT.lib
REM /nologo => Suppresses display of sign-on banner
REM /GR  => enable run-time type information
REM /Eh  =>
REM /Od  => disable optimization
REM /Oi  => generate intrinsic functions
REM /WX  => treats warnings as errors
REM /W4  => sets output warning level
REM /wd  => disable specified warning
REM /FC  => use full pathname in diagnostics
REM /Z7  => generates C 7.0-compativle debuggin information.
REM /Zi  => debuging information
REM /Fe: => name executable file
REM /Fm: => create a map file
set COMPILE_OPTIONS=/MT /nologo /GR- /EHa- /Od /Oi /WX /W4 /wd4201 /wd4100 /wd4109 /FC /Z7 /Fe: %PROJECT_NAME% /Fm: %PROJECT_NAMR%.map /std:c++17

REM /incremental =>
REM /opt		 =>
set LINK_OPTIONS=/incremental:no /opt:ref

if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%
pushd %OUTPUT_DIR%

cl %COMPILE_OPTIONS% %SOURCE_FILES% %INCLUDE_DIRS% /link %LINK_OPTIONS% %LIBS%

popd %OUTPUT_DIR%

ENDLOCAL
