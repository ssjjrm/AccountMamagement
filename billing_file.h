#include <time.h>

#ifndef BILLING_FILE_H  // 防止头文件重复包含
#define BILLING_FILE_H

typedef struct Billing {
	char aCardName[18];    // 卡号
	time_t tStart;         // 上机时间
	time_t tEnd;           // 下机时间
	float fAmount;         // 消费金额
	int nStatus;           // 消费状态，0-未结算，1-已经结算
	int nDel;              // 删除标识，0-未删除,1-删除
}Billing;



#endif
