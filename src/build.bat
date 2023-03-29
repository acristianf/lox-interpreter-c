@echo off

REM call vcvarsall x64

set CommonCompilerFlags=-MT -nologo -Gm- -GR- -EHa- -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4211
REM set CommonLinkerFlags=-opt:ref User32.lib Gdi32.lib Winmm.lib

mkdir ..\build
pushd ..\build

REM 32-bit build
REM cl %CommonCompilerFlags% -DHANDMADE_INTERNAL=1 -DHANDMADE_SLOW=1 -FC -Z7 -Fmwin32_handmade.map ..\code\win32_handmade.cpp /link -subsystem:windows,5.1 %CommonLinkerFlags%

REM 64-bit build
cl %CommonCompilerFlags% -FC -Z7 ..\src\main.cpp
popd
