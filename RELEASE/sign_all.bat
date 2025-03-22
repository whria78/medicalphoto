@echo off
setlocal enabledelayedexpansion

:: 설정 (필요에 따라 수정)
set CERT_NAME="Your Certificate Name"   :: EV 인증서(USB 토큰) 사용 시
set CERT_PFX=""  :: PFX 파일 경로 (PFX 사용 시)
set CERT_PASSWORD="your_password"   :: PFX 비밀번호
set TIMESTAMP_SERVER="http://timestamp.digicert.com"
set SIGNTOOL="C:\Program Files (x86)\Windows Kits\10\bin\10.0.26100.0\x64\signtool.exe"

:: 현재 폴더 기준
set TARGET_FOLDER="%CD%"

:: 로그 파일 설정
set LOG_FILE="%TARGET_FOLDER%\sign_log.txt"
echo Signing process started at %DATE% %TIME% > %LOG_FILE%

:: 현재 폴더 및 하위 폴더의 모든 .exe 및 .dll 파일 찾기
for /r %TARGET_FOLDER% %%F in (*.exe *.dll) do (
    echo Signing %%F...
    
    if exist %CERT_PFX% (
        :: PFX 인증서 사용
        %SIGNTOOL% sign /f %CERT_PFX% /p %CERT_PASSWORD% /tr %TIMESTAMP_SERVER% /td sha256 /fd sha256 "%%F" >> %LOG_FILE% 2>&1
    ) else (
        :: EV 인증서 (USB 토큰) 사용
        %SIGNTOOL% sign /n %CERT_NAME% /tr %TIMESTAMP_SERVER% /td sha256 /fd sha256 "%%F" >> %LOG_FILE% 2>&1
    )

    if %ERRORLEVEL% == 0 (
        echo Successfully signed: %%F
        echo Successfully signed: %%F >> %LOG_FILE%
    ) else (
        echo Failed to sign: %%F
        echo Failed to sign: %%F >> %LOG_FILE%
    )
)

echo Signing process completed at %DATE% %TIME% >> %LOG_FILE%
echo Done! Check the log file: %LOG_FILE%
exit /b
