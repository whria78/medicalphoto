copy "D:\Documents and Settings\Han Seung Seog\Desktop\readme.pdf" "E:\SVN\branches\readme.pdf"
copy "E:\SVN\branches\readme.pdf" "\\10.0.0.2\www\medicalphoto\repo\update\readme.pdf"

copy "E:\SVN\branches\version.rc2" "E:\SVN\branches\whriaview\res\whriaview.rc2"
copy "E:\SVN\branches\version.rc2" "E:\SVN\branches\MedicalPhotoServer\res\MedicalPhotoServer.rc2"
copy "E:\SVN\branches\version.rc2" "E:\SVN\branches\Configure\res\Configure.rc2"

"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" /build Release "E:\SVN\branches\newconsole.sln"

"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" /build Release "E:\SVN\branches\WhriaView.sln"
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" /build Release "E:\SVN\branches\Configure.sln"
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" /build Release "E:\SVN\branches\MedicalPhotoServer.sln"
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" /build Release "E:\SVN\branches\unreg\unreg.sln"
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" /build Release "E:\SVN\branches\XYNTServiceProject\XYNTService.sln"
"c:\Program Files\CreateInstall v4\ci" e:\svn\branches\medicalphoto.ci
copy "E:\SVN\branches\release.txt" "\\10.0.0.2\www\medicalphoto\repo\release\beta\release.txt"
copy "E:\SVN\branches\version.dat" "\\10.0.0.2\www\medicalphoto\repo\release\beta\version.dat"

copy "E:\SVN\branches\release\medicalphoto.exe" "\\10.0.0.2\www\medicalphoto\repo\update\MedicalPhoto.exe"
copy "E:\SVN\branches\release\medicalphotoServer.exe" "\\10.0.0.2\www\medicalphoto\repo\update\MedicalPhotoServer.exe"
copy "E:\SVN\branches\release\console.exe" "\\10.0.0.2\www\medicalphoto\repo\update\console.exe"
copy "E:\SVN\branches\release\config.exe" "\\10.0.0.2\www\medicalphoto\repo\update\Config.exe"
copy "E:\SVN\branches\release\unreg.exe" "\\10.0.0.2\www\medicalphoto\repo\update\unreg.exe"
copy "E:\SVN\branches\release\MedicalPhotoService.exe" "\\10.0.0.2\www\medicalphoto\repo\update\MedicalPhotoService.exe"
copy "E:\SVN\branches\release\MedicalPhotoService.ini" "\\10.0.0.2\www\medicalphoto\repo\update\MedicalPhotoService.ini"
copy "E:\SVN\branches\version.dat" "\\10.0.0.2\www\medicalphoto\repo\update\version.dat"
copy "E:\SVN\branches\diagnosis\icd10.dat" "\\10.0.0.2\www\medicalphoto\repo\update\diagnosis\icd10.dat"
copy "E:\SVN\branches\diagnosis\derma.dat" "\\10.0.0.2\www\medicalphoto\repo\update\diagnosis\derma.dat"
copy "E:\SVN\branches\template\*.ppt" "\\10.0.0.2\www\medicalphoto\repo\update\template\"

copy "\\10.0.0.2\www\medicalphoto\repo\release\beta\release.txt" "\\10.0.0.2\www\medicalphoto\repo\release\release.txt"
copy "\\10.0.0.2\www\medicalphoto\repo\release\beta\version.dat" "\\10.0.0.2\www\medicalphoto\repo\release\version.dat"
copy "\\10.0.0.2\www\medicalphoto\repo\release\beta\setup.exe" "\\10.0.0.2\www\medicalphoto\repo\release\setup.exe"
copy "\\10.0.0.2\www\medicalphoto\repo\release\beta\setup.exe" "\\10.0.0.2\www\medicalphoto\repo\release\old\setup.exe"

