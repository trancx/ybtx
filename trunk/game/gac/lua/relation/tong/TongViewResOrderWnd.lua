--gac_require "relation/tong/TongViewResOrderWndInc"
--
--------帮会资源收购浏览面板------
--
--function CreateTongViewResOrderWnd(Parent)
--	local Wnd = CTongViewResOrderWnd:new()
--	Wnd:Init(Parent)
--	return Wnd
--end
--
--function CTongViewResOrderWnd:Init(Parent)
--	self.m_TongBuyResOrderTbl = {}
--	self:CreateFromRes("TongViewResOrderWnd", Parent)
--	self:ShowWnd(false)
--	g_ExcludeWndMgr:InitExcludeWnd(self, 2, false, nil, 1)
--end
--
--function CTongViewResOrderWnd:OnChildCreated()
--	self.m_BuyResOrderList = self:GetDlgChild("TongList")
--	self.m_OkBtn = self:GetDlgChild("OkBtn")
--	self.m_CancelBtn = self:GetDlgChild("CancelBtn")
--	self.m_XBtn = self:GetDlgChild("XBtn")
--	self.m_PreBtn = self:GetDlgChild("PreBtn")
--	self.m_NextBtn = self:GetDlgChild("NextBtn")
--	self.m_CurPage = self:GetDlgChild("CurPageLbl")
--	self.m_TotalPage = self:GetDlgChild("TotalPageLbl")
--end
--
--function CTongViewResOrderWnd:OpenPanel()
--	Gac2Gas:GetTongMarketOrderInfoList(g_Conn)
--	self:ShowWnd(true)
--end
--
----消息
--function CTongViewResOrderWnd:OnCtrlmsg(Child, uMsgID, uParam1, uParam2)
--	if uMsgID == BUTTON_LCLICK then
--		if Child == self.m_CancelBtn or Child == self.m_XBtn then
--			self:ShowWnd(false)
--		elseif Child == self.m_OkBtn then
--			Gac2Gas:ShowMyResOrderWnd(g_Conn)
--			self:ShowWnd(false)
--		elseif Child == self.m_PreBtn then
--			local CurPage = tonumber(self.m_CurPage:GetWndText())
--			self:DrawTongBuyResOrderList(CurPage - 1)
--		elseif Child == self.m_NextBtn then
--			local CurPage = tonumber(self.m_CurPage:GetWndText())
--			self:DrawTongBuyResOrderList(CurPage + 1)
--		end
--	end
--end
--
--function CTongViewResOrderWnd:DrawTongBuyResOrderList(index)
--	self.m_BuyResOrderList:DeleteAllItem()
--	self.m_BuyResOrderList:InsertColumn(0, self.m_BuyResOrderList:GetWndOrgWidth())
--	local tbl = self.m_TongBuyResOrderTbl
--	
--	self.m_CurPage:SetWndText(index)
--	local totalPage
--	if #tbl % 10 == 0 then
--		totalPage = math.floor(#tbl / 10)
--	else
--		totalPage = math.floor(#tbl / 10) + 1
--	end
--	self.m_TotalPage:SetWndText(totalPage)
--	
--	if index == 1 or index == 0 then
--		self.m_PreBtn:EnableWnd(false)
--	else
--		self.m_PreBtn:EnableWnd(true)
--	end
--	
--	if index == totalPage then
--		self.m_NextBtn:EnableWnd(false)
--	else
--		self.m_NextBtn:EnableWnd(true)
--	end
--	
--	if index > 0 then
--		local startIndex = (index - 1) * 10 + 1
--		local endIndex
--		if index == totalPage then
--			endIndex = #tbl
----			if #tbl % 10 == 0 then
----				endIndex = index * 10
----			else
----				endIndex = (index - 1) * 10 + math.floor(#tbl % 10)
----			end
--		else
--			endIndex = index * 10
--		end
--		
--		local nCurI
--		for i = startIndex, endIndex do
--			if math.floor(i % 10) == 0 then
--				nCurI = 9
--			else
--				nCurI = math.floor(i % 10) - 1
--			end
--			self.m_BuyResOrderList:InsertItem(nCurI, 30)
--			local item = self.m_BuyResOrderList:GetSubItem(nCurI, 0)
--			local itemWnd = self:CreateListItemWnd(item)
--			itemWnd:SetInfo(tbl[i])
--		end
--	end
--end
--
--function CTongViewResOrderWnd:CreateListItemWnd(parent)
--	local wnd = CTongBuyResOrderListItem:new()
--	wnd:CreateFromRes("TongBuyResOrderListItem", parent)
--	wnd:ShowWnd(true)
--	return wnd
--end
--
--function CTongBuyResOrderListItem:OnChildCreated()
--	self.m_TongName = self:GetDlgChild("TongName")
--	self.m_Wz = self:GetDlgChild("Wz")
--	self.m_Wzs = self:GetDlgChild("Wzs")
--	self.m_Price = self:GetDlgChild("Price")
--	self.m_LeftNum = self:GetDlgChild("LeftNum")
--end
--
--function CTongBuyResOrderListItem:SetInfo(ListInfo)
--	self.m_TongName:SetWndText(ListInfo[1])
--	self.m_Wz:SetWndText(ListInfo[2])
--	self.m_Wzs:SetWndText(ListInfo[3])
--	self.m_Price:SetWndText(ListInfo[4])
--	self.m_LeftNum:SetWndText(ListInfo[5])
--end