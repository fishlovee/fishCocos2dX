#include "lotteryTurnTable.h"
#include "dxutils.h"

#define  Text_lottery_times  "您还有 %d 次抽奖机会"
#define  Text_lottery_next_times  "下次免费抽奖 %s"
#define  Text_lottery_loginFree_times  "每日登录即可获得%d次免费抽奖机会"
#define  Text_lottery_winnName  "获奖名单"
#define  Text_diamondNotEnough  "亲，钻石太少了，需要去获取点钻石吗？"
#define  Text_lottery_Error  "抽奖出错!"
#define  Text_lottery_Award  "抽奖奖励"
#define  Text_lottery_tips  "再进行%d场游戏可以获得下一次抽奖"

#define Lottery_WinBg_Tag	123456
#define Lottery_WinLabel_Tag	1234567


LotteryTurnTable::LotteryTurnTable()
{
	_turntableBg = nullptr;
	_lotteryTimeTTF = nullptr;
	_lotteryListView = nullptr;
	_startButton = nullptr;
	_lotterytime = 0;
	_lotteryInning = 0;
	_isRunning = false;
	_lotteryStatus = eLotteryNorm;
	_arrow = nullptr;
	_blink = nullptr;
}

LotteryTurnTable::~LotteryTurnTable()
{
}

void LotteryTurnTable::runCase()
{

}

bool LotteryTurnTable::init()
{
	DX_SAFE_RETURN_BEGAN
	{
		DX_BREAK_IF_FALSE(DxLayer::init());
		DX_BREAK_IF_FALSE(this->addBg());
		DX_BREAK_IF_FALSE(this->addCloseButton());
		DX_BREAK_IF_FALSE(this->addDescribe());
		DX_BREAK_IF_FALSE(this->addLotteryList());
		DX_BREAK_IF_FALSE(this->addTurntable());

		return true;
	} DX_SAFE_RETURN_END;

	CC_SAFE_DELETE(_turntableBg);
	CC_SAFE_DELETE(_lotteryTimeTTF);
	CC_SAFE_DELETE(_lotteryListView);
	CC_SAFE_DELETE(_startButton);
	return false;
}

bool LotteryTurnTable::addBg()
{
	CC_SAFE_DELETE(_turntableBg);
	DX_SAFE_RETURN_BEGAN 
	{
		auto size = Director::getInstance()->getVisibleSize();
		auto org = Director::getInstance()->getVisibleOrigin();
		_turntableBg = Sprite::create("lotteryTurnTable/turnTable_bg.png");
		DX_BREAK_IF_NULLPTR(_turntableBg);
		_turntableBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_turntableBg->setPosition(Vec2(size.width / 2 + org.x, org.y + size.height / 2));
		this->addChild(_turntableBg);

	}DX_SAFE_RETURN_END


	CC_SAFE_DELETE(_turntableBg);
	return false;
}

bool LotteryTurnTable::addDescribe()
{
	CC_SAFE_DELETE(_lotteryTimeTTF);
	DX_SAFE_RETURN_BEGAN
	{
		// 描述背景框 
		auto chanceBg = Sprite::create("lotteryTurnTable/lotteryChanceBg.png");
		DX_BREAK_IF_NULLPTR(chanceBg);
		chanceBg->setAnchorPoint(Vec2::ZERO);
		chanceBg->setPosition(Vec2(60, _turntableBg->getContentSize().height*0.42));
		_turntableBg->addChild(chanceBg);

		// 描述文字一：
		auto  changeTips = LabelTTF::create(toUtf8String(DX_ZN_CODE, StringUtils::format(Text_lottery_tips, _lotteryInning)), DX_FONT_ARIAL, 20);
		DX_BREAK_IF_NULLPTR(changeTips);
		changeTips->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		changeTips->setPosition(ccp(chanceBg->getContentSize().width / 2, chanceBg->getContentSize().height*0.55));
		changeTips->setColor(ccc3(255, 255, 0));
		chanceBg->addChild(changeTips);

		// 描述文字二：
		_lotteryTimeTTF = LabelTTF::create(toUtf8String(DX_ZN_CODE,StringUtils::format(Text_lottery_times,_lotterytime)),DX_FONT_BLACK,26);
		DX_BREAK_IF_NULLPTR(_lotteryTimeTTF);
		_lotteryTimeTTF->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		_lotteryTimeTTF->setPosition(ccp(chanceBg->getContentSize().width / 2, chanceBg->getContentSize().height*0.35));
		_lotteryTimeTTF->setColor(ccc3(255, 255, 0));
		chanceBg->addChild(_lotteryTimeTTF);
	}DX_SAFE_RETURN_END;

	CC_SAFE_DELETE(_lotteryTimeTTF);
	return false;
}

