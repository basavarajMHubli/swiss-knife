/**
 * @file demo.c
 * @brief Demo file to show usage of c-logger utility
 * @author Basavaraj M. Hubli
 * @version 2.0
 * @date 2020-03-30
 */

#include <stdio.h>
#include <unistd.h>
#include "clog.h"

int main()
{
    int val = 5;

    cLogInit("demo", CLOG_TYPE_FILE, CLOG_LEVEL_INFO);

    for (;;)
    {
        cLogInfo("info level log\n");
        cLogError("error level log\n");
        cLogDebug("debug level log\n");
        sleep(1);
    }

    cLogDeinit();
    return 0;
}
