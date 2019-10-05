
/**
 * @file circ-buff.h
 * @brief Circular buffer implementation
 * @author Basavaraj M. Hubli
 * @version 1.0
 * @date 2019-09-25
 */

#ifndef __CIRC_BUF_H__
#define __CIRC_BUF_H__

#include <stdbool.h>

/**
 * @brief
 */
typedef enum circ_buf_err {
    CIRC_BUF_NOERR  = 0,
    CIRC_BUF_ERR    = -1,
    CIRC_BUF_EMPTY  = -2,
    CIRC_BUF_FULL   = -3
} circ_buf_err_t;

/**
 * @brief
 */
typedef struct circ_buf {
    int head;
    int tail;
    int max_elem;
    int *data;
} circ_buf_t;

/* Function prototype */
int circ_buf_init(circ_buf_t **circ_buf, int max_elem);
int circ_buf_deinit(circ_buf_t *circ_buf);

int circ_buf_push(circ_buf_t *circ_buf, int elem);
int circ_buf_pop(circ_buf_t *circ_buf, int *elem);

bool is_circ_buf_empty(circ_buf_t *circ_buf);
bool is_circ_buf_full(circ_buf_t *circ_buf);

#endif /* __CIRC_BUF_H__ */