bool LotteryTurnTable::addLotteryList()
{
	CC_SAFE_DELETE(_lotteryListView);

	DX_SAFE_RETURN_BEGAN
	{
		auto winBg = Sprite::create("lotteryTurnTable/winNameBg.png");
		DX_BREAK_IF_NULLPTR(winBg);
		winBg->setAnchorPoint(Vec2::ZERO);
		winBg->setPosition(Vec2(60, _turntableBg->getContentSize().height*0.08));
		_turntableBg->addChild(winBg);

		auto winTitle = LabelTTF::create(toUtf8String(DX_ZN_CODE, Text_lottery_winnName), DX_FONT_BLACK, 26);
		DX_BREAK_IF_NULLPTR(winTitle);
		winTitle->setColor(ccc3(255, 255, 0));
		winTitle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		winTitle->setPosition(Vec2(winBg->getContentSize().width/2,winBg->getContentSize().height*0.8));
		winBg->addChild(winTitle);

		//void setCellSelectedBg(int bgTag, Sprite *selectedBg, Sprite *normBg = nullptr);
		//void setCellSize(Size cellSize) { _cellSize = cellSize; }
		//void appendCell(Node *node);	// 在外部已经构造好的cell


		Vector<Node *> elMENTS;
		for (int nIndex = 0;nIndex < 20;++nIndex)
		{
			Sprite *BgSprite = Sprite::create("lotteryTurnTable/wincell.png");
			BgSprite->setTag(1);
			auto name = toUtf8String(DX_ZN_CODE,StringUtils::format("第%d名：", nIndex + 1));
			auto nameTTF = LabelTTF::create(name, DX_FONT_ARIAL, 24);
			nameTTF->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
			nameTTF->setPosition(Vec2(0,BgSprite->getContentSize().height/2));
			nameTTF->setTag(Lottery_WinLabel_Tag);
			BgSprite->addChild(nameTTF);

			//exchange_item20
			auto elemet = Sprite::create(StringUtils::format("lotteryTurnTable/exchange_item%d.png", nIndex + 1));
			elemet->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
			elemet->setPosition(Vec2(BgSprite->getContentSize().width, BgSprite->getContentSize().height / 2));
			BgSprite->addChild(elemet);

			elMENTS.pushBack(BgSprite);
		}

		Sprite *winElementBg = Sprite::create("lotteryTurnTable/wincell.png");
		Size tableSize = Size(winBg->getContentSize().width, winBg->getContentSize().height - 50);
		auto winList = DxLotteryWinList::create(tableSize,elMENTS, winElementBg->getContentSize());
		winList->setCellSize(winElementBg->getContentSize());
		winList->setAnchorPoint(Vec2::ZERO);
		winList->setPosition(Vec2::ZERO);
		winBg->addChild(winList);
		winList->setLabelTag(Lottery_WinLabel_Tag);
		winList->refesh();

		//_lotteryListView = TableView::create();
		//DX_BREAK_IF_NULLPTR(_lotteryListView);

	}DX_SAFE_RETURN_END;

	CC_SAFE_DELETE(_lotteryListView);
	return false;
}

