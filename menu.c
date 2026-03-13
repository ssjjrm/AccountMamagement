
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "menu.h"
#include "card_file.h"
#include "billing_file.h"
#include "billing_service.h"
#include "card_service.h"
#include "record_file.h"
#include "record_service.h"
#include "service.h"


void  menuf() {
    initStaticCardData();
    while (1) {
        printf("系统菜单：“1. 添加卡、2. 查询卡、3. 上机、4. 下机、5. 充值、6. 退费、7. 查询统计、8. 注销卡、0. 退出”\n");
        int select = 0;
        scanf("%d", &select);
        if (select == 1) {
            insertCard_service();
        }
        else if (select == 2) {
            searchCard_service();
        }
        else if (select == 3) {

        }
        else if (select == 4) {

        }
        else if (select == 5) {

        }
        else if (select == 6) {

        }
        else if (select == 7) {

        }
        else if (select == 8) {

        }
        else if (select == 0) {
            return;
        }
    }
}