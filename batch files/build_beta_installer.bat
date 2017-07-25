copy "E:\SVN\branches\version.rc2" "E:\SVN\branches\whriaview\res\whriaview.rc2"
copy "E:\SVN\branches\version.rc2" "E:\SVN\branches\MedicalPhotoServer\res\MedicalPhotoServer.rc2"
copy "E:\SVN\branches\version.rc2" "E:\SVN\branches\Configure\res\Configure.rc2"
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" /build Release newconsole.sln
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" /build Release WhriaView.sln
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" /build Release Configure.sln
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" /build Release MedicalPhotoServer.sln
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" /build Release .\unreg\unreg.sln
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" /build Release .\XYNTServiceProject\XYNTService.sln
"c:\Program Files\CreateInstall v4\ci" e:\svn\branches\medicalphoto.ci
copy "E:\SVN\branches\release.txt" "\\10.0.0.2\www\medicalphoto\repo\release\beta\release.txt"
copy "E:\SVN\branches\version.dat" "\\10.0.0.2\www\medicalphoto\repo\release\beta\version.dat"
\\10.0.0.2\repo\release\beta\setup.exe
