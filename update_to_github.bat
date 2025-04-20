@echo off
REM Получаем текущую директорию, где находится батник
set REPO_DIR=%~dp0
cd /d "%REPO_DIR%"

REM Проверяем, что мы находимся в правильном репозитории
if not exist ".git" (
    echo This is not a git repository. Exiting...
    pause
    exit /b
)

REM Получение последних изменений из форка
echo Pulling changes from GitHub...
git pull origin enhanced

REM Пуш изменений в форк на GitHub
echo Pushing changes to GitHub...
git add -A
git commit -m "Updated local changes"
git push origin enhanced

REM Завершение
echo Changes pushed to GitHub successfully!
pause
