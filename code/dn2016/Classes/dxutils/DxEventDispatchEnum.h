#pragma once

#define DxEventDispatchEnumBegan	10000
#define DxEventDispatchUserBegan		100000

#define DxNoToString(no)	StringUtils::format("%d",(no))

// 所有事件最好能在此处依次定义，如不在此处定义，则应该使用比 DxEventDispatchUserBegan 大的值，避免冲突
#define DxED_LOTTERY_TIMES_CHANGE	DxNoToString(DxEventDispatchEnumBegan + 1)								// 转盘抽奖次数变更，lotteryTurnTable::

