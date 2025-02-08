#include "stdafx.h"
#include "helpapi.h"

bool FileIsExist(const SStringT &filepath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile(filepath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		return false;
	}
	else {
		FindClose(hFind);
		return true;
	}
}


SStringT GetFileExtname(const SStringT& filepath)
{
	TCHAR szExt[50] = { 0 };
	_tsplitpath(filepath, NULL, NULL, NULL, szExt);
	return szExt;
}

SStringT GetFilename(const SStringT& filepath)
{
	TCHAR szName[MAX_PATH] = { 0 };
	_tsplitpath(filepath, NULL, NULL, szName, NULL);
	return szName;
}

//自定义排序函数  
bool SortSString(const SStringT &v1, const SStringT &v2)
{
	return v1 < v2;		//升序排列  
}

bool SortSStringNoCase(const SStringT &v1, const SStringT &v2)
{
	return v1.CompareNoCase(v2) < 0;		//升序排列  
}