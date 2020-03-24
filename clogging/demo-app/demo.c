/**
 * @file demo.c
 * @brief Demo file to show usage of c-logger utility
 * @author Basavaraj M. Hubli
 * @version 1.0
 * @date 2020-03-24
 */

#include <stdio.h>
#include <unistd.h>
#include "clog.h"

int main()
{
    int val = 5;

    cLogInit("demo", CLOG_TYPE_CONSOLE, CLOG_LEVEL_INFO);

    for (;;)
    {
        cLogInfo("info level log");
        cLogError("error level log");
        cLogDebug("debug level log");
        sleep(1);
        putchar('\n');
    }

    cLogDeinit();
    return 0;
}
