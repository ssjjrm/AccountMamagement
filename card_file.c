#include "card_file.h"

#define FILE_PATH "data/card.txt"  //文件路径

//struct Card cardList[100];


// CardNode 结构体
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


void freeCardList() {
    struct CardNode* p = cardListHead;
    while (p) {
        struct CardNode* temp = p;
        p = p->next;
        free(temp);
    }
    cardListHead = NULL;
    g_cardCount = 0;
}


void initStaticCardData()
{
    // static变量控制仅执行1次初始化
    static int isInited = 0;
    if (isInited) return;

    readCardInFile(FILE_PATH);
    g_cardCount = getCardCountInFile(FILE_PATH);

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

    saveCardToFile(&newCard, "data/card.txt");

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


//删除卡
void deleteCard(char name[]) {
    // 封装查询参数
    Card findCard;
    strcpy(findCard.aName, name);

    if (deleteCardNode(findCard)) {
        printf("删除成功\n");
    }
    else {
        printf("删除失败\n");
    }

}


// 1. 保存卡到文件（追加到末尾）
int saveCardToFile(const Card* pCard, const char* pPath) {
    if (pCard == NULL || pPath == NULL) return 0;

    // 追加模式打开文件
    FILE* fp = fopen(pPath, "a");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return 0;
    }

    // 时间转字符串
    char startBuf[30] = { 0 }, lastBuf[30] = { 0 }, endBuf[30] = { 0 };
    timeToString(pCard->tStart, startBuf);
    timeToString(pCard->tLast, lastBuf);
    timeToString(pCard->tEnd, endBuf);

    // 按 ## 格式写入文件
    fprintf(fp, "%s##%s##%d##%s##%s##%.2f##%s##%d##%.2f##%d\n",
        pCard->aName,
        pCard->aPwd,
        pCard->nStatus,
        startBuf,
        endBuf,
        pCard->fTotalUse,
        lastBuf,
        pCard->nUseCount,
        pCard->fBalance,
        pCard->nDel);

    fclose(fp);
    return 1;
}

// 2. 获取文件中卡数量
int getCardCountInFile(const char* pPath) {
    FILE* fp = fopen(pPath, "r");
    if (fp == NULL) return 0;

    int count = 0;
    char buf[1024];
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        if (strlen(buf) > 1) count++;
    }

    fclose(fp);
    return count;
}

// 3. 解析字符串为Card结构体
Card parseCard(char* pBuf) {
    Card card;
    // 按 ## 分割字符串
    char* token = strtok(pBuf, "##");

    strcpy(card.aName, token);
    token = strtok(NULL, "##");
    strcpy(card.aPwd, token);
    token = strtok(NULL, "##");
    card.nStatus = atoi(token);
    token = strtok(NULL, "##");
    card.tStart = stringToTime(token);
    token = strtok(NULL, "##");
    card.tEnd = stringToTime(token);
    token = strtok(NULL, "##");
    card.fTotalUse = atof(token);
    token = strtok(NULL, "##");
    card.tLast = stringToTime(token);
    token = strtok(NULL, "##");
    card.nUseCount = atoi(token);
    token = strtok(NULL, "##");
    card.fBalance = atof(token);
    token = strtok(NULL, "##");
    card.nDel = atoi(token);

    return card;
}

// 4. 从文件读取所有卡
int readCardInFile(const char* pPath) {
    if (pPath == NULL) return 0;

    FILE* fp = fopen(pPath, "r");
    if (fp == NULL) return 0;

    char buf[1024];
    int index = 0;

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        buf[strcspn(buf, "\n")] = 0; // 去掉换行
        if (strlen(buf) == 0) continue;
        addCardNode(parseCard(buf));
    }

    fclose(fp);
    return 1;
}
