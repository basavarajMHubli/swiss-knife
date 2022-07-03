
#include <stdio.h>
#include "bst.h"

/* Driver program to test above functions*/
int main()
{
    BstNode* root = NULL;

    root = InsertNode(NULL, 100);
    InsertNode(root, 20);
    InsertNode(root, 200);
    InsertNode(root, 10);
    InsertNode(root, 30);
    InsertNode(root, 150);
    InsertNode(root, 300);

    printf("\nPreorder traversal of binary tree is \n");
    PrintPreorder(root);

    printf("\nInorder traversal of binary tree is \n");
    PrintInorder(root);

    printf("\nPostorder traversal of binary tree is \n");
    PrintPostorder(root);

    putchar('\n');

    root = DeleteNode(root, 100);
    printf("\nPreorder traversal of binary tree after deletion \n");
    PrintPreorder(root);

    putchar('\n');
    return 0;
}
