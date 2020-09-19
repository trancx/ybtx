#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
#include "CContextCom.h"
#include "CEditContext.h"

namespace sqr_tools
{
	class CCtrlBase;
	public ref  class CBaseComponent abstract : public System::ComponentModel::Component
	{
	public: 
		CBaseComponent(void);
		virtual ~CBaseComponent(void);
	
	protected:
		CCtrlBase*		m_pCtrl;
		CContextComponent^	m_pContextCom;

	public:
		[Category("�ؼ�������"),Description("ѡ��ؼ���Ӧ��Context"),TypeConverterAttribute(ReferenceConverter::typeid)]
		property CContextComponent^ ContextComponent
		{
			CContextComponent^ get();			//{ return m_pContextCom;		}
			void set(CContextComponent^ val);	//{ m_pContextCom = val;		}
		}

	public:
		void*				GetCoreCtrl(void);
		CContextComponent^	GetContextComponet(void);
		virtual void	Update(void);
		virtual char*	GetImpTypeName(void) = 0;
		virtual void*	GetImpParam(void);
	protected: 
		virtual System::Void _InitCtrl(void);
	};
}