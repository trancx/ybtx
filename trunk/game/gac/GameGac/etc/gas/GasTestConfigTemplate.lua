GasTestConfig =
{
	Need 		 			= 0,	--�Ƿ����gas����,1 ��ʾ���в��������� 0 ��ʾ��������������
	QuitWhenDone	= 0,	--������������Ƿ������˳�
	ConnCount 		= 0,	--��Ҫ����client�����Ӳ����в��������� 0 ��ʾֱ������
	
	TestSuites=
	{
		InitGasGenEquipAttribTest,
		InitGasReloadTest,
		InitGasEventTest,
		InitGasAccountMgrTest,
		InitGasContextMgrTest,
		InitGasPropMgrTest,
		InitGasLogMgrTest,
		InitGasTextFilterMgrTest,
		InitGasSceneControl
	}
}