@echo off
:: Создание директории Build, если она не существует
if not exist "Build" mkdir Build
cd Build

:: Удаление папки .vs
if exist ".vs" rmdir /S /Q ".vs"

:: Очистка старых зависимостей и кэша CMake
del /F /S /Q _deps
del /F /S /Q CMakeCache.txt

:: Запуск CMake для пересборки проекта
cmake .. -G "Visual Studio 17 2022" -DCMAKE_POLICY_VERSION_MINIMUM=3.5

echo Сборка завершена.
pause
