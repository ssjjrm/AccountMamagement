#include <stdio.h>
#include <time.h>

// 字符串转时间 (年-月-日 时:分 → time_t)
time_t stringToTime(char* pTime) {
    struct tm tm_time;
    sscanf(pTime, "%d-%d-%d %d:%d",
        &tm_time.tm_year, &tm_time.tm_mon, &tm_time.tm_mday,
        &tm_time.tm_hour, &tm_time.tm_min);
    tm_time.tm_year -= 1900;
    tm_time.tm_mon -= 1;
    tm_time.tm_sec = 0;
    return mktime(&tm_time);
}

// 时间转字符串 (time_t → 年-月-日 时:分)
void timeToString(time_t t, char* buf) {
    struct tm* tm_time = localtime(&t);
    sprintf(buf, "%04d-%02d-%02d %02d:%02d",
        tm_time->tm_year + 1900, tm_time->tm_mon + 1, tm_time->tm_mday,
        tm_time->tm_hour, tm_time->tm_min);
}