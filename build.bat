copy "E:\SVN\branches\version.rc2" "E:\SVN\branches\whriaview\res\whriaview.rc2"
copy "E:\SVN\branches\version.rc2" "E:\SVN\branches\MedicalPhotoServer\res\MedicalPhotoServer.rc2"
copy "E:\SVN\branches\version.rc2" "E:\SVN\branches\Configure\res\Configure.rc2"
"D:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /build Release newconsole.sln
"D:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /build Release WhriaView.sln
"D:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /build Release Configure.sln
"D:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /build Release MedicalPhotoServer.sln
rem "D:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /build Release .\unreg\unreg.sln
rem "D:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /build Release .\XYNTServiceProject\XYNTService.sln

"c:\Program Files\autohotkey\compiler\Ahk2Exe.exe" /out "e:\svn\branches\release\Assist.exe" /in "d:\onedrive\CopyName.ahk" /icon "e:\svn\branches\release\green.ico"

"c:\Program Files (x86)\CreateInstall v4\ci" e:\svn\branches\medicalphoto.ci
"c:\Program Files (x86)\CreateInstall v4\ci" e:\svn\branches\medicalphoto_kor.ci
copy "E:\SVN\branches\release.txt" "\\i5\http\medicalphoto\repo\release\beta\release.txt"
copy "E:\SVN\branches\version.dat" "\\i5\http\medicalphoto\repo\release\beta\version.dat"
"C:\Program Files\7-Zip\7z.exe" a E:\SVN\branches\release\setup.zip E:\SVN\branches\release\setup.exe
"C:\Program Files\7-Zip\7z.exe" a E:\SVN\branches\release\setup_kor.zip E:\SVN\branches\release\setup_kor.exe
copy "E:\SVN\branches\release\setup.zip" "\\i5\http\medicalphoto\repo\release\beta\setup.zip"
copy "E:\SVN\branches\release\setup_kor.zip" "\\i5\http\medicalphoto\repo\release\beta\setup_kor.zip"
copy "E:\SVN\branches\release\setup.exe" "\\i5\http\medicalphoto\repo\release\beta\setup.exe"
copy "E:\SVN\branches\release\setup_kor.exe" "\\i5\http\medicalphoto\repo\release\beta\setup_kor.exe"
