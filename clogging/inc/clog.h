/**
 * @file clog.h
 * @brief Controlled logging utility
 * @author Basavaraj M. Hubli
 * @version 1.0
 * @date 2020-03-24
 */

/* TODO: Currently, console logging is implemented. syslog and file logging yet to be implemented */

#ifndef __CLOG_H__
#define __CLOG_H__

#define CLOG_TYPE_CONSOLE (1 << 0)
#define CLOG_TYPE_FILE    (1 << 1)
#define CLOG_TYPE_SYSLOG  (1 << 2)

#define cLogInfo(...)   cLog(CLOG_LEVEL_INFO, __VA_ARGS__)
#define cLogDebug(...)  cLog(CLOG_LEVEL_DEBUG, __VA_ARGS__)
#define cLogError(...)  cLog(CLOG_LEVEL_ERROR,__VA_ARGS__)

#define APP_NAME_LEN    64

/**
 * @brief Logger configuration structure
 */
typedef struct cLogCfg_s
{
    char            appName[APP_NAME_LEN];   /* Application name */
    unsigned char   cLogTypeMap; /* bitmap: cLog_TYPE_* type */
    unsigned char   cLogLevel;   /* enum ClogLevel */
} CLogCfg_t;

/**
 * @brief Function return value enum
 */
typedef enum cLogRet_e
{
    CLOG_ERR = -1,
    CLOG_OK  = 0
} CLogRet_t;

/**
 * @brief Log level enum
 */
typedef enum cLogLevel_e
{
    CLOG_LEVEL_ERROR    = 0,
    CLOG_LEVEL_INFO     = 1,
    CLOG_LEVEL_DEBUG    = 2,
    CLOG_LEVEL_MAX
} CLogLevel_t;

void        cLog(int cLogLevel, const char *fmt, ...);
CLogRet_t   cLogInit(const char *appName, int logType, int cLogLevel);
void        cLogDeinit(void);

#endif /* __CLOG_H__ */
