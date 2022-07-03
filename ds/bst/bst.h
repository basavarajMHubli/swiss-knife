
/**
 * @file bst.h
 * @brief Implementation of binary search tree
 * @author Basavaraj M. Hubli
 * @version 1.0
 * @date 2021-06-16
 */

#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct bstNode {
	int data;
	struct bstNode* left;
	struct bstNode* right;
} BstNode;

/* Helper function that allocates a new node with the
given data and NULL left and right pointers. */
BstNode* NewNode(int data)
{
	BstNode* node = (BstNode*)malloc(sizeof(BstNode));
    assert ((node != NULL) && "Malloc failed");

	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return (node);
}

/* Given a binary tree, print its nodes according to the
"bottom-up" postorder traversal. */
void PrintPostorder(BstNode* node)
{
	if (node == NULL)
		return;

	// first recur on left subtree
	PrintPostorder(node->left);

	// then recur on right subtree
	PrintPostorder(node->right);

	// now deal with the node
	printf("%d ", node->data);
}

/* Given a binary tree, print its nodes in inorder*/
void PrintInorder(BstNode* node)
{
	if (node == NULL)
		return;

	/* first recur on left child */
	PrintInorder(node->left);

	/* then print the data of node */
	printf("%d ", node->data);

	/* now recur on right child */
	PrintInorder(node->right);
}

/* Given a binary tree, print its nodes in preorder*/
void PrintPreorder(BstNode* node)
{
	if (node == NULL)
		return;

	/* first print data of node */
	printf("%d ", node->data);

	/* then recur on left sutree */
	PrintPreorder(node->left);

	/* now recur on right subtree */
	PrintPreorder(node->right);
}

/* A utility function to insert
   a new node with given data in
 * BST */
BstNode* InsertNode(BstNode* node, int data)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return NewNode(data);

    /* Otherwise, recur down the tree */
    if (data < node->data)
        node->left = InsertNode(node->left, data);
    else if (data > node->data)
        node->right = InsertNode(node->right, data);

    /* return the (unchanged) node pointer */
    return node;
}

BstNode* GetLeftMostNode(BstNode *node)
{
    BstNode *cur = node;
    while (cur && cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}

BstNode* DeleteNode(BstNode* node, int data)
{
    if (node == NULL)
        return NULL;

    if (data < node->data) {
        node->left = DeleteNode(node->left, data);
    } else if (data > node->data) {
        node->right = DeleteNode(node->right, data);
    } else if (data == node->data) {
        if (node->left == NULL) {
            BstNode *rightNode = node->right;
            free (node);
            return rightNode;
        } else if (node->right == NULL) {
            BstNode *leftNode = node->left;
            free (node);
            return leftNode;
        }

        /* Get min value node or inorder successor */
        BstNode *minNode = GetLeftMostNode(node->right);

        node->data = minNode->data;
        node->right = DeleteNode(node->right, minNode->data);
    }
    return node;
}

#endif /* __BST_H__ */
