#include "StdAfx.h"
#include "SSOLogin.h"
#include <Winsock2.h>

void SSOLogin::OpenURL( const CString &strURI )
{
	//���Ĭ��������ļ�������
	TCHAR szBrowzeName[256];
	TCHAR szPathName[MAX_PATH];
	TCHAR szdrive[_MAX_DRIVE];
	TCHAR szdir[_MAX_DIR];
	TCHAR szfname[_MAX_FNAME];
	TCHAR szext[_MAX_EXT];
	DWORD dwCount = 256;
	ZeroMemory(szBrowzeName, 256);

	HKEY hKey = NULL;
	long lReturn = RegOpenKeyEx( HKEY_CLASSES_ROOT, _T("\\HTTP\\shell\\open\\command"), 0 , KEY_ALL_ACCESS , &hKey);
	if (ERROR_SUCCESS == lReturn)
	{		
		(void)RegQueryValueEx(hKey , _T("") , 0 , &dwCount , (BYTE *)szBrowzeName , &dwCount) ;
		(void)RegCloseKey(hKey);	

		if ( szBrowzeName[0] == '\0' )
		{
			hKey = NULL;
			lReturn = RegOpenKeyEx( HKEY_CLASSES_ROOT, _T("\\https\\shell\\open\\command"), 0 , KEY_ALL_ACCESS , &hKey);

			if (ERROR_SUCCESS == lReturn)
			{		
				(void)RegQueryValueEx(hKey , _T("") , 0 , &dwCount , (BYTE *)szBrowzeName , &dwCount) ;
				(void)RegCloseKey(hKey);	
			}
		}
	}

	if ( szBrowzeName[0] == '\0' )
	{
		(void)::ShellExecute(NULL, _T("open"),  strURI, NULL, NULL, SW_MAXIMIZE);
		return;
	}

	//��һ��ת������Ϊע�����д�������ȫ·����������
	CString strFileName = szBrowzeName;

	//ȫ��ת����Сд	
	strFileName = strFileName.MakeLower();

	//����.exe��λ��
	int iIndex = strFileName.Find( _T(".exe") );
	if ( iIndex > 0 )
	{
		//�������������ȫ·����
		strFileName = strFileName.Left( iIndex+4 );

		//�ж�����Ƿ������
		if( strFileName.GetAt( 0 ) == '\"' )
		{
			strFileName = strFileName.Mid( 1 , strFileName.GetLength()-1 );
		}	
	}

	int iRet = (int)ShellExecute( NULL, _T("open"), strFileName , strURI,  NULL, SW_SHOWNORMAL);

	//Ĭ���������ʧ�ܣ����IE
	if (iRet <= 32)
	{
		//��ȡϵͳĿ¼
		(void)::GetSystemDirectory(szPathName, MAX_PATH);
		(void)_tsplitpath_s(szPathName, szdrive, szdir, szfname, szext);

		CString cstrIexplore = szdrive;
		cstrIexplore += _T("\\Program Files\\Internet Explorer\\IEXPLORE.EXE");
		(void)ShellExecute(NULL, _T("open"), cstrIexplore , strURI,  NULL, SW_SHOWNORMAL);
	}
}

