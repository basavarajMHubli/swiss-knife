/**
 * @file clog.c
 * @brief Controlled logging utility
 * @author Basavaraj M. Hubli
 * @version 1.0
 * @date 2020-03-24
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "clog.h"

#define CLOG_BUF_SIZE   1024

CLogCfg_t   *cLogCfg;
char        *cLogBuf;

extern void cLogCmdHandlerInit(void);

/**
 * @brief 
 *
 * @param fmt
 * @param args
 */
static void
cLogFormatPrint(const char *fmt, va_list args)
{
	int hrs, mins, sec, day, month, year, off;
	time_t now;
	time(&now);

	struct tm *local = localtime(&now);

    hrs     = local->tm_hour;      	    // get hours since midnight (0-23)
    mins    = local->tm_min;     	    // get minutes passed after the hour (0-59)
    sec     = local->tm_sec;     	    // get seconds passed after minute (0-59)
    day     = local->tm_mday;           // get day of month (1 to 31)
    month   = local->tm_mon + 1;   	    // get month of year (0 to 11)
    year    = local->tm_year + 1900;    // get year since 1900

    /* Prepend timestamp to new buffer */
    off = sprintf(cLogBuf, "%d-%d-%d %02d:%02d:%02d: [%s] ", day, month, year,
                  hrs, mins, sec, cLogCfg->appName);

    /* Append log to new buffer */
    vsnprintf(cLogBuf + off, CLOG_BUF_SIZE, fmt, args);

    /* Print based on type configured */
    if (cLogCfg->cLogTypeMap & CLOG_TYPE_CONSOLE)
    {
        fprintf(stdout, "%s\n", cLogBuf);
    }
    if (cLogCfg->cLogTypeMap & CLOG_TYPE_FILE)
    {
        /* TODO */
    }
    if (cLogCfg->cLogTypeMap & CLOG_TYPE_SYSLOG)
    {
        /* TODO */
    }
    return;
}

/**
 * @brief 
 *
 * @param appName
 * @param logType
 * @param cLogLevel
 *
 * @return 
 */
CLogRet_t
cLogInit(const char *appName, int logType, int cLogLevel)
{
    cLogCfg = (CLogCfg_t *) malloc (sizeof(CLogCfg_t));
    if (NULL == cLogCfg)
    {
        return CLOG_ERR;
    }
    memset (cLogCfg, 0, sizeof(CLogCfg_t));

    cLogBuf = (char *) malloc (CLOG_BUF_SIZE);
    if (NULL == cLogBuf)
    {
        return CLOG_ERR;
    }
    memset (cLogBuf, 0, CLOG_BUF_SIZE);

    memcpy(cLogCfg->appName, appName, APP_NAME_LEN);
    cLogCfg->cLogTypeMap |= logType;
    cLogCfg->cLogLevel = cLogLevel;

    cLogCmdHandlerInit();

    return CLOG_OK;
}

/**
 * @brief 
 *
 * @param cLogLevel
 * @param fmt
 * @param ...
 */
void
cLog(int cLogLevel, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    if (cLogLevel <= cLogCfg->cLogLevel)
    {
        cLogFormatPrint(fmt, args);
    }
}

/**
 * @brief 
 */
void
cLogDeinit(void)
{
    if (cLogCfg)
    {
        free (cLogCfg);
        cLogCfg = NULL;
    }

    if (cLogBuf)
    {
        free (cLogBuf);
        cLogBuf = NULL;
    }
}
