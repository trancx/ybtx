GasConfig =
{
	MysqlConnNum		= 2,					--mysql��������
	SkipGBSAuth 		= 1,                --�����Ƿ�Ҫ����GBS��¼��֤��1-������0-��������
	GBSAuthType		= 1,                --erating��½��֤��ʽ��0-������֤,1-���,2-yyר����
	EratingIBPaySend	= 1,							--erating������Ϣ���ͷ�ʽ��0--�����ͣ�1--�������erating[serverid == 1]��ע��tick��ʼ���ͣ�3--ֻ�����ѵ�ʱ��ע��tick���ͣ�
	EratingIBPaySendNum = 20,				--erating����ÿ����෢�Ͷ�����
	EratingExchangeSendNum = 10,		--erating��Ǯ��ͨÿ����෢�Ͷ�����
	SkipAdultCheck = 1,		--�Ƿ�������������֤(1--������֤��2--������)
	IgnoreRcp       = 1,
	GMValidate		= 0,		--�Ƿ����gmָ��Ȩ����֤��0����Ҫ��֤��1��Ҫ��֤
	StopServerCountDown = 0,			--�ط�����ʱ
	TestDropRate       = 0,       --�����Ƿ���Ե�����ʣ�1-���ԣ�0-�����ԣ�
	OpenCfgSwitch		= 1,					--�����Ƿ������ñ��⣨1-������0-�رգ�
	PreloadAllScene       = 0,       --���ó������뷽ʽ��0-������:�״ν��볡��ʱ���룬1-��Ӫ��:Ԥ�����г�����
	DBCoroutine		= 1,	--����Ctrl+C���˳������ǽ���GDB���е��ԣ�1-�˳��� 0-���ԣ�
	ApexProxyAddress	= "127.0.0.1",		--�����ϵͳ
	ApexProxyPort 		= 15306,
	GameWebServerIp		= "0.0.0.0",		--web serverģ������IP
	GameWebServerPort	= 10077,		--web serverģ�������˿�
	LogoutTime				= 300000,	--������ҵǳ�5����֮���ٵ�¼��Ϸ������¼�Ŷӡ�
	CISCheck			= false,
	EServiceCheck = true,
	SceneObjLimit		= true,			--�Ƿ����������������Ŀ����
	MaxDBResultSize 	= 3369600,		--db result���������С���������ֵ��¼log
	SortTime = 7200000,  --ÿ����Сʱˢһ�����а�
	StatisticDBTrans = 0,       --�Ƿ񿪷��Ϳ�ʼͳ��transation���õ�ʱ��ʹ�����1-���ԣ�0-�����ԣ�
	StatisticDBCalls = 0,		--�Ƿ񿪷��Ϳ�ʼͳ��sql���ʱ��ʹ�����1-���ԣ�0-�����ԣ�
	RequireDbBoxFile = 0,	--�Ƿ񿪷���������DB�ļ���1-���أ�0-�����أ�
	
	MaxSynLoginNum = 20,
	MaxSynChangeNum = 40,
	AllCpuLimit = 800,	--����ĳ������cpuʹ���ʴ��� AllCpuLimit ʱ�� ��ɫ��������û����ϵ�����������,
	MaxThreadCpuLimit = 10000000, --������������ĳ���߳�cpuʹ���ʴ���MaxThreadCpuLimit ʱ��, ��ɫ��������ý����е�����������
	
	RecruitTime = 720,  --�ؽ���ļ�Զ�����ʱ��(����)
	AccountTransWatchTime = 5,	--�ʺ�ִ��DbTrans�ļ��ʱ��
	AccountTransCount = 100,	--�ʺŵ�λʱ��������ִ��DbTrans����
	
	GasType = 0,  --����������,  0 Ϊ����������,  1Ϊpvp����������,
	
	StressCheck = 0,--ѹ�⿪��,(0��ʾ����ͻ��˷�ѹ���rpc��Ϣ;1��ʾ����Ϣ)���ѹ���ʱ��,��Ϊ1����.
	BuChangCheck = 0,
}

CISConfig = {
	CISHost = "10.10.43.142",
	CISPort = "80",
	CISAddRole_url = "/cgi-bin/cis/AddNewRole.php",
	CISCheckName_url = "/cgi-bin/cis/CheckName.php",
	CISRoleRename_url = "/cgi-bin/cis/ChangeRoleName.php",
	CISDelRole_url = "/cgi-bin/cis/DelRole.php",
	CISAddUser_url = "/cgi-bin/cis/AddNewUser.php",
	CISReuseRole_url = "/cgi-bin/cis/ReuseRole.php",
}


EServiceConfig = {
	Host = "59.151.39.146",
	Port = "8080",
	InsertQuestion = "/eService/system/insertQuestionFromClient.do",
	QueryQuestionList = "/eService/system/listQueryGameQuestions.do",
}
