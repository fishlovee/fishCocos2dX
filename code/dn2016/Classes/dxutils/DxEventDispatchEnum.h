#pragma once

#define DxEventDispatchEnumBegan	10000
#define DxEventDispatchUserBegan		100000

#define DxNoToString(no)	StringUtils::format("%d",(no))

// �����¼�������ڴ˴����ζ��壬�粻�ڴ˴����壬��Ӧ��ʹ�ñ� DxEventDispatchUserBegan ���ֵ�������ͻ
#define DxED_LOTTERY_TIMES_CHANGE	DxNoToString(DxEventDispatchEnumBegan + 1)								// ת�̳齱���������lotteryTurnTable::

