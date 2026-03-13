#include "card_service.h"

void insertCard_service()
{
    Card newCard = { 0 };

    printf("===== 新增卡片 =====\n");
    printf("请输入卡号（最长17位）：");
    scanf("%17s", newCard.aName); // 限制长度，防止数组越界

    printf("请输入密码（最长7位）：");
    scanf("%7s", newCard.aPwd);

    printf("请输入初始余额：");
    scanf("%f", &newCard.fBalance);

    insertCard(newCard);
}

void searchCard_service()
{
    char searchName[18] = { 0 };

    printf("===== 查找卡片 =====\n");
    printf("请输入要查询的卡号：");
    scanf("%17s", searchName);

    searchCard(searchName);
}
