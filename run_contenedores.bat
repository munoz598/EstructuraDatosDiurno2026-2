@echo off
setlocal

set "GCC=C:\Users\mariana\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin\gcc.exe"
set "SRC=%~dp0contenedores_portuarios.c"
set "OUT=%~dp0contenedores_portuarios.exe"

"%GCC%" "%SRC%" -o "%OUT%"
if errorlevel 1 (
    echo Error al compilar.
    exit /b %errorlevel%
)

echo Ejecutando programa...
"%OUT%"
