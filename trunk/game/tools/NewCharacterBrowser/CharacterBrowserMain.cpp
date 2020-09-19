// NewCharacterBrowser.cpp : main project file.

#include "stdafx.h"
#include "CharacterBrowserForm.h"
#include "CharacterBrowserBriage.h"
#include "IApplication.h"
#include "ICtrlImpFactory.h"
using namespace CharacterBrowser;

//[STAThreadAttribute]
//int WINAPI WinMain(HINSTANCE hinst,HINSTANCE hpre, LPSTR lpCmd, int nShowCmd)
int main(void)
{
	wchar_t curPath[MAX_PATH];
	_wgetcwd(curPath, _countof(curPath));
	//�趨log·�����Ժ����е�log������err log������log���ڴ�й¶����д���·������
	printf("%ws\n\n\n\n\n\n", curPath);
	//_wchdir(L"../../..");
	printf("asdasdasads\n");
	IApplication::InitApp();

 	//////////////////////////////////////////////////////////////////////////
 	if( !CharacterBrowserBriage::HasInst() )
 		CharacterBrowserBriage::Create();
	
	CharacterBrowserBriage::GetInst()->InitEnviroment();
	//////////////////////////////////////////////////////////////////////////

	CUIBase::Initialize(IApplication::GetInst()->GetCtrlImpFactory());
	CharacterBrowserForm^ mainForm = gcnew CharacterBrowserForm();
	mainForm->Show();
	IApplication::GetInst()->Run();

 	if( CharacterBrowserBriage::HasInst() )
 		CharacterBrowserBriage::Destroy();

	return 0;
}
