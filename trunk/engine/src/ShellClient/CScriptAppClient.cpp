#include "stdafx.h"
#include "CScript.h"
#include "CScriptAppClient.h"
#include "CAppClient.h"
#include "TBaseScriptApp.inl"
#include "ErrLogHelper.h"
#include <iostream>
#include "CAppConfigClient.h"
#include "TScriptAppGCTick.inl"
#include "PkgStream.h"
#include "CLangCfg.h"
#include "CFontCfg.h"
#include "CFileWatcherThread.h"
#include "CFileWatcherClientAdapter.h"
#include "CComputerInfo.h"
#include "CLogThreadMgr.h"

class CGCStepTickTraitsClient
{
public:
	typedef CAppClient						App_t;
	typedef CAppConfigClient				AppConfig_t;
};

typedef TScriptAppGCTick<CGCStepTickTraitsClient>		CGCStepTickClient;


template class TBaseScriptApp<CScriptAppClient>;
// gacconfig gacSceneConfig.xml
CScriptAppClient::CScriptAppClient( const char* szConfig, const char* szGfkConfig)
{
	//parent ��ȡĬ�ϵ�congfig���ǳ�ɵ�Ƶ�д������

	CLogThreadMgr::Init();

	ipkgstream strmGacConfig(L"", szConfig);
	if(!strmGacConfig)
		GenErr("Can't open Gac Config file.");
	new CComputerInfo();

//	ErrLogHeadMsg("OS",CComputerInfo::GetInst()->GetOSInfo().c_str());
//	ErrLogHeadMsg("HD",CComputerInfo::GetInst()->GetHDInfo().c_str());
	//ErrLogHeadMsg("CPU",CComputerInfo::GetInst()->GetCpuInfo().c_str());
	//win7 ����bug��ʱ����
	//ErrLogHeadMsg("VIDEO",CComputerInfo::GetInst()->GetAudioCardInfo().c_str());
//	ErrLogHeadMsg("DX",CComputerInfo::GetInst()->GetDirectInfo().c_str());
//	ErrLogHeadMsg("MEM",CComputerInfo::GetInst()->GetMemInfo().c_str());

	// �������ȫ����config���������Եȵȡ��� TRANCE
	new CAppConfigClient( strmGacConfig, szGfkConfig );

	//�������pkg file��鿪�أ�ͬʱ����pkg�ļ�����ô���ǿ���дlog
	// ���е�open ���ص� CPkgFileOpen ����ᴦ��pkg�ļ���
	if(CAppConfigClient::Inst()->PkgFileUsed())
	{
		SetErrLogEnabled(PkgFileUsed());
	}
	else
	{
		//���û�򿪿��أ���ôһֱ����дlog
		SetErrLogEnabled(true);
	}

	// ����Լ�gui����ͼƬ·������ӳ�䣬��guiͼƬ��Դ����ӳ��ɵ�ǰ���԰�����
	wstring szLangFolder = utf8_to_utf16(CLangCfg::GetInst()->GetLanFolder(0));
	wstring szOriLangFolder = utf8_to_utf16(CLangCfg::GetInst()->GetOriLanFolder());
	if ( m_bPkgFileUsed )
	{
		CPkgFile::AddMapPkgPreName(L"guitex", szLangFolder.c_str());
		CPkgFile::AddMapPkgPreName(L"guitex", szOriLangFolder.c_str());
	}

	wstring szGUITexPath = GetLangFilePath() + wstring(L"/") + szLangFolder;
	wstring szOriGUITexPath = GetLangFilePath() + wstring(L"/") + szOriLangFolder;
	CPkgFile::AddLoadPath(L"guitex", szGUITexPath.c_str());
	CPkgFile::AddLoadPath(L"guitex", szGUITexPath.c_str());
	CPkgFile::AddLoadPath(L"guitex", CPkgFile::GetLoadPath(L"res"));

	// �������������ļ�
	CFontCfg::GetInst()->LoadFongConfig(CLangCfg::GetInst()->GetLanFolder(0));
	
	// ���ݵ�ǰ�������ã��������ñ��ı�����·��
	
	wstring szCfgLan = szLangFolder + L"/table";
	AddScriptLoadPath("lan", utf16_to_utf8(szCfgLan).c_str());

	CreateMainVM();

	RegisterCoreScript();
	// �����ƺ��������Ⱦ֮��Ķ���
	CAppClient::Init();
}

CScriptAppClient::~CScriptAppClient(void)
{
	CAppClient::Unit();

	delete CComputerInfo::GetInst();
	delete CAppConfigClient::Inst();

	CLogThreadMgr::Unit();
}

string CScriptAppClient::Run( const char* szFileName )
{
	string sResult;

	SQR_TRY
	{
#ifdef _WIN32
		if (CAppConfigClient::Inst()->GetReload())
		{
			CFileWatcherThread::Init(new CFileWatcherClientAdapter(), GetCfgFilePath(""), GetLangFilePath(), GetRootFilePath("/game"));
		}
#endif
		//���õ���gc��ȫgc��tick
		CScript* pScript = GetScript();
		CGCStepTickClient* pGCTick = new CGCStepTickClient(pScript);

		stringstream strm;
		strm<<"engine_require(\"client/CoreClient\")\n"
			"CoreClient.Run(\""<<szFileName<<"\")";

		sResult=GetScript()->RunString(strm.str().c_str(),NULL);
		if (!sResult.empty())
		{
			LogErr(sResult.c_str());
		}

		GetScript()->GCAll();

		delete pGCTick;
#ifdef _WIN32
		if (CAppConfigClient::Inst()->GetReload())
		{
			CFileWatcherThread::Unit();
		}
#endif
	}
	SQR_CATCH(exp)
	{
		LogExp(exp);
	}
	SQR_TRY_END;

	return sResult;
}

void CScriptAppClient::RegisterCoreScript()
{
	CScript* pScript = GetMainVM();

	if( !RegisterModule(*pScript) )
		GenErr("RegisterModule failed");

	if( !RegisterCommon(*pScript) )
		GenErr("RegisterCommon failed");

	if( !RegisterThink(*pScript) )
		GenErr("RegisterThink failed");

	if( !RegisterGraphic(*pScript) )
		GenErr("RegisterGraphic failed");

	if( !RegisterGUI(*pScript) )
		GenErr("RegisterGUI failed");

	if( !RegisterNetwork(*pScript) )
		GenErr("RegisterNetwork failed");

	if( !RegisterScene(*pScript) )
		GenErr("RegisterScene failed");

	if( !RegisterCoreCommon(*pScript) )
		GenErr("RegisterCoreCommon failed");

	if( !RegisterCoreClient(*pScript) )
		GenErr("RegisterClient failed");

	if( !RegisterCoreScriptCommon(*pScript) )
		GenErr("RegisterCoreScriptCommon failed");
}
