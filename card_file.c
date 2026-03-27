#include "card_file.h"



//struct Card cardList[100];



// CardNode 结构体（你原代码，不动）
struct CardNode {
    Card data;
    struct CardNode* next;
};

// 链表头指针（初始为空）
static struct CardNode* cardListHead = NULL;
static int g_cardCount = 0;//记录当前有效卡片数量

int addCardNode(Card newCard) {
    // 1. 分配新节点
    struct CardNode* newNode = (struct CardNode*)malloc(sizeof(struct CardNode));
    if (newNode == NULL) return -1;

    newNode->data = newCard;
    newNode->next = NULL;

    // 2. 尾插
    if (cardListHead == NULL) {
        cardListHead = newNode;
    }
    else {
        struct CardNode* current = cardListHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    g_cardCount++;
    return 0;
}

struct Card* searchCardNode(Card findCard) {
    // 空链表判断
    if (cardListHead == NULL) {
        return NULL;
    }

    struct CardNode* p = cardListHead;
    while (1) {
        // 字符串比较用strcmp
        if (strcmp(p->data.aName, findCard.aName) == 0) {
            return &p->data;
        }
        else {
            if (p->next != NULL) {
                p = p->next;
            }
            else {
                return NULL;
            }
        }
    }
}

int deleteCardNode(Card findCard) {
    // 空链表判断
    if (cardListHead == NULL) {
        return 0;
    }

    struct CardNode* p = cardListHead;
    struct CardNode* before = cardListHead;
    while (1) {
        // 字符串比较用strcmp
        if (strcmp(p->data.aName, findCard.aName) == 0) {
            g_cardCount--;
            if (p == cardListHead) {
                cardListHead = p->next;
            }
            else {
                before->next = p->next;
            }
            free(p); //释放节点内存，防止泄漏
            return 1;
        }
        else {
            if (p->next != NULL) {
                // 前驱指针正确移动逻辑
                before = p;
                p = p->next;
            }
            else {
                return 0;
            }
        }
    }
}




void initStaticCardData()
{
    // static变量控制仅执行1次初始化
    static int isInited = 0;
    if (isInited) return;

    Card card; // 临时卡片变量
    // 初始化3张测试卡数据 → 调用addCardNode尾插链表
    // 第1张测试卡
    strcpy(card.aName, "1");
    strcpy(card.aPwd, "123");
    card.nStatus = 0;
    card.tStart = time(NULL);
    card.tEnd = 0;
    card.fTotalUse = 0.0f;
    card.tLast = time(NULL);
    card.nUseCount = 0;
    card.fBalance = 100.0f;
    card.nDel = 0;
    addCardNode(card); // 链表尾插

    // 第2张测试卡
    strcpy(card.aName, "2");
    strcpy(card.aPwd, "123");
    card.nStatus = 0;
    card.tStart = time(NULL);
    card.tEnd = 0;
    card.fTotalUse = 0.0f;
    card.tLast = time(NULL);
    card.nUseCount = 0;
    card.fBalance = 200.0f;
    card.nDel = 0;
    addCardNode(card); // 链表尾插

    // 第3张测试卡
    strcpy(card.aName, "3");
    strcpy(card.aPwd, "123");
    card.nStatus = 0;
    card.tStart = time(NULL);
    card.tEnd = 0;
    card.fTotalUse = 0.0f;
    card.tLast = time(NULL);
    card.nUseCount = 0;
    card.fBalance = 500.0f;
    card.nDel = 0;
    addCardNode(card); // 链表尾插

    isInited = 1; // 标记已初始化
}

//新增卡
int insertCard(Card newCard) {
    if (g_cardCount >= 100)
    {
        printf("卡链表已满\n");
        return -1;
    }

    // 封装查询参数
    Card findCard;
    strcpy(findCard.aName, newCard.aName);
    // 调用链表查询函数校验卡号是否重复
    Card* pExist = searchCardNode(findCard);
    if (pExist != NULL && pExist->nDel == 0)
    {
        printf("卡号%s已存在\n", newCard.aName);
        return -2;
    }

    newCard.nStatus = 0;
    newCard.nDel = 0;
    newCard.tStart = time(NULL);
    newCard.tLast = time(NULL);
    newCard.nUseCount = 0;
    newCard.fTotalUse = 0.0f;

    // 调用链表尾插函数添加
    addCardNode(newCard);

    printf("卡号%s新增成功！当前总卡数：%d\n", newCard.aName, g_cardCount);
    return 0;
}

//查找卡
Card* searchCard(char name[]) {
    // 封装查询参数
    Card findCard;
    strcpy(findCard.aName, name);
    Card* pCard = searchCardNode(findCard);

    if (pCard != NULL && pCard->nDel == 0)
    {
        printf("【成功】找到卡号%s的卡片信息：\n", name);
        printf("  卡号：%s\n", pCard->aName);
        printf("  状态：%d（0-未上机 1-上机中 2-注销 3-失效）\n", pCard->nStatus);
        printf("  余额：%.2f 元\n", pCard->fBalance);
        printf("  使用次数：%d 次\n", pCard->nUseCount);
        printf("  开卡时间：%s", ctime(&pCard->tStart));
        return pCard;
    }

    // 未找到
    printf("【失败】未找到卡号%s的有效卡片！\n", name);
    return NULL;
}