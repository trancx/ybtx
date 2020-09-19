// GacLauncher.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CScriptAppClient.h"
#include "ExpHelper.h"
#include "CScript.h"
#include "CPathMgr.h"
#include "RegistGacShell.h"
#include "TimeHelper.h"
#include "ErrLogHelper.h"
#include "Module.h"
#include "Memory.h"
#include "AntiDebug.h"
#include "CodeCvs.h"
#include "CAppConfigClient.h"
#include "CodeCvs.h"
#include "CGameClientProxyBank.h"
#include "ErrLogHelper.h"
#include "CLog.h"
#include "CPathMgr.h"
#include "stdio.h"

DEFINITION_OF_OPERATOR_NEW

// SQRENTRY int SqrMain(int argc, wchar_t* argv[])
//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 int main(int argc, wchar_t* argv[])
{
	SQR_TRY
	{	
		printf("asdasdasdahdhasdhashdahsdha\n\n\n\n\n\n");
		SetErrLogEnabled(true);
		wchar_t curPath[MAX_PATH];
		_wgetcwd(curPath, _countof(curPath));
		//设定log路径，以后所有的log，包括err log，简易log，内存泄露都会写入此路径下面
		printf("%ws\n\n\n\n\n\n", curPath);
		wstring log =  L"mylog.txt";
		SetLogPath(curPath);

		//在var game目录下面创建gas的err log
		SetErrLogFileName(log.c_str());
#ifndef _WIN32
		// 临时解决vs2005文件系统的一个bug
		wstring dummy_file = wstring(curPath) + L"/___file_fix___";
		vector<FILE*>	fileVec(512, 0);
		for ( int i = 0; i<512; ++i )
		{
			fileVec[i] = _wfopen(dummy_file.c_str(), L"wb");
		}
		for ( int j = 0; j<512; ++j )
		{
			if ( fileVec[j] != 0 )
				fclose(fileVec[j]);
		}
		DeleteFileW(dummy_file.c_str());
#endif
		InitGameClientProxyBank();

		{
			CScriptAppClient Runner("etc/gac/GacConfig.xml","etc/gac/GacSceneConfig.xml");

			CScript* pScript = NULL;


#ifndef _DEBUG
			ConfirmNoDebuger();
#endif

			pScript = Runner.GetMainVM();

			//为了支持命令行传参数，所以把第一个参数过滤掉。
			//通过命令行的会把命令本身也传递过来，而通过CreateProcess创建的进程就可以不传递第一个参数

			ostringstream strm;
			//int argc = 2;
			if(argc>1)
			{
				strm<<"g_strSelServerInfo=\""<< "124.71.184.116:52520"<<"\"\n";
			}

			strm<<"g_sSettingPath=\""<<Runner.GetCfgFilePath(NULL)<<"\"\n";

			string sResult;

			sResult=pScript->RunString(strm.str().c_str(),NULL);

			if(!sResult.empty())
			{
				MessageBox(NULL,sResult.c_str(),"error",MB_OK|MB_ICONERROR);
				return 0;
			}

			//注册游戏逻辑的c++代码到lua中

			RegistGacShell(*pScript);

			string gac_path = pScript->GetLoadPath("gac");
			string gac_main = gac_path + string("framework/main_frame/GacMain");
			printf("gac main = %s\n", gac_main.c_str());
			sResult=Runner.Run( gac_main.c_str() );

			SetErrLogEnabled(true);

			if(!sResult.empty())
			{
				MessageBox(NULL,sResult.c_str(),"error",MB_OK|MB_ICONERROR);
				return 0;
			}
		}
		UnitGameClientProxyBank();
	}
	SQR_CATCH(exp)
	{
		// 跑这儿来有作弊嫌疑啦~
		LogExp(exp);
	}
	SQR_TRY_END;
	return 0;
}


