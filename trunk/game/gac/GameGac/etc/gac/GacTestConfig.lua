GacTestConfig =
{
	OneStepLoginAccount = "onestep",
	OneStepLoginName = "onestep",
	Need = 0 , --[[
			0, Ϊ��������
			1, ���Զ�����
			2, һ����½
		--]]
	TestSuites =
	{       
		InitGacTestNPCShop,
		InitGacTestEmail,
		InitGacPlayerBag,
		InitGacTestStone,
		InitGacTestLogin,
		InitGacTestCDG,
		InitGacTestSelectCharState,
		InitGacTestAllLoginState,
		InitGacTestCreateRole,
		InitGacBagSpace, 
		InitGacTestMessage,
		InitGacPlayerMoney,
		--[[
		InitGacTestDynEquip,
		InitGacTestSkillTalentPannel,
		InitGacPlayerSkillPannel,
		--]]
	}
}
