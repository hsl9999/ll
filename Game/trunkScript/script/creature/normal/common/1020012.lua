--怪物喊话脚本

-- 怪物进入战斗喊话
function c1020012_OnEnterCombat(MapID, InstanceID, CreatureID)
       local temp = math.random(1,100)
	if temp>=1 and temp<=25 then
		--15%几率喊话
             cre.MonsterSay(MapID, InstanceID, CreatureID, 20072)
       end
	unit.AddBuff(MapID, InstanceID,CreatureID,5055901,CreatureID)
end

aux.RegisterCreatureEvent(1020012, 2, "c1020012_OnEnterCombat")

