#include "stdafx.h"
#include "CAppClient.h"
#include "CConnClient.h"
#include "CApexClient.h"
#include "PtrlGac2GasCPPDcl.h"
#include "PtrlGac2GasCPPDef.h"
#include "CAppThreadEvent.h"

//
//pfRec �� Apex Client �ṩ�����ݴ�����;��,GameClient �յ�GameServer��������Apex �����ݵ�ʱ��
//		�����������ָ�봦��;���:  int		NoticeApec_UserData(const char * pBuf,int nBufLen);
//
_FUNC_C_REC			pfRec					= NULL;

static uint32	m_uApexNetTime = 0;

//֪ͨApexClient,��GameSever������Ϣ
//����
//pBuffer	: �������ݵĻ�����
//nLen		: �������ݵĳ���

class CApexNetEvent : public CAppThreadEvent
{
public:
	CApexNetEvent(uint32 uTime, const char* pBuffer, int nLen);
	~CApexNetEvent();

private:
	uint32			m_uTime;
	char*			m_pBuffer;
	int				m_nLen;
};

CApexNetEvent::CApexNetEvent(uint32 uTime, const char* pBuffer, int nLen)
: m_uTime(uTime)
, m_nLen(nLen)
{
	m_pBuffer = new char[nLen];
	memcpy(m_pBuffer, pBuffer, nLen);
}

CApexNetEvent::~CApexNetEvent()
{
	CGac2GasCPP_ApexProxyMsg cmd;	
	cmd.uLen = (uint16)m_nLen;
	CConnClient* pConn = CConnClient::Inst();
	if (!pConn)
	{
		delete [] m_pBuffer;
		return;
	}
	
	if(m_uTime != m_uApexNetTime)
	{
		delete [] m_pBuffer;
		return;
	}

	CConnClient::Inst()->SendCmd(&cmd);
	CConnClient::Inst()->Send(m_pBuffer,m_nLen);
	delete [] m_pBuffer;
}

long NetSendToGameServer(const char * pBuffer,int nLen)
{
	CAppClient::Inst()->PostThreadAppEvent(new CApexNetEvent(m_uApexNetTime, pBuffer, nLen));
	return 0;
}

//
//����		:	����ApexClient;
//
int	StartApexClient()
{
	// m_uApexNetTime++;

	//����ApexClient;	NetSendToGameServer ��ApexClient��GameServer����Ϣ����
	//					pfRec				��Apex �ṩ�Ľ��ܺ���;
	// long    re= CHCStart(NetSendToGameServer,pfRec);
	return 0;
}

//
//ֹͣApexClient
//
int	StopApexClient()
{
	//ֹͣ ApecClient
	// CHCEnd();
	return 0;
}

//
//֪ͨApexClient,�����ݴ� GameServer ������
//			
//
//����
//pBuf			: �������ݵĻ�����
//nBufLen		: �������ݵĳ���
int	NoticeApec_UserData(const char * pBuf,int nBufLen)
{
	if(pfRec)
	{
		pfRec(pBuf,nBufLen);
	}
	return 0;
}



