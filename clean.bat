"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /clean Release WhriaView.sln
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /clean Debug WhriaView.sln
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /clean Release Configure.sln
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /clean Debug Configure.sln
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /clean Release newconsole.sln
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /clean Debug newconsole.sln
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /clean Release MedicalPhotoServer.sln
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /clean Debug MedicalPhotoServer.sln
:: 삭제할 개별 파일들
del /s *.plg *.ncb *.aps *.opt *.clw *.obj *.idb *.pch *.res *.pdb *.scc *.sbr *.exp *.bsc *.ilk *.tmp *.log *.VC.db
del /s *.tlog *.user *.ipdb *.iobj

:: 삭제할 폴더들
rmdir /s /q ipch
rmdir /s /q .vs
rmdir /s /q Debug
