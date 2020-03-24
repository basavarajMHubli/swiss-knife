/**
 * @file clog_ctl.c
 * @brief Controlled logger ctl for controlling log levels, types
 * @author Basavaraj M. Hubli
 * @version 1.0
 * @date 2020-03-24
 */

#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "clog.h"

#define LOG_LEVEL_INFO      "info"
#define LOG_LEVEL_DEBUG     "debug"
#define LOG_LEVEL_ERROR     "error"

#define LOG_TYPE_CONSOLE    "console"
#define LOG_TYPE_FILE       "file"
#define LOG_TYPE_SYSLOG     "syslog"

/**
 * @brief 
 *
 * @param cfg
 *
 * @return 
 */
static int
cLogSendCmd(CLogCfg_t *cfg)
{
    int ret;
    char mqName[128] = {0};
    char *buf = (char *)cfg;

    mqd_t mqDes;

    sprintf(mqName, "/%s", cfg->appName);
    mqDes = mq_open(mqName, O_RDWR);
    if (-1 == mqDes)
    {
        perror("Failed to open mq");
        return -1;
    }

    printf("Writing msg...");
    ret = mq_send(mqDes, buf, sizeof(CLogCfg_t), 0);
    if (-1 == ret)
    {
        perror("Failed to open mq");
        return -1;
    }
    printf("Done\n");

    return 0;
}

/**
 * @brief 
 */
static void
displayUsage(void)
{
    fprintf(stderr, "Usage: ./clog_ctl -p <logger name> -t <log type> -l <log level>\n");
    fprintf(stderr, "<log type>: console/syslog/file\n");
    fprintf(stderr, "<log level>: info/error/debug\n");
    return;
}

/**
 * @brief 
 *
 * @param argc
 * @param argv[]
 *
 * @return 
 */
int
main(int argc, char *argv[])
{
    int opt, ret;
    char *loggerName = NULL, *logType = NULL, *logLevel = NULL;

    CLogCfg_t cfg;

    while ((opt = getopt(argc, argv, "p:t:l:h")) != -1)
    {
        switch (opt)
        {
            case 'p':
                loggerName = optarg;
                fprintf(stdout, "Logger name: %s\n", loggerName);
                break;
            case 't':
                logType = optarg;
                fprintf(stdout, "Log type: %s\n", logType);
                break;
            case 'l':
                logLevel = optarg;
                fprintf(stdout, "Log level: %s\n", logLevel);
                break;
            case 'h':
            default:
                displayUsage();
                exit(EXIT_FAILURE);
        }
    }

    memset(&cfg, 0, sizeof(cfg));

    strncpy(cfg.appName, loggerName, sizeof(cfg.appName));
    if (logLevel)
    {
        if (!strcmp(logLevel, LOG_LEVEL_INFO))
            cfg.cLogLevel = CLOG_LEVEL_INFO;
        else if (!strcmp(logLevel, LOG_LEVEL_DEBUG))
            cfg.cLogLevel = CLOG_LEVEL_DEBUG;
        else if (!strcmp(logLevel, LOG_LEVEL_ERROR))
            cfg.cLogLevel = CLOG_LEVEL_ERROR;
        else
        {
            fprintf(stderr, "Invalid Log level (%s). Aborting\n", logLevel);
            exit(EXIT_FAILURE);
        }
    }

    if (logType)
    {
        if (!strcmp(logType, LOG_TYPE_CONSOLE))
            cfg.cLogTypeMap |= CLOG_TYPE_CONSOLE;
        else if (!strcmp(logType, LOG_TYPE_FILE))
            cfg.cLogTypeMap |= CLOG_TYPE_FILE;
        else if (!strcmp(logType, LOG_TYPE_SYSLOG))
            cfg.cLogTypeMap |= CLOG_TYPE_SYSLOG;
        else
        {
            fprintf(stderr, "Invalid Log type (%s). Aborting\n", logType);
            exit(EXIT_FAILURE);
        }
    }

    ret = cLogSendCmd(&cfg);
    if (-1 == ret)
    {
        fprintf(stderr, "Failed to send cmd\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
