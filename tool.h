#pragma once
#ifndef TOOL_H
#define TOOL_H

#include <time.h>

time_t stringToTime(char* pTime);
void timeToString(time_t t, char* buf);

#endif
