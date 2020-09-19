#include "stdafx.h"
#include "CBaseDiff.h"
#include "PatchCommonDef.h"
#include "PatchFileProcess.h"
#include <Windows.h>
#include <io.h>




#define  Min(x, y)  ( x > y ? y : x )

extern std::wstring Utf8ToUCS2( const string& src );

static void XorBuffer(uint8* dst, uint8* src, int len)
{
	uint8* srcPtr = src;
	uint8* dstPtr = dst;
	for (int i=0; i<len; ++i)
	{
		*dstPtr = *srcPtr ^ *dstPtr;
		++srcPtr;
		++dstPtr;
	}
}


CBaseDiff::CBaseDiff()
{
}

CBaseDiff::~CBaseDiff()
{
}

bool CBaseDiff::ExecuteModify(FileHead* pPatchHead)
{
	wstring sPath = Utf8ToUCS2(pPatchHead->pPath);
	FILE* fp = _wfopen(sPath.c_str(), L"rb+");
	if ( ! fp )
	{	
		//������rb+�����Դ򲻿���������������ǿ�Ƹ����ļ�����
		DWORD attr = GetFileAttributes(sPath.c_str());
		if (attr & FILE_ATTRIBUTE_READONLY)
		{
			SetFileAttributes(sPath.c_str(), FILE_ATTRIBUTE_NORMAL);
			fp = _wfopen(sPath.c_str(), L"rb+");
			if(!fp)
				return false;
		}
		else
		{
			return false;
		}
	}
	uint32 uSourceSize = GetFileLength(fp);

	uint8* pData = pPatchHead->pData;
	ModifyNode sModifyNode = {0};
	uint32 uCount = 0;
	while ( uCount < pPatchHead->uDiffSize )
	{
		memcpy(&sModifyNode, pData, sizeof(ModifyNode));
		fseek(fp, sModifyNode.uSkip, SEEK_CUR);
		pData += sizeof(ModifyNode);
		fwrite(pData, sizeof(uint8), sModifyNode.uSize, fp);
		pData += sModifyNode.uSize;

		uCount += sizeof(ModifyNode) + sModifyNode.uSize;
	}

	// �����º��Դ�ļ��س���Ŀ���ļ�ͬ��С������Դ�ļ���Ŀ���ļ��޵Ķ�������
	_chsize(_fileno(fp), pPatchHead->uFileSize);

	fclose(fp);

	return true;
}