bool LotteryTurnTable::addTurntable()
{
	// 12个奖品，每个30°
	// 中间一个按钮，含”开始“文字，一个指针，点击按钮后”开始“文字隐藏，禁止点击按钮，指针开始转圈
	// 指针转圈：由快到慢随即转动，最后根据指针最后的角度获取奖品的信息，指针转圈完成后使能抽奖按钮
	// 弹出中奖信息：
	//DX_PRINT("0.95 = %d,0.49 = %d,1.21 - 1 = %d,1.94 - 1 = %d", (int)0.95, (int)0.49, (int)(1.21 - 1), (int)(1.94 - 1));
	Sprite *turntable = nullptr;
	Sprite *startBg = nullptr;
	Sprite *startFore = nullptr;
	CC_SAFE_RELEASE_NULL(_arrow);
	DX_SAFE_RETURN_BEGAN
	{
		string strFolderName = "common";
		turntable = Sprite::create(StringUtils::format("lotteryTurnTable/common/turnTable.png"));
		DX_BREAK_IF_NULLPTR(turntable);
		turntable->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		turntable->setPosition(_turntableBg->getContentSize().width - 15, _turntableBg->getContentSize().height / 2 - 5);

		// 开始按钮 freeLottery_bg.png freeLottery_bg1.png
		auto centerPos = turntable->getContentSize() / 2;
		startBg = Sprite::create(StringUtils::format("lotteryTurnTable/common/freeLottery_bg.png"));
		DX_BREAK_IF_NULLPTR(turntable);
		startBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		startBg->setPosition(centerPos);
		turntable->addChild(startBg);

		startFore = Sprite::create(StringUtils::format("lotteryTurnTable/common/freeLottery_bg1.png"));
		DX_BREAK_IF_NULLPTR(turntable);
		startFore->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		startFore->setPosition(centerPos);
		turntable->addChild(startFore);

		_startButton = createButtonWithOneImg(StringUtils::format("lotteryTurnTable/common/freeLottery.png"), [&](Ref *) {
			auto curRotation = _arrow->getRotation();
			float delta = curRotation - (int)curRotation;
			float targetRotation = (int)curRotation % 360 + delta;
			DX_PRINT(toUtf8String(DX_ZN_CODE,StringUtils::format("开始抽奖...rotation = %f,targetRotation = %f", _arrow->getRotation(), targetRotation)).c_str());  // 抽奖
			_isRunning = true;
			changeStartButtonStat();
			_blink->stopAllActions();
			_blink->setVisible(false);
			_arrow->setRotation(targetRotation);
		});

		_startButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_startButton->setPosition(centerPos);
		turntable->addChild(_startButton);


		// 闪光动画
		_blink = Sprite::create("lotteryTurnTable/common/turnTale_light_1.png");
		_blink->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_blink->setPosition(centerPos);
		//blink->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.2f, 30),nullptr)));
		blinkAction();
		turntable->addChild(_blink);

		// 转盘指针 arrow.png
		_arrow = Sprite::create(StringUtils::format("lotteryTurnTable/common/arrow.png"));
		_arrow->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_arrow->setPosition(centerPos);
		turntable->addChild(_arrow);

		// 奖品
		std::srand(time(NULL));
		Vector<Sprite *> items;
		for (int index = 0;index < 12;++index)
		{
			int nNo = RandomHelper::random_int(1, 12);
			auto elmt = Sprite::create(StringUtils::format("lotteryTurnTable/exchange_item%d.png", nNo));
			DX_BREAK_IF_NULLPTR(elmt);
			items.pushBack(elmt);
		}

		
		// destroy
		if (items.size() != 12)
		{
			items.clear();
			break;
		}
		else
		{
			for (int n = 0; n < items.size(); ++n)
			{
				auto item = items.at(n);
				float turnTable_radius = turntable->getContentSize().width / 2 - item->getContentSize().width / 2 - 40;
				int nAngle = 30 * (n);
				float y = turnTable_radius * cos(nAngle*DEG_RAD);	// 度数要*pi/180
				float x = turnTable_radius * sin(nAngle*DEG_RAD);	// 
				DX_PRINT("item%d:x = %f,y = %f", n, centerPos.width + x, centerPos.height + y);
				DX_PRINT("--item%d:x = %f,y = %f", n,x, y);
				item->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				item->setPosition(Vec2(centerPos.width + x, centerPos.height + y));
				turntable->addChild(item);
			}
		}

		//CCTargetedAction

		//FadeTo
		_turntableBg->addChild(turntable);
	} DX_SAFE_RETURN_END;


	CC_SAFE_DELETE(turntable);
	CC_SAFE_DELETE(startBg);
	CC_SAFE_DELETE(_startButton);
	CC_SAFE_DELETE(_arrow);
	return false;
}

bool LotteryTurnTable::addCloseButton()
{
	ui::Button *closeButton = nullptr;
	DX_SAFE_RETURN_BEGAN
	{
		closeButton = DxUtils::createButtonWithOneImg("guanbi.png", [&](Ref *) {
			this->enableShowLayerZoom(true);
			this->RemoveLayer(0.75f);
		});
		CC_BREAK_IF(closeButton == nullptr);

		Vec2 buttonPos = Vec2(_turntableBg->getContentSize().width + closeButton->getContentSize().width,
			_turntableBg->getContentSize().height - closeButton->getContentSize().height*0.7);
		closeButton->setPosition(buttonPos);
		this->addChild(closeButton);
	}DX_SAFE_RETURN_END

	CC_SAFE_DELETE(closeButton);
	return false;
}

