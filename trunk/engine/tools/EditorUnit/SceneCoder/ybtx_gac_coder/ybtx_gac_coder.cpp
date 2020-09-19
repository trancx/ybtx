#include "stdafx.h"
#include "ybtx_gac_coder.h"
#include "CEditTerrainMgr.h"
#include "CEditSkyMgr.h"
#include "CEditWaterMgr.h"
#include "CEditLogicDataMgr.h"
#include "CGraphic.h"
#include "CRenderGroup.h"
#include "BaseHelper.h"
#include "CQuadScene.h"
#include "CMetaGridMgr.h"

#include "CEditTerrainNode.h"
#include "CEditLogicData.h"
#include "CVertexDeclaration.h"
#include "CEditDataScene.h"

CYbtxGacCoder::CYbtxGacCoder( CDataScene* pScene )
: CSceneManagerClient(pScene->GetSceneName(), pScene->GetTreeScene(),NULL,0,0,0)
{
}

CYbtxGacCoder::~CYbtxGacCoder()
{
}



bool CYbtxGacCoder::SceneDeCode( CDataScene* pScene )
{
	CEditDataScene* pDataScene = (CEditDataScene*)pScene;
	m_pRenderGroup	= pDataScene->GetRenderGroup();
	m_pTerrainMgr	= pDataScene->GetTerrainMgr();
	m_pWaterMgr		= pDataScene->GetWaterMgr();
	m_pSkyMgr		= pDataScene->GetSkyMgr();
	m_pLogicDataMgr = pDataScene->GetLogicDataMgr();
	Initialize();
	Create();

	pDataScene->m_uWidthInRegion = m_uWidthInRegion;
	pDataScene->m_uHeightInRegion = m_uHeightInRegion;

	pDataScene->m_uWidth = pDataScene->m_uWidthInRegion / 4;
	pDataScene->m_uHeight = pDataScene->m_uHeightInRegion / 4;


	pDataScene->m_uWidthInGrid		= pDataScene->m_uWidthInRegion  * eRegionSpan;
	pDataScene->m_uHeightInGrid		= pDataScene->m_uHeightInRegion * eRegionSpan;

	pDataScene->m_uWidthInPixel		= m_uGridWidth * pDataScene->m_uWidthInGrid;
	pDataScene->m_uHeightInPixel	= m_uGridWidth * pDataScene->m_uHeightInGrid;


	pDataScene->m_RgnsList			= m_RgnsList;			//�������Ϣ�б�
	pDataScene->m_SubRegionsMap		= m_SubRegionsMap;	//һ�������������������������Ϣ�б�
	pDataScene->m_vecCamPath		= m_vecCamPath;			// ������켣����
	pDataScene->m_AmbientFxInfo		= m_AmbientFxInfo;		// ������Ч��Ϣ

	pDataScene->m_SceneInfo[EST_AFTERNOON] = m_SceneInfo[EST_AFTERNOON];	// ȫ�����������Ϣ

	return true;
}