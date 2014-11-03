#include "StdAfx.h"
#include "SSOLogin.h"
#include <Winsock2.h>

void SSOLogin::OpenURL( const CString &strURI )
{
	//获得默认浏览器文件的名称
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

	//做一个转换，因为注册表中写的浏览器全路径名带参数
	CString strFileName = szBrowzeName;

	//全部转换成小写	
	strFileName = strFileName.MakeLower();

	//查找.exe的位置
	int iIndex = strFileName.Find( _T(".exe") );
	if ( iIndex > 0 )
	{
		//真正的浏览器的全路径名
		strFileName = strFileName.Left( iIndex+4 );

		//判断左侧是否带引号
		if( strFileName.GetAt( 0 ) == '\"' )
		{
			strFileName = strFileName.Mid( 1 , strFileName.GetLength()-1 );
		}	
	}

	int iRet = (int)ShellExecute( NULL, _T("open"), strFileName , strURI,  NULL, SW_SHOWNORMAL);

	//默认浏览器打开失败，则打开IE
	if (iRet <= 32)
	{
		//获取系统目录
		(void)::GetSystemDirectory(szPathName, MAX_PATH);
		(void)_tsplitpath_s(szPathName, szdrive, szdir, szfname, szext);

		CString cstrIexplore = szdrive;
		cstrIexplore += _T("\\Program Files\\Internet Explorer\\IEXPLORE.EXE");
		(void)ShellExecute(NULL, _T("open"), cstrIexplore , strURI,  NULL, SW_SHOWNORMAL);
	}
}