void LotteryTurnTable::runLotteryActions(float delta)
{
	float speed = 0;

	// 90°之后切换到fast，剩余180°的时候切换到slow，少于30°的时候切换到stop
	switch (_lotteryStatus)
	{
	case LotteryTurnTable::eLotteryNorm:
	{
		_lotteryStatus = eLotteryStart;
		_startDegree = _arrow->getRotation();
		speed = 0.3;
		_ftotalDegree = 30*(RandomHelper::random_int(3, 5) * 12 + RandomHelper::random_int(1, 12)) + _startDegree; // 随机要转的格子数
		//_ftotalDegree = 24*30 + +_startDegree;// 每个格子30°
		DX_PRINT("current degree = %f,target degree:%f", _startDegree, _ftotalDegree);
		break;
	}
	case LotteryTurnTable::eLotteryStart:
	{
		speed = 0.3;
		if (_arrow->getRotation() - _startDegree >= 90 )
		{
			_lotteryStatus = eLotteryFast;
		}
		break;
	}
	case LotteryTurnTable::eLotteryFast:
	{
		if (_ftotalDegree - _arrow->getRotation() < 180)
		{
			_lotteryStatus = eLotterySlow;
		}
		speed = 1.5; 
		break;
	}
	case LotteryTurnTable::eLotterySlow:
	{
		speed = 0.75;
		float delta = _ftotalDegree - _arrow->getRotation();
		if (_ftotalDegree - _arrow->getRotation() < 60)
		{
			// 在0.2s内移动到目标degree
			auto rotate = RotateBy::create(0.2f, delta);
			//auto rotate = RotateTo::create(0.2f, _ftotalDegree);	// rotateto有个问题，第二次抽奖的时候总是多转一圈，但是rotateby就没问题！！！如果在每次转动前将角度转换为0~360°则使用totateto又正常了。
			_lotteryStatus = eLotteryStop;
			//auto rotatefinishCallback = CallFunc::create([&]() {
			//	_lotteryStatus = eLotteryStop;
			//});
			DX_PRINT("++++current degree = %f,target degree:%f", _arrow->getRotation(), _ftotalDegree);
			//_arrow->stopAllActions();
			auto finishcallback = CallFunc::create([&]() {
				_blink->setVisible(true);
				blinkAction();
			});
			_arrow->runAction(Sequence::createWithTwoActions(rotate, finishcallback));
		}
		DX_PRINT("current degree = %f,target degree:%f,delta = %f,", _arrow->getRotation(), _ftotalDegree,delta);
		break;
	}
	case LotteryTurnTable::eLotteryStop:
	{
		speed = 0;
		_isRunning = false;
		_lotteryStatus = eLotteryNorm;
		changeStartButtonStat();
		break;
	}
	default:
		break;
	}


	if (_lotteryStatus != eLotteryStop)
	{
		_arrow->setRotation(_arrow->getRotation() + 360 * speed*delta);
	}
}

void LotteryTurnTable::changeStartButtonStat()
{
	if (_startButton == nullptr)
	{
		return;
	}

	_startButton->setVisible(!_isRunning);
}

void LotteryTurnTable::blinkAction()
{
	if (_blink == nullptr || !_blink->isVisible())
	{
		return;
	}

	_blink->runAction(RepeatForever::create(Sequence::createWithTwoActions(RotateBy::create(0.05f, 30), DelayTime::create(0.1))));
}

void LotteryTurnTable::onEnter()
{
	DxLayer::onEnter();
	scheduleUpdate();

	// 注册事件

	// 中奖列表变更事件

	// 抽奖次数

	// 抽奖
}

void LotteryTurnTable::onExit()
{
	DxLayer::onExit();

	// 注销事件
}

void LotteryTurnTable::update(float delta)
{
	if (!isRunning())
	{
		return;
	}

	runLotteryActions(delta);
}

//LotteryTurnTable * LotteryTurnTable::create()
//{
//	auto turntable = new LotteryTurnTable();
//	if (turntable  && turntable->init())
//	{
//		turntable->autorelease();
//	}
//	else
//	{
//		CC_SAFE_DELETE(turntable);
//	}
//	return turntable;
//}

