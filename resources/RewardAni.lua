require("extern")
local HallUtils = require("HallUtils")
local Resources = require("Resources")
local CCButton = require("FFSelftools/CCButton")
local hallui = require("HallLayers/hallui")
local RewardAni  = class("RewardAni", function()
	return CCLayer:create()
end)

-- rewardType:奖励种类,0=金币，1=砖石，2=话费券，3=现金，4=物品，5=红包碎片
-- rewardNo:奖励数量
-- rewardTxt:奖励描述，只针对奖励种类为4的时候
-- rewardID:奖品对应的图片ID，用于替换图片
-- parentNode ： 父节点
-- showInDialog ： 是否是在
-- rewardScene : 1 = 抽奖界面获取  2 = 兑换界面获取
function RewardAni:init(rewardType,rewardNo,rewardTxt,rewardID,parentNode,rewardScene)
    local index = -1
    local aniIndex = {
        [0] = 0,
        [1] = 1,
        [2] = 0,
        [3] = 2,
        [4] = 0,
        [5] = 2
    }
    
    self.parentNode = parentNode
    if rewardType ~= nil and rewardType >= 0 and rewardType <= 5 then
        index = aniIndex[rewardType]
    end
    
    if index == -1 then
        cclog("playRewardAni:wrong rewardType " .. (rewardType ~= nil and rewardType or "nil"))
        return
    end
    
    CCArmatureDataManager:sharedArmatureDataManager():addArmatureFileInfo("resources/new/ani/gongxihuode/gongxihuode.ExportJson")
    self.m_rewardAni = CCArmature:create("gongxihuode")
    self.m_rewardAni:setPosition(ccp(640,360))
    self:addChild(self.m_rewardAni)

    local money = 0
    if(rewardNo >= 10000) then 
        money =""..(rewardNo/10000) .. "万"
    else
        money=""..rewardNo
    end
    
    local str;
    if(rewardType == 2) then 
       str = money --.. "话费"
    elseif(rewardType == 1) then
        str = money --.. "钻石"
    elseif(rewardType == 0) then
        str = money --.. "金币"
    elseif (rewardType == 3 or rewardType == 5) then
        str = money .. "元"
    elseif (rewardType == 4) then
        str = rewardTxt
    end

    -- 只适用于替换图片资源
    local function changeBoneDisplay(boneName,picName,useChangeFunc,index)
        if useChangeFunc then           
            self.m_rewardAni:getBone(boneName):changeDisplayWithName(string.format("gongxihuode/" .. picName),true)
        else
            if index ~= nil then
                -- 收货地址很奇怪，获取的骨骼坐标总是负数~~，先使用index获取，index依赖于ExportJson文件
                -- 所以如果改了json文件此处的索引可能也需要更改，以后更新了C++后使用 changeDisplayWithName 即可
                self.m_rewardAni:getBone(boneName):changeDisplayWithIndex(index,true)   
            else
                local path = string.format("resources/new/lottery/gongxihuode/" .. picName) -- 资源要拷贝到该目录下
                local pWPSprite = CCSprite:create(path)
                self.m_rewardAni:getBone(boneName):addDisplay(pWPSprite,0)
            end
        end
    end

    -- 显示中间文字描述
    local pLabel = CCLabelTTF:create(string.format("X %s",str), Resources.FONT_BLACK, 48)  
    pLabel:setColor(ccc3(0xee,0xd5,0x3d)) --  setFontFillColor
    self.m_rewardAni:getBone("zhong_shu"):addDisplay(pLabel, 0)  

    local useChangeFunc = false 
    if rewardType == 2 or rewardType == 4 then
        changeBoneDisplay("quduihuan",string.format("shouhuoxinxi.png"),useChangeFunc,2)
        changeBoneDisplay("wuping",string.format("exchange_item%d.png",rewardID),useChangeFunc)
        changeBoneDisplay("zhong_zi",string.format("zhong_zi3.png"),useChangeFunc)
    end

    local function closeEvent()
        if self.m_rewardAni ~= nil then
            self.m_rewardAni:removeFromParentAndCleanup(true)
            --self:removeFromParentAndCleanup(true)
            self.m_rewardAni = nil
        end

        if self.btList then
            local btCount = #self.btList
            for i = 1,btCount do
                if self.btList[i] ~= nil then
                    self.btList[i]:removeFromParentAndCleanup(true)
                    self.btList[i] = nil
                end
            end
        end
    end

    local function okButton(removefromparent)
        if removefromparent and self.parentNode ~= nil then 
            self.parentNode:removeFromParentAndCleanup(true)
            self.parentNode = nil
        end
        closeEvent()
    end

    local function lingquButton()
        local RewardDialogLayer = require("HallLayers/lottery/RedPacketHelpDialog")
        local layer = RewardDialogLayer.create()
        CCDirector:sharedDirector():getRunningScene():addChild(layer)

        okButton(false) -- 不关闭抽奖界面
    end

    local function addressButton()
        local layer = nil
        if rewardScene == 1 then -- 在转盘获得的，要跳转兑换界面
            if require("HallControl"):instance():isEnableFrag() == true then  --兑换类型:true为话费券兑换 false为金币兑换
                layer = require("HallLayers/exchangeex/ExchangeLayer").create(hallui.funcInfo.btexchange.res,true) --话费券兑换
            else
                layer = require("HallLayers/exchange/ExchangeLayer").create(hallui.funcInfo.btexchange.res,true) --金币兑换
            end
            CCDirector:sharedDirector():getRunningScene():addChild(layer)
            okButton(false)
        elseif rewardScene == 2 then -- 在兑奖处获取的，关闭动画并跳转到填写地址界面
            if self.parentNode then
                self.parentNode:showExchangeInputDialog(false)
            end
            okButton(false)
        end
    end

    -- 弹出兑换界面
    local function exchangeButton()
        cclog("####exchangeButton clicked####")
        local removefromparent = rewardScene == 1 and true or false       -- 是否关闭抽奖界面
        okButton(removefromparent)  
        local layer = nil
        if require("HallControl"):instance():isEnableFrag() == true then  --兑换类型:true为话费券兑换 false为金币兑换
            layer = require("HallLayers/exchangeex/ExchangeLayer").create(hallui.funcInfo.btexchange.res) --话费券兑换
        else
            layer = require("HallLayers/exchange/ExchangeLayer").create(hallui.funcInfo.btexchange.res) --金币兑换
        end
        CCDirector:sharedDirector():getRunningScene():addChild(layer)
    end

    -- 绑定按钮
    self.btList = {}
    local function bandBoneBtClick(boneName,newName,callBack,rmIndex)
        local picPath = "resources/new/lottery/gongxihuode/" .. newName
        local pBone = self.m_rewardAni:getBone(boneName)
        local pButton = CCButton.createCCButtonByStatusFilePath(picPath,picPath,picPath,callBack)
        local bonePosition = pBone:getPosition()
        local pNode = pBone:getDisplayRenderNode()
        local position = pNode:convertToWorldSpace(ccp(0,0))
        pButton:setAnchorPoint(0.5,0.5)
        pButton:setPosition(position.x + pButton:getContentSize().width/2,position.y + pButton:getContentSize().height/2)
        --[boneName] = pButton
        pushTable(self.btList,pButton)
        self:addChild(pButton)
    end

    -- 事件：0-开始 1-结束 2-循环结束
    local function animationMovementEvent(animation,  movementType, movementID)
        if (movementType ~= 1) then
            return
        end 
               
        bandBoneBtClick("queding","quding.png",closeEvent,0)  -- 绑定确定按钮事件
        if rewardType == 0  then -- 红包，点击按钮弹出兑换界面
            bandBoneBtClick("quduihuan","quduihuan.png",exchangeButton,1)
        elseif rewardType == 3 or rewardType == 5 then
            bandBoneBtClick("quduihuan","lingqu.png",lingquButton,1)
        elseif rewardType == 4 or rewardType == 2 then
            bandBoneBtClick("quduihuan","shouhuoxinxi.png",addressButton,2)
            local pBone = self.m_rewardAni:getBone("quduihuan")
        end
    end 

    self.m_rewardAni:getAnimation():setMovementEventCallFunc(animationMovementEvent)
    self.m_rewardAni:getAnimation():playWithIndex(index)
end

function RewardAni.create(rewardType,rewardNo,rewardTxt,rewardID,parentNode,rewardScene)
    local ani = RewardAni.new()
	ani:init(rewardType,rewardNo,rewardTxt,rewardID,parentNode,rewardScene)
	return ani
end

return RewardAni