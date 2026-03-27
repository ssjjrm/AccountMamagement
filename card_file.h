#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef CARD_FILE_H  // 防止头文件重复包含
#define CARD_FILE_H

typedef struct Card{ 
	char aName[18];    // 卡号
	char aPwd[8];     // 密码
	int nStatus;   // 卡状态(0-未上机；1-正在上机；2-已注销；3-失效)
	time_t tStart;     // 开卡时间
	time_t tEnd;      // 卡的截止时间
	float fTotalUse;   // 累计金额
	time_t tLast;       // 最后使用时间
	int nUseCount;      // 使用次数
	float fBalance;     // 余额
	int nDel;           // 删除标识0-未删除,1-删除
}Card;

void initStaticCardData();

//新增卡：返回0成功，-1数组已满，-2卡号重复
int insertCard(Card newCard);

//查找卡：传入卡号，返回找到的卡片指针（NULL为未找到/已删除）
Card* searchCard(char name[]);

#endif