/**
 * @file clog_utils.c
 * @brief Utility file for c-logger
 * @author Basavaraj M. Hubli
 * @version 2.0
 * @date 2020-03-30
 */

#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <errno.h>
#include <signal.h>
#include "clog.h"

#define MQ_MSG_MAX      10
#define MQ_MSG_LEN      256
#define MQ_NAME_LEN     128

#define NOTIFY_SIG SIGUSR1

mqd_t mqDes;
extern CLogCfg_t   *cLogCfg;

extern void cLogInitFile();
extern void cLogInitSyslog();

/**
 * @brief Function to enable signal handling for incoming msg q
 */
static
void cLogRegisterNotify(void)
{
    int ret;
    struct sigevent sev;

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = NOTIFY_SIG;

    ret = mq_notify(mqDes, &sev);
    if (-1 == ret)
    {
        perror("mq_notify");
    }
}

/**
 * @brief Handler function for new configuration
 *
 * @param signo
 */
static
void cLogCmdHandler(int signo)
{
    ssize_t rdBytes;
    char buf[MQ_MSG_LEN] = {0};
    CLogCfg_t *newCfg = (CLogCfg_t *)buf;

    rdBytes = mq_receive(mqDes, buf, MQ_MSG_LEN, NULL);
    if (-1 == rdBytes)
    {
        perror("Failed to receive");
        return;
    }

    fprintf(stdout, "New configuration received. %d\n", newCfg->cLogLevel);

    cLogCfg->cLogLevel = newCfg->cLogLevel;
    cLogCfg->cLogTypeMap = newCfg->cLogTypeMap;

    if (cLogCfg->cLogTypeMap & CLOG_TYPE_FILE)
    {
        if (cLogCfg->_isFileOpen == false)
        {
            cLogInitFile();
        }
    }

    if (cLogCfg->cLogTypeMap & CLOG_TYPE_SYSLOG)
    {
        if (cLogCfg->_isSyslogOpen == false)
        {
            cLogInitSyslog();
        }
    }

    cLogRegisterNotify();
}

/**
 * @brief Function to initialize configuration change commands
 */
void
cLogCmdHandlerInit(void)
{
    int ret;
    char mqName[MQ_NAME_LEN] = {0};

    struct sigaction sa;
    struct mq_attr mqAttr;

    mqAttr.mq_maxmsg = MQ_MSG_MAX;
    mqAttr.mq_msgsize = MQ_MSG_LEN;

    sprintf(mqName, "/%s", cLogCfg->appName);
    ret = mq_unlink(mqName);
    if (-1 == ret)
    {
        perror("unlink");
    }

    mqDes = mq_open(mqName, O_CREAT | O_RDONLY, S_IWUSR|S_IRUSR,
                    &mqAttr);
    if (-1 == mqDes)
    {
        perror("Failed to open mq");
        return;
    }

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = cLogCmdHandler;
    if (sigaction(NOTIFY_SIG, &sa, NULL) == -1)
    {
        perror("sigaction");
        return;
    }

    cLogRegisterNotify();
}
