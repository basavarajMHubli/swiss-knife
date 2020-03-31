
#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26
#define CHAR_TO_IDX(c) ((unsigned int)c - (unsigned int)'a')

/**
 * @brief Trie api return types
 */
typedef enum trieRetType
{
    TRIE_SUCCESS,
    TRIE_FAILED,
    TRIE_FOUND,
    TRIE_NOTFOUND
} TrieRetType;

/**
 * @brief Trie node data structure
 */
typedef struct trieNode
{
    struct trieNode *children[ALPHABET_SIZE];
    bool isLastNode;
} TrieNode;

/**
 * @brief Create new trie node
 *
 * @return TRIE_*
 */
TrieNode *createTrieNode(void)
{
    TrieNode *node;

    node = (TrieNode *) malloc (sizeof (TrieNode));

    if (node)
    {
        for (int idx = 0; idx < ALPHABET_SIZE; idx++)
        {
            node->children[idx] = NULL;
            node->isLastNode = false;
        }
    }

    return node;
}

/**
 * @brief Insert key into trie ds
 *
 * @param root Trie ds
 * @param key Element to be inserted
 *
 * @return TRIE_*
 */
TrieRetType insertTrieNode(TrieNode *root, const char *key)
{
    TrieNode *cur;
    unsigned int keyLen, cIdx;

    if (!root)
        return TRIE_FAILED;

    keyLen = strlen(key);

    cur = root;
    for (int i = 0; i < keyLen; i++)
    {
        cIdx = CHAR_TO_IDX(key[i]);

        if (cur->children[cIdx] == NULL)
        {
            cur->children[cIdx] = createTrieNode();
            if (cur->children[cIdx] == NULL)
                return TRIE_FAILED;
        }

        cur = cur->children[cIdx];
    }
    cur->isLastNode = true;

    return TRIE_SUCCESS;
}

/**
 * @brief Search trie data structure for key
 *
 * @param root Trie ds
 * @param key Element to be searched
 *
 * @return TRIE_*
 */
TrieRetType searchTrieNode(TrieNode *root, const char *key)
{
    TrieNode *cur;
    unsigned int keyLen, cIdx;

    if (!root)
        return TRIE_FAILED;

    keyLen = strlen(key);

    cur = root;
    for (int i = 0; i < keyLen; i++)
    {
        cIdx = CHAR_TO_IDX(key[i]);
        if (cur->children[cIdx] == NULL)
            return TRIE_NOTFOUND;

        cur = cur->children[cIdx];
    }

    return (cur->isLastNode ? TRIE_FOUND : TRIE_NOTFOUND);
}

#endif /* __TRIE_H__ */
