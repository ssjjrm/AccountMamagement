#include "card_file.h"

struct Card cardList[100];
static int g_cardCount = 0;//记录当前有效卡片数量

//初始化测试卡数据
void initStaticCardData()
{
    // static变量控制仅执行1次初始化
    static int isInited = 0;
    if (isInited) return;

    // 初始化3张测试卡数据
    // 第1张测试卡
    strcpy(cardList[0].aName, "6222020001");
    strcpy(cardList[0].aPwd, "123456");
    cardList[0].nStatus = 0;
    cardList[0].tStart = time(NULL);  // 开卡时间为当前时间
    cardList[0].tEnd = 0;
    cardList[0].fTotalUse = 0.0f;
    cardList[0].tLast = time(NULL);
    cardList[0].nUseCount = 0;
    cardList[0].fBalance = 100.0f;
    cardList[0].nDel = 0;

    // 第2张测试卡
    strcpy(cardList[1].aName, "6222020002");
    strcpy(cardList[1].aPwd, "654321");
    cardList[1].nStatus = 0;
    cardList[1].tStart = time(NULL);
    cardList[1].tEnd = 0;
    cardList[1].fTotalUse = 0.0f;
    cardList[1].tLast = time(NULL);
    cardList[1].nUseCount = 0;
    cardList[1].fBalance = 200.0f;
    cardList[1].nDel = 0;

    // 第3张测试卡
    strcpy(cardList[2].aName, "6222020003");
    strcpy(cardList[2].aPwd, "000000");
    cardList[2].nStatus = 0;
    cardList[2].tStart = time(NULL);
    cardList[2].tEnd = 0;
    cardList[2].fTotalUse = 0.0f;
    cardList[2].tLast = time(NULL);
    cardList[2].nUseCount = 0;
    cardList[2].fBalance = 500.0f;
    cardList[2].nDel = 0;

    // 更新有效卡片数量
    g_cardCount = 3;
    isInited = 1; // 标记已初始化，后续不再执行
}

//新增卡
int insertCard(Card newCard){
    if (g_cardCount >= 100)
    {
        printf("卡数组已满\n");
        return -1;
    }

    //校验卡号是否重复（排除已删除的卡）
    for (int i = 0; i < g_cardCount; i++)
    {
        if (cardList[i].nDel == 0 && strcmp(cardList[i].aName, newCard.aName) == 0)
        {
            printf("卡号%s已存在\n", newCard.aName);
            return -2;
        }
    }

    //补充卡片默认值
    newCard.nStatus = 0;        // 默认未上机
    newCard.nDel = 0;           // 默认未删除
    newCard.tStart = time(NULL); // 开卡时间为当前时间
    newCard.tLast = time(NULL);  // 最后使用时间为当前时间
    newCard.nUseCount = 0;       // 默认使用次数0
    newCard.fTotalUse = 0.0f;    // 默认累计金额0

    cardList[g_cardCount] = newCard;
    g_cardCount++;

    printf("卡号%s新增成功！当前总卡数：%d\n", newCard.aName, g_cardCount);
    return 0;
}

//查找卡
Card* searchCard(char name[]){
    for (int i = 0; i < g_cardCount; i++){
        if (cardList[i].nDel == 0 && strcmp(cardList[i].aName, name) == 0){
            printf("【成功】找到卡号%s的卡片信息：\n", name);
            printf("  卡号：%s\n", cardList[i].aName);
            printf("  状态：%d（0-未上机 1-上机中 2-注销 3-失效）\n", cardList[i].nStatus);
            printf("  余额：%.2f 元\n", cardList[i].fBalance);
            printf("  使用次数：%d 次\n", cardList[i].nUseCount);
            printf("  开卡时间：%s", ctime(&cardList[i].tStart)); // ctime自动转换时间为字符串
            return &cardList[i]; // 返回找到的卡片指针
        }
    }

    // 未找到
    printf("【失败】未找到卡号%s的有效卡片！\n", name);
    return NULL;
}
