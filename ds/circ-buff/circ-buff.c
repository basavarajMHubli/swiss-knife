
/**
 * @file circ-buff.c
 * @brief
 * @author Basavaraj M. Hubli
 * @version 1.0
 * @date 2019-09-25
 */

#include "circ-buff.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Function to initialize circular buffer ds
 *
 * @param circ_buf to be initialized
 * @param max_elem max elements
 *
 * @return CIRC_BUF_*
 */
int
circ_buf_init(circ_buf_t **circ_buf, int max_elem)
{
    int buf_size;

    *circ_buf = (circ_buf_t *) malloc(sizeof(circ_buf_t));
    if (*circ_buf == NULL) {
        return CIRC_BUF_ERR;
    }

    buf_size = sizeof(*(*circ_buf)->data) * max_elem;
    (*circ_buf)->data = (int *) malloc(buf_size);
    if ((*circ_buf)->data == NULL) {
        return CIRC_BUF_ERR;
    }

    memset((*circ_buf)->data, 0, buf_size);
    (*circ_buf)->head = (*circ_buf)->tail = 0;
    (*circ_buf)->max_elem = max_elem;

    return CIRC_BUF_NOERR;
}

/**
 * @brief Push/Insert element into circ buff
 *
 * @param circ_buf ds
 * @param elem element to be inserted/pushed
 *
 * @return CIRC_BUF_*
 */
int
circ_buf_push(circ_buf_t *circ_buf, int elem)
{
    if (is_circ_buf_full(circ_buf)) {
        return CIRC_BUF_FULL;
    }

    circ_buf->data[circ_buf->tail] = elem;
    circ_buf->tail = (circ_buf->tail + 1) % circ_buf->max_elem;

    return CIRC_BUF_NOERR;
}

/**
 * @brief Pop/Remove element from circ buff
 *
 * @param circ_buf ds
 * @param elem popped element
 *
 * @return CIRC_BUF_*
 */
int
circ_buf_pop(circ_buf_t *circ_buf, int *elem)
{
    if (is_circ_buf_empty(circ_buf)) {
        return CIRC_BUF_EMPTY;
    }

    *elem = circ_buf->data[circ_buf->head];
    circ_buf->head = (circ_buf->head + 1) % circ_buf->max_elem;

    return CIRC_BUF_NOERR;
}

/**
 * @brief Function to check if circ buff is empty
 *
 * @param circ_buf ds
 *
 * @return true if empty, else false
 */
inline bool
is_circ_buf_empty(circ_buf_t *circ_buf)
{
    return (circ_buf->head == circ_buf->tail);
}

/**
 * @brief Function to check if circ buff is full
 *
 * @param circ_buf ds
 *
 * @return true if full, else false
 */
inline bool
is_circ_buf_full(circ_buf_t *circ_buf)
{
    return (((circ_buf->tail + 1) % circ_buf->max_elem) == circ_buf->head);
}

/**
 * @brief Function to deinitialize circ buff
 *
 * @param circ_buf
 *
 * @return
 */
int
circ_buf_deinit(circ_buf_t *circ_buf)
{
    circ_buf->head = circ_buf->tail = circ_buf->max_elem = 0;
    free(circ_buf->data);
    free(circ_buf);

    return CIRC_BUF_NOERR;
}
