@echo off
echo ================================
echo   Limpiando proyecto ASTUCIA NAVAL...
echo ================================

rem Borrar ejecutable si existe
if exist build\astucia_naval.exe (
    del /Q build\astucia_naval.exe
    echo Ejecutable eliminado.
)

rem Borrar todos los .obj en la carpeta build
del /Q build\*.obj >nul 2>&1

rem Eliminar carpeta build si esta vacía
for /f %%i in ('dir /b build') do set found=1
if not defined found (
    rmdir build
    echo Carpeta build eliminada.
)

echo ✅ Limpieza completada.
pause
