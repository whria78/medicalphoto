copy "E:\SVN\branches\version.rc2" "E:\SVN\branches\whriaview\res\whriaview.rc2"
copy "E:\SVN\branches\version.rc2" "E:\SVN\branches\MedicalPhotoServer\res\MedicalPhotoServer.rc2"
copy "E:\SVN\branches\version.rc2" "E:\SVN\branches\Configure\res\Configure.rc2"
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /build Release newconsole.sln
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /build Release WhriaView.sln
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /build Release Configure.sln
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /build Release MedicalPhotoServer.sln
rem "D:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /build Release .\unreg\unreg.sln
rem "D:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv" /build Release .\XYNTServiceProject\XYNTService.sln