DxLotteryWinList * DxLotteryWinList::create(Size tableSize, Vector<Node *> cellElements, Size cellSize)
{
	auto dxtb = new DxLotteryWinList();
	if (dxtb != nullptr && dxtb->init(tableSize))
	{
		dxtb->autorelease();
		dxtb->setContentSize(tableSize);
		dxtb->reSetData(cellElements);
		dxtb->setCellSize(cellSize);
		return dxtb;
	}

	CC_SAFE_DELETE(dxtb);
	return dxtb;
}

void DxLotteryWinList::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}

Size DxLotteryWinList::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return _cellSize;
}

TableViewCell* DxLotteryWinList::tableCellAtIndex(TableView *table, ssize_t idx)
{
	if (idx >= _cellElements.size()) return nullptr;

	TableViewCell *cell = table->dequeueCell();
	if (cell == nullptr)
	{
		cell = TableViewCell::create();
		auto node = _cellElements.at(idx);
		node->setAnchorPoint(Vec2::ZERO);
		node->setPosition(Vec2::ZERO);
		cell->addChild(node);
	}

	Node *node = (LabelTTF *)cell->getChildByTag(1);
	if (node)
	{
		LabelTTF *label = (LabelTTF *)node->getChildByTag(_labeltag);
		if (label)
		{
			label->setString(toUtf8String(DX_ZN_CODE, StringUtils::format("第%d名：", idx + 1)));
		}
	}

	return cell;
}

ssize_t DxLotteryWinList::numberOfCellsInTableView(TableView *table)
{
	return _cellElements.size();
}

void DxLotteryWinList::tableCellHighlight(TableView* table, TableViewCell* cell)
{
	if (_selectedCellBg == nullptr) return;
	Sprite * bg = (Sprite *)cell->getActionByTag(_bgTag);
	if (bg == nullptr) return;
	bg->setTexture(_selectedCellBg->getTexture());
}

void DxLotteryWinList::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
	if (_normCellBg == nullptr) return;
	Sprite * bg = (Sprite *)cell->getActionByTag(_bgTag);
	if (bg == nullptr) return;
	bg->setTexture(_normCellBg->getTexture());
}

void DxLotteryWinList::setCellSelectedBg(int bgTag, Sprite *selectedBg, Sprite *normBg /*= nullptr*/)
{
	if (selectedBg != nullptr)
	{
		CC_SAFE_RETAIN(selectedBg);
		CC_SAFE_RELEASE(_selectedCellBg);
		_selectedCellBg = selectedBg;
	}

	if (normBg != nullptr)
	{
		CC_SAFE_RETAIN(normBg);
		CC_SAFE_RELEASE(_normCellBg);
		_normCellBg = selectedBg;
	}

	_bgTag = bgTag;
}

void DxLotteryWinList::setLabelTag(int tag)
{
	_labeltag = tag;
}

void DxLotteryWinList::appendNode(Node *node, bool forceReload)
{
	_cellElements.pushBack(node);
	if (forceReload)
	{
		refesh();
	}
}

void DxLotteryWinList::reSetData(Vector<Node *> cellElements)
{
	for each (auto elmt in _cellElements)
	{
		CC_SAFE_RELEASE(elmt);
	}
	_cellElements.clear();

	for each (auto elmt in cellElements)
	{
		CC_SAFE_RETAIN(elmt);
		_cellElements.pushBack(elmt);
	}

	_tableView->reloadData();
}

void DxLotteryWinList::refesh()
{
	if (_tableView != nullptr) _tableView->reloadData();
}

DxLotteryWinList::DxLotteryWinList()
{
	_selectedCellBg = nullptr;
	_normCellBg = nullptr;
	_bgTag = 0;
	_tableView = nullptr;
}

bool DxLotteryWinList::init(Size tableSize)
{
	DX_SAFE_RETURN_BEGAN
	{
		DX_BREAK_IF_FALSE(DxLayer::init());

		_tableView = TableView::create(this, tableSize);
		DX_BREAK_IF_NULLPTR(_tableView);

		//tableView->setDirection(ScrollView::Direction::HORIZONTAL);
		_tableView->setAnchorPoint(Vec2::ZERO);
		_tableView->setPosition(Vec2::ZERO);
		_tableView->setDelegate(this);
		_tableView->setDirection(ScrollView::Direction::VERTICAL);
		_tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		this->addChild(_tableView);
		_tableView->reloadData();


	}DX_SAFE_RETURN_END;

	return false;
}