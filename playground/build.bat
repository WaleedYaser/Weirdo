@echo off

set PROJECT_NAME=playground
set PROJECT_DIR=%~dp0
set OUTPUT_DIR=%PROJECT_DIR%..\build\

set INCLUDE_DIRS=^
	%PROJECT_DIR%include\

set LIBS=User32.lib Gdi32.lib

REM TODO(Waleed): find better way for writing lists and escape tabs
set SOURCE_FILES=^
	%PROJECT_DIR%src\main.cpp^
	%PROJECT_DIR%src\os\Window.cpp^
	%PROJECT_DIR%src\os\Bitmap.cpp

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
set COMPILE_OPTIONS=/MT /nologo /GR- /EHa- /Od /Oi /WX /W4 /wd4201 /wd4100 /wd4109 /FC /Z7 /Fe: %PROJECT_NAME% /Fm: %PROJECT_NAMR%.map

REM /incremental =>
REM /opt		 =>
set LINK_OPTIONS=/incremental:no /opt:ref

mkdir %OUTPUT_DIR%
pushd %OUTPUT_DIR%

cl %COMPILE_OPTIONS% %SOURCE_FILES% /I %INCLUDE_DIRS% /link %LINK_OPTIONS% %LIBS%

popd %OUTPUT_DIR%
