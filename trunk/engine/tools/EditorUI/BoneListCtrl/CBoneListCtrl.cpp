#include "StdAfx.h"
#include "CBoneListCtrl.h"
#include "BoneListCtrl/CBoneListCtrlImp.h"
#include "dthelp.h"

#define BoneListCtrlImp ((CBoneListCtrlImp*)GetCoreCtrl())

char* sqr_tools::CBoneListCtrl::GetImpTypeName( void )
{
	return GET_IMP_NAME(CBoneListCtrlImp);
}

void* sqr_tools::CBoneListCtrl::GetImpParam( void )
{
	return this->Handle.ToPointer();
}

void sqr_tools::CBoneListCtrl::Update( void )
{
	if (BoneListCtrlImp)
	{
		this->BoneListTreeView->Nodes->Clear();
		String^ rootSke = gcnew String(BoneListCtrlImp->GetRootSkeletalName().c_str());
		if (rootSke->Length)
		{
			TreeNode^ rootNode = gcnew TreeNode(rootSke);
			InsertNode(rootNode, rootSke);
			this->BoneListTreeView->Nodes->Add(rootNode);
		}
	}
}

void sqr_tools::CBoneListCtrl::InsertNode( TreeNode^ parent, String^ name )
{
	if (BoneListCtrlImp)
	{
		std::string strCPlus = MagStringToUnmagString(name);
		int num = BoneListCtrlImp->GetChildSkeletalNum(strCPlus);
		for (int i = 0; i < num; i++)
		{
			String^ childName = gcnew String(BoneListCtrlImp->GetChildSkeletalNameByIndex(strCPlus, i).c_str());
			TreeNode^ childNode = gcnew TreeNode(childName);
			if (!childName->Contains("Bone") || !this->���˻������ToolStripMenuItem->Checked)
			{
				parent->Nodes->Add(childNode);
				InsertNode(childNode, childName);
			}
		}
	}
}

System::Void sqr_tools::CBoneListCtrl::TravelNodes( TreeNode^ node )
{
	if (node)
	{
		std::string strCPlus = MagStringToUnmagString(node->Text);
		BoneListCtrlImp->AddNode(strCPlus);

		for (int i = 0; i < node->Nodes->Count; i++)
			TravelNodes(node->Nodes[i]);
	}
}

System::Void sqr_tools::CBoneListCtrl::���˻������ToolStripMenuItem_Click( System::Object^ sender, System::EventArgs^ e )
{
	this->���˻������ToolStripMenuItem->Checked = !this->���˻������ToolStripMenuItem->Checked;
	Update();
}

System::Void sqr_tools::CBoneListCtrl::��ӽڵ�ToolStripMenuItem_Click( System::Object^ sender, System::EventArgs^ e )
{
	if (BoneListCtrlImp)
	{
		if (this->BoneListTreeView->SelectedNode == nullptr)
			return;

		std::string strCPlus = MagStringToUnmagString(this->BoneListTreeView->SelectedNode->Text);
		BoneListCtrlImp->Reset();
		BoneListCtrlImp->AddNode(strCPlus);
		BoneListCtrlImp->SendMsg();
	}
}

std::vector<std::string> str_vector;
System::Void sqr_tools::CBoneListCtrl::��ӵ�ǰ�ڵ�ToolStripMenuItem_Click( System::Object^ sender, System::EventArgs^ e )
{
	if (BoneListCtrlImp)
	{
		if (this->BoneListTreeView->SelectedNode == nullptr)
			return;

		BoneListCtrlImp->Reset();
		TravelNodes(this->BoneListTreeView->SelectedNode);
		BoneListCtrlImp->SendMsg();
	}
}

System::Void sqr_tools::CBoneListCtrl::BoneListTreeView_MouseDown( System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e )
{
	if( e->Button == System::Windows::Forms::MouseButtons::Right )
	{
		TreeNode^ node = this->BoneListTreeView->GetNodeAt( e->X, e->Y );
		if (node)
		{
			this->BoneListTreeView->SelectedNode = node;
		}
	}
}