@echo off
REM Batch file to run the copy_recent_files_since_date.py script
REM Copies all .fcfx/.fcsx/.fcweb files modified since 2026-06-26,
REM regardless of whether they were already copied before.

echo Running file copy script (since 26 June 2026)...
echo.

python copy_recent_files_since_date.py

echo.
echo Script execution completed.
pause
