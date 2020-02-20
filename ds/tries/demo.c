
#include <stdio.h>
#include "trie.h"

/*
 * Demo code to test trie
 */

int main()
{

    char *keys[] = {"basu", "deepa", "sarita", "mahadev"};
    TrieRetType ret;

    TrieNode *root = createTrieNode();

    ret = insertTrieNode (root, keys[0]);
    if (ret == TRIE_SUCCESS)
    {
        printf("%s inserted in trie\n", keys[0]);
    }
    else
    {
        printf("%s not inserted in trie\n", keys[0]);
    }

    ret = searchTrieNode (root, keys[0]);

    if (ret == TRIE_FOUND)
    {
        printf("%s found in trie\n", keys[0]);
    }
    else
    {
        printf("%s not found in trie\n", keys[0]);
    }

    ret = searchTrieNode (root, keys[1]);

    if (ret == TRIE_FOUND)
    {
        printf("%s found in trie\n", keys[1]);
    }
    else
    {
        printf("%s not found in trie\n", keys[1]);
    }
    return 0;
}
