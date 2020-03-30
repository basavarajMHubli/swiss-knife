/**
 * @file clog.c
 * @brief Controlled logging utility
 * @author Basavaraj M. Hubli
 * @version 2.0
 * @date 2020-03-30
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <syslog.h>
#include <time.h>
#include "clog.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CLOG_BUF_SIZE       1024
#define CLOG_FILE_PATH      "/tmp"
#define CLOG_MAX_FILENAME   128

CLogCfg_t   *cLogCfg;
char        *cLogBuf;

extern void cLogCmdHandlerInit(void);

static int
addTimeStamp(char *clogMsg)
{
	int hrs, mins, sec, day, month, year, off;
	time_t now;
	time(&now);

	struct tm *local = localtime(&now);

    hrs     = local->tm_hour;
    mins    = local->tm_min;
    sec     = local->tm_sec;
    day     = local->tm_mday;
    month   = local->tm_mon + 1;   	    // get month of year (0 to 11)
    year    = local->tm_year + 1900;    // get year since 1900

    /* Prepend timestamp to new buffer */
    off = sprintf(cLogBuf, "%d-%d-%d %02d:%02d:%02d: [%s] ", day, month, year,
                  hrs, mins, sec, cLogCfg->appName);

    return off;
}

static void
cLogConsolePrint(const char *cLogMsg)
{
    fprintf(stdout, "%s", cLogMsg);
}

static void
cLogFilePrint(const char *cLogMsg)
{
    ssize_t ret;

    ret = write(cLogCfg->_fileFd, (void *)cLogMsg, strlen(cLogMsg));
    sync();
    (void)ret;
}

static void
cLogSyslogPrint(const char *cLogMsg)
{
    int syslogLevel;

    if (cLogCfg->cLogLevel == CLOG_LEVEL_INFO)
        syslogLevel = LOG_INFO;
    else if (cLogCfg->cLogLevel == CLOG_LEVEL_DEBUG)
        syslogLevel = LOG_DEBUG;
    else if (cLogCfg->cLogLevel == CLOG_LEVEL_ERROR)
        syslogLevel = LOG_ERR;
    else
        syslogLevel = LOG_INFO;

    syslog(syslogLevel, "%s", cLogMsg);
}

/**
 * @brief 
 *
 * @param fmt
 * @param args
 */
static void
cLogModulePrint(const char *fmt, va_list args)
{
    int off;

    off = addTimeStamp(cLogBuf);

    /* Append log to new buffer */
    vsnprintf(cLogBuf + off, CLOG_BUF_SIZE, fmt, args);

    /* Print based on type configured */
    if (cLogCfg->cLogTypeMap & CLOG_TYPE_CONSOLE)
    {
        cLogConsolePrint(cLogBuf);
    }
    if (cLogCfg->cLogTypeMap & CLOG_TYPE_FILE)
    {
        cLogFilePrint(cLogBuf);
    }
    if (cLogCfg->cLogTypeMap & CLOG_TYPE_SYSLOG)
    {
        cLogSyslogPrint(cLogBuf + off);
    }
    return;
}

void
cLogInitFile(void)
{
    char fileName[CLOG_MAX_FILENAME] = {0};
    sprintf(fileName, "%s/%s.log", CLOG_FILE_PATH, cLogCfg->appName);

    cLogCfg->_fileFd = open(fileName, O_CREAT|O_RDWR|O_APPEND, S_IRUSR|S_IWUSR);
    if (-1 == cLogCfg->_fileFd)
    {
        perror("open");
        cLogCfg->_isFileOpen = false;
        return;
    }
    cLogCfg->_isFileOpen = true;

    return;
}

void
cLogInitSyslog(void)
{
    openlog(cLogCfg->appName, LOG_PID, LOG_USER);
    cLogCfg->_isSyslogOpen = true;
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

    cLogCfg->_fileFd = -1;
    cLogCfg->_isFileOpen = false;
    cLogCfg->_isSyslogOpen = false;

    if (cLogCfg->cLogTypeMap & CLOG_TYPE_FILE)
    {
        cLogInitFile();
    }

    if (cLogCfg->cLogTypeMap & CLOG_TYPE_SYSLOG)
    {
        cLogInitSyslog();
    }

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
        cLogModulePrint(fmt, args);
    }
}

static void
cLogDeinitFile(void)
{
    close (cLogCfg->_fileFd);
    cLogCfg->_isFileOpen = false;
}

static void
cLogDeinitSyslog(void)
{
    closelog();
    cLogCfg->_isSyslogOpen = false;
}

/**
 * @brief 
 */
void
cLogDeinit(void)
{
    if (cLogCfg)
    {
        if (cLogCfg->_isFileOpen)
        {
            cLogDeinitFile();
        }

        if (cLogCfg->_isSyslogOpen)
        {
            cLogDeinitSyslog();
        }

        free (cLogCfg);
        cLogCfg = NULL;
    }

    if (cLogBuf)
    {
        free (cLogBuf);
        cLogBuf = NULL;
    }
}
