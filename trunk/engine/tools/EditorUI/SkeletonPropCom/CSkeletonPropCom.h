#pragma once
#include "CBaseComponent.h"
#include "SizeControl.h"
#include "SaveControl.h"

namespace sqr_tools
{
	public ref class ContrastEditor : public System::Drawing::Design::UITypeEditor
	{
	public:
		virtual System::Drawing::Design::UITypeEditorEditStyle GetEditStyle(System::ComponentModel::ITypeDescriptorContext^ context) override
		{
			return System::Drawing::Design::UITypeEditorEditStyle::DropDown;
		}
		virtual System::Object^ EditValue(System::ComponentModel::ITypeDescriptorContext^ context, System::IServiceProvider^ provider, System::Object^ value) override
		{
			System::Windows::Forms::Design::IWindowsFormsEditorService^ wfes = (System::Windows::Forms::Design::IWindowsFormsEditorService^)provider->GetService(System::Windows::Forms::Design::IWindowsFormsEditorService::typeid);
			if (wfes)
			{
				SizeControl^ sizeCtrl = gcnew SizeControl;
				sizeCtrl->m_iValue = (int)value;
				sizeCtrl->_wfes = wfes;
				wfes->DropDownControl(sizeCtrl);
				value = sizeCtrl->m_iValue;
			}
			return value;
		}
	};

	public ref class SaveEditor : public System::Drawing::Design::UITypeEditor
	{
	public:
		virtual System::Drawing::Design::UITypeEditorEditStyle GetEditStyle(System::ComponentModel::ITypeDescriptorContext^ context) override
		{
			return System::Drawing::Design::UITypeEditorEditStyle::DropDown;
		}
		virtual System::Object^ EditValue(System::ComponentModel::ITypeDescriptorContext^ context, System::IServiceProvider^ provider, System::Object^ value) override
		{
			System::Windows::Forms::Design::IWindowsFormsEditorService^ wfes = (System::Windows::Forms::Design::IWindowsFormsEditorService^)provider->GetService(System::Windows::Forms::Design::IWindowsFormsEditorService::typeid);
			if (wfes)
			{
				static int i = 0;
				i++;
				SaveControl^ saveCtrl = gcnew SaveControl;
				saveCtrl->_wfes = wfes;
				wfes->DropDownControl(saveCtrl);
				String^ temp = Convert::ToString(i);
				value = temp;
			}
			return value;
		}
	};

	public ref class CSkeletonPropCom : public CBaseComponent
	{
	public: 
		CSkeletonPropCom();
		~CSkeletonPropCom();

		virtual char* GetImpTypeName(void) override;
		virtual void  Update(void) override;

		[CategoryAttribute("����"), DescriptionAttribute("��ʾ����")]
		property bool ��ʾ���� 
		{
			virtual bool get();
			virtual void set(bool value);
		}

		[CategoryAttribute("����"), DescriptionAttribute("��ǰѡ�й���")]
		property System::String^ ��ǰѡ�й���
		{
			System::String^ get();
			void set(System::String^ value);
		}

		[CategoryAttribute("����"), DescriptionAttribute("����������С"), EditorAttribute(ContrastEditor::typeid,
			System::Drawing::Design::UITypeEditor::typeid)]
		property int ����������С
		{
			int get();
			void set(int value);
		}

		[CategoryAttribute("����"), DescriptionAttribute("��ǰ�����ļ�"), ReadOnlyAttribute(true)]
		property System::String^ ��ǰ�����ļ�
		{
			System::String^ get();
			void set(System::String^ value);
		}

		[CategoryAttribute("����"), DescriptionAttribute("��������ļ�"), EditorAttribute(SaveEditor::typeid,
			System::Drawing::Design::UITypeEditor::typeid)]
		property System::String^ ��������ļ�
		{
			System::String^ get();
			void set(System::String^ value);
		}

		[CategoryAttribute("�ؼ�������"), DescriptionAttribute("���ݼ�ӵ����")]
		property System::Windows::Forms::ContainerControl^ ControlParent 
		{
			virtual System::Windows::Forms::ContainerControl^ get();
			virtual void set(System::Windows::Forms::ContainerControl^ value);
		}

	protected: virtual System::Void _InitCtrl(void) override;
	protected: String^	m_strSkeletonName;
	protected: String^ m_strSeletedSkeletonName;
	protected: String^ m_strSkeletonFileInfo;
	protected: bool	m_bShowSkeleton;
	protected: int m_iSkeletonSize;
	protected: int m_iLastSkeletonSize;
	protected: System::Windows::Forms::ContainerControl^ m_pUserCtrl;
	};
}
