@echo off

echo ���������� ���� HWUCSDK DLL��������������������������
xcopy /Y /S .\..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C50SPC100B091\debug\dll\* 	.\output\debug\
xcopy /Y /S .\..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C50SPC100B091\release\dll\* .\output\release\
echo ���������� ���� HWUCSDK DLL �ɹ�������������������������

echo ���������� ���� UCService��������Դ�ļ� ��������������������������
xcopy /Y /S .\UCResource\* 	.\output\debug\
xcopy /Y /S .\UCResource\*  	.\output\release\
echo ���������� ���� UCService��������Դ�ļ� �ɹ�������������������������

pause