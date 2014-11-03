@echo off

echo －－－－－ 拷贝 HWUCSDK DLL－－－－－－－－－－－－－
xcopy /Y /S .\..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C50SPC100B091\debug\dll\* 	.\output\debug\
xcopy /Y /S .\..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C50SPC100B091\release\dll\* .\output\release\
echo －－－－－ 拷贝 HWUCSDK DLL 成功－－－－－－－－－－－－

echo －－－－－ 拷贝 UCService依赖的资源文件 －－－－－－－－－－－－－
xcopy /Y /S .\UCResource\* 	.\output\debug\
xcopy /Y /S .\UCResource\*  	.\output\release\
echo －－－－－ 拷贝 UCService依赖的资源文件 成功－－－－－－－－－－－－

pause