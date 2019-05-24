#pragma once

#include <cocos2d.h>
#include "dxutils.h"
#include "testcode/testdefs.h"
#include <cocos-ext.h>


USING_NS_CC;
USING_NS_CC_EXT;

class LotteryTurnTable:public DxLayer
{
public:
	enum EN_LOTTERY_STATUS
	{
		eLotteryNorm = 0, 
		eLotteryStart,
		eLotterySlow,
		eLotteryFast,
		eLotteryStop
	};

	~LotteryTurnTable();
	void runCase();
	bool init();


	void onEnter();
	void onExit();

	void update(float delta);
	//static LotteryTurnTable * create();
	CREATE_FUNC(LotteryTurnTable);
	CREATE_TEST_FUNC(LotteryTurnTable);
private:
	bool isRunning() { return _isRunning; }
	bool addBg();
	bool addDescribe();
	bool addLotteryList();
	bool addTurntable();
	bool addCloseButton();
	void runLotteryActions(float delta);
	void changeStartButtonStat();
	void blinkAction();
private:
	LotteryTurnTable();
	Sprite *_turntableBg;
	LabelTTF *_lotteryTimeTTF;
	TableView *_lotteryListView;
	ui::Button *_startButton;
	Sprite *_arrow;
	Sprite *_blink;
	unsigned int _lotterytime;
	unsigned int _lotteryInning;
	float _ftotalDegree;
	float _startDegree;
	bool _isRunning;
	EN_LOTTERY_STATUS _lotteryStatus;
};

class DxLotteryWinList : public DxLayer, public TableViewDataSource, public TableViewDelegate
{
public:

	static DxLotteryWinList * create(Size tableSize, Vector<Node *> cellElements, Size cellSize);

	virtual void scrollViewDidScroll(extension::ScrollView* view)override {};
	virtual void scrollViewDidZoom(extension::ScrollView* view)override {}
	virtual void tableCellTouched(extension::TableView* table, extension::TableViewCell* cell)override;
	virtual Size tableCellSizeForIndex(extension::TableView *table, ssize_t idx)override;
	virtual extension::TableViewCell* tableCellAtIndex(extension::TableView *table, ssize_t idx)override;
	virtual ssize_t numberOfCellsInTableView(extension::TableView *table)override;
	virtual void tableCellHighlight(extension::TableView* table, extension::TableViewCell* cell) override;
	virtual void tableCellUnhighlight(extension::TableView* table, extension::TableViewCell* cell) override;

public:
	void setCellSelectedBg(int bgTag, Sprite *selectedBg, Sprite *normBg/* = nullptr*/);
	void setLabelTag(int tag);
	void setCellSize(Size cellSize) { _cellSize = cellSize; }
	void appendNode(Node *node,bool forceReload = false);	// 在外部已经构造好的cell
	void reSetData(Vector<Node *> cellElements);
	void refesh();
private:
	DxLotteryWinList();
	bool init(Size tableSize);
	Vector<Node *> _cellElements;
	Size _cellSize;
	Sprite *_selectedCellBg;
	Sprite *_normCellBg;
	int _bgTag;
	int _labeltag;
	extension::TableView *_tableView;
};