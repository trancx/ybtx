gac	game client			��Ϸ�ͻ����Լ����ͻ��˵��õĳ���
gmc	gm client			GM�ͻ���
gas	game server			��Ϸ������
rcp	reception server		�Ӵ�������
cis	central infomation server	������Ϣ������
tools	any other things		ά���Ϳ����õĹ���
common	�����õĴ���

���õĴ���������ר�ŵ��ļ����У���Ҫ�Ƿ�����������ȡ�ļ�
gac_gas
gac_rcp
gmc_gas



���ô����Ŀ¼���ֵ�����˳��
gac gmc gas cis rcp

����gac_gas����ȷ�ģ�����gas_gac�Ǵ���ģ���Ϊ����������������˳��






����
1��ȫ����Template��β�������ļ����ڱ��ض�Ҫ����һ�ݡ���ʾÿ̨���������ÿ��ܲ�һ��

truck\etc\commonĿ¼��
	DirectoryTemplate.xml ���ò߻��ĵ�·����data·��
	
truck\etc\gacĿ¼��
	GacConfig.xml  				 		 gac��������,��c++��ȡ
	GacTestConfigTemplate.lua  gac��lua ������������
	GacConfigTemplate.lua  		 gacĬ��������������
	
truck\etc\gasĿ¼��
	GasConfig.xml							 gas��������,��c++��ȡ
	GasConfigTemplate.lua      gas�����˿ڡ�mysql�˿ڣ�ip���á�����gbs��֤����
	GasTestConfigTemplate.lua  gas��lua ������������
	
truck\etc\rpcĿ¼��
	RcpConfig.xml							 rcp��������,��c++��ȡ
	
truck\etc\toolsĿ¼��
  TestSuiteTemplate.xml      engine test ������������
