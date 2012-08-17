--
--gac_gas_require "relation/cofc/CofcTechnologyMgr"
--local tech_mgr = CCofcTechnologyMgr:new()
--local StmtOperater = {}		--用来挂sql语句的table
--
--------------------------------------
----闭包开始
--local CCofcTechBox = CreateDbBox(...)
------------------------------------------SQL相关------------------------------------------------------
----根据商会id查询所有科技信息
--local StmtDef = 
--{
--	"_GetAllCofcTechInfo",
--	[[
--		select tc_nTechId,tc_uPoint,tc_uLevel from tbl_technology_cofc
--		where c_uId = ?
--	]]
--}
--DefineSql(StmtDef, StmtOperater)
--
----得到商会当前科研项目代号
--local StmtDef = 
--{
--	"_GetCofcCurrentTechID",
--	[[
--		select tc_nTechId  from tbl_cofc
--		where c_uId = ?
--	]]
--}
--DefineSql(StmtDef, StmtOperater)
--
----设置当前科研项目
--local StmtDef = 
--{
--	"_UpdateCofcCurrentTech",
--	[[
--		update tbl_cofc set tc_nTechId = ?
--		where c_uId = ?
--	]]
--}
--DefineSql(StmtDef, StmtOperater)
--
----查询某科技信息
--local StmtDef = 
--{
--	"_GetCofcTechByIndex",
--	[[
--		select tc_uPoint,tc_uLevel from tbl_technology_cofc
--		where c_uId = ? and tc_nTechId = ?
--	]]
--}
--DefineSql(StmtDef, StmtOperater)
--
----增加科技信息
--local StmtDef = 
--{
--	"_AddCofcTechInfo",
--	[[
--		insert into tbl_technology_cofc(c_uId,tc_nTechId,tc_uLevel,tc_uPoint) values(?,?,?,?)
--	]]
--}
--DefineSql(StmtDef, StmtOperater)
--
----增加科技等级
--local StmtDef = 
--{
--	"_AddCofcTechLevel",
--	[[
--		update  tbl_technology_cofc set tc_uLevel = tc_uLevel + 1,tc_uPoint = 0
--		where c_uId = ? and tc_nTechId = ?
--	]]
--}
--DefineSql(StmtDef, StmtOperater)
--
----增加科技点数
--local StmtDef = 
--{
--	"_AddCofcTechPoint",
--	[[
--		update  tbl_technology_cofc set tc_uPoint = tc_uPoint + ?
--		where c_uId = ? and tc_nTechId = ?
--	]]
--}
--DefineSql(StmtDef, StmtOperater)
-------------------------------------------------------------------------------------------------
----【得到商会所有科技信息】
--function CCofcTechBox.GetAllCofcTechInfo(cofc_id)
--  local query_result = StmtOperater._GetAllCofcTechInfo:ExecSql('nnn', cofc_id)
--  
--  local row = query_result:GetRowNum()
--	local res = {}
--	
--	for i = 1, row do
--		table.insert(res, query_result:GetRow(i-1))
--	end
--	
--	query_result:Release()
--	return res
--end
--
----得到商会当前科研项目代号
--function CCofcTechBox.GetCofcCurrentTechID(cofc_id)
--  local query_result = StmtOperater._GetCofcCurrentTechID:ExecSql('n', cofc_id)
--  if 0 == query_result:GetRowNum() then
--  	query_result:Release()
--  	return 0
--  end
--  local nTechID = query_result:GetNumber(0,0)
--	query_result:Release()
--	return nTechID
--end
--
----设置当前科研项目
--function CCofcTechBox.UpdateCofcCurrentTech(cofc_id,nIndex)
-- 	StmtOperater._UpdateCofcCurrentTech:ExecSql('',nIndex,cofc_id)
-- 	if not (g_DbChannelMgr:LastAffectedRowNum()>= 0)  then
--  	CancelTran()
--  	return false
--  end
--  return true
--end
--
----获得某科技的信息
--function CCofcTechBox.GetCofcTechByIndex(cofc_id,nIndex)
-- 	local query_result = StmtOperater._GetCofcTechByIndex:ExecSql('nn',cofc_id,nIndex)
-- 	if 0 == query_result:GetRowNum() then
-- 		return nil,nil
-- 	end
-- 	
-- 	local point,level = query_result:GetNumber(0,0),query_result:GetNumber(0,1)
-- 	
-- 	query_result:Release()
-- 	
-- 	return point,level
--end
--
---------------------------------------------------------------------------------------------------
----【获得某商会所有科技信息】
--function CCofcTechBox.GetCofcTechnologyInfoDB(parameters)
--
--	local uCofcID = parameters["uCofcID"]
--	
--	local info = CCofcTechBox.GetAllCofcTechInfo(uCofcID)
--	local curr_tech = CCofcTechBox.GetCofcCurrentTechID(uCofcID)
--	return info,curr_tech
--end
--
----【设置当前科研项目】
--function CCofcTechBox.UpdateCofcCurrentTechDB(parameters)
-- 	local uCofcID = parameters["uCofcID"]
--	local nIndex = parameters["nIndex"]
--	local uPlayerID = parameters["uPlayerID"]
--	local CofcBasicDB = RequireDbBox("CofcBasicDB")
--	if CofcBasicDB.GetPosition(uPlayerID) ~= "会长" then
--		return false
--	end
--	
--	local tech_info = tech_mgr:GetTechnologyInfo(nIndex)
--	if tech_info == nil then
--		--说明配置表没有该代号的科技
--		return false
--	end
--	
--	local current_tech = CCofcTechBox.GetCofcCurrentTechID(uCofcID)
--	if current_tech == nIndex then
--		--说明该科技已经是当前科研项目
--		return false
--	end
--	
--	local point,level = CCofcTechBox.GetCofcTechByIndex(uCofcID,nIndex)
--	local add_point = 100	--要增加的点数应该是做任务获得，这里先默认设置为50
--	if point == nil or level == nil then
--		--说明该科技没有被设置过
--		local default_level,default_point = 0,add_point
--		if add_point >= tech_info.NeedPoint then
--			default_level,default_point = 1,0
--		end
--		StmtOperater._AddCofcTechInfo:ExecSql('',uCofcID,nIndex,default_level,default_point)
--		if not (g_DbChannelMgr:LastAffectedRowNum() > 0)  then
--  		CancelTran()
--  		return false
--  	end
--  else
--  	--已经设置过该科技
--  	if (-1 ~= tech_info.UpperLevel) and (level >= tech_info.UpperLevel) then
--  		--已经达到最大等级的不能设置为当前科研项目
--  		return false
--  	end
--  	if add_point + point >= tech_info.NeedPoint then
--  		--点数之和大于升级所需点数，则升级
--  		StmtOperater._AddCofcTechLevel:ExecSql('',uCofcID,nIndex)
--  	else
--  		--点数之和小于所需点数，增加点数
--  		StmtOperater._AddCofcTechPoint:ExecSql('',add_point,uCofcID,nIndex)
--  	end
--  	if not (g_DbChannelMgr:LastAffectedRowNum() >= 0)  then
--  		CancelTran()
--  		return false
--  	end
--	end
--	--修改当前科研项目
--	local bFlag = CCofcTechBox.UpdateCofcCurrentTech(uCofcID,nIndex)
--	if not bFlag then
--		return false
--	end
--	local info,curr_tech = CCofcTechBox.GetAllCofcTechInfo(uCofcID),CCofcTechBox.GetCofcCurrentTechID(uCofcID)
--	return true,info,curr_tech
--end
--
--return CCofcTechBox
--
--
--
--
