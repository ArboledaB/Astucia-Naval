@echo off
echo ================================
echo   Compilando ASTUCIA NAVAL...
echo ================================

rem
if not exist build mkdir build

rem
cl /std:c++17 /EHsc /I include src\*.cpp main.cpp /Fo:build\ /Fe:build\astucia_naval.exe

if %errorlevel% neq 0 (
    echo.
    echo ❌ ERROR: La compilacion fallo.
    pause
    exit /b %errorlevel%
) else (
    echo.
    echo ✅ Compilacion exitosa!
    echo Ejecutando el juego...
    echo ================================
    build\astucia_naval.exe
)

pause
