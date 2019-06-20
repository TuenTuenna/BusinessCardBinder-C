//BinaryTree.c

#include "BinaryTree.h"
#include <stdlib.h>
#include <memory.h>

void BinaryTree_Create(BinaryTree *binaryTree) {
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;

}

BinaryNode* BinaryTree_Insert(BinaryTree *binaryTree, void *key, size_t size, int(*compare)(void*, void*)) {
	BinaryNode *index;
	BinaryNode *it;
	BinaryNode *parent = NULL;

	index = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
	memcpy(index + 1, key, size);
	index->left = NULL;
	index->right = NULL;
	it = binaryTree->root;
	while (it != NULL) {
		parent = it;
		if (compare(it + 1, key) > 0) {
			it = it->left;
		}
		else {
			it = it->right;
		}
	}
	if (parent != NULL) {
		if (compare(parent + 1, key) > 0) {
			parent->left = index;
		}
		else {
			parent->right = index;
		}
		if (compare(binaryTree->root + 1, key) > 0) {
			binaryTree->balance--;
		}
		else {
			binaryTree->balance++;
		}
	}
	else {
		binaryTree->root = index;
	}
	binaryTree->length++;

	return index;
}



BinaryNode* BinaryTree_Search(BinaryTree *binaryTree, void *key, size_t size, int(*compare)(void*, void*)) {
	BinaryNode *index;

	index = binaryTree->root;
	while (index != NULL && compare(index + 1, key) != 0) {
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	return index;
}


BinaryNode* BinaryTree_Delete(BinaryTree *binaryTree, void *key, size_t size, int(*compare)(void*, void*)) {

	BinaryNode *index;
	BinaryNode *indexParent = NULL;
	BinaryNode *it = NULL;
	BinaryNode* itParent = NULL;
	void *keyBalance;

	keyBalance = malloc(size);
	memcpy(keyBalance, binaryTree->root + 1, size);
	index = binaryTree->root;
	while (index != NULL && compare(index + 1, key) != 0) {
		indexParent = index;
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	itParent = index;
	if (index->right != NULL || index->left != NULL) {
		if (index->right != NULL) {
			it = index->right;
			while (it->left != NULL) {
				itParent = it;
				it = it->left;
			}
			it->left = index->left;
			if (index != itParent) {
				itParent->left = it->right;
				it->right = index->right;
			}
		}
		else {
			it = index->left;
			while (it->right != NULL) {
				itParent = it;
				it = it->right;
			}
			it->right = index->right;
			if (index != itParent) {
				itParent->right = it->left;
				it->left = index->left;
			}

		}
	}
	if (index != binaryTree->root) {
		if (indexParent->right != index) {
			indexParent->left = it;
		}
		else {
			indexParent->right = it;
		}
	}
	else {
		binaryTree->root = it;
	}
	if (index != NULL) {
		free(index);
		index = NULL;
	}

	if (compare(keyBalance, key) != 0) {
		if (compare(keyBalance, key) > 0) {
			binaryTree->balance++;
		}
		else {
			binaryTree->balance--;
		}
	}
	binaryTree->length--;

	if (keyBalance != NULL) {
		free(keyBalance);
		keyBalance = NULL;
	}
		return index;
}


void BinaryTree_MakeBalance(BinaryTree *binaryTree, size_t size) {
	void (*keys);
	Long count;

	BinaryTree_MakeKeys(binaryTree, &keys, &count, size);
	BinaryTree_DeleteAllItems(binaryTree);
	BinaryTree_MakeTree(binaryTree, keys, count, size);
	if (keys != NULL) {
		free(keys);
		keys = NULL;
	}
}

void BinaryTree_MakeKeys(BinaryTree *binaryTree, void*(*keys), Long *count, size_t size) {
	Long index = 0;
	*count = 0;
	*keys = calloc(binaryTree->length, size);
	BinaryTree_Node_MakeKeys(binaryTree->root, *keys, count, &index, size);
}

void BinaryTree_Node_MakeKeys(BinaryNode *node, void(*keys), Long *count, Long *index, size_t size) {
	if (node != NULL) {
		BinaryTree_Node_MakeKeys(node->left, keys, count, index, size);
		memcpy((char*)keys + ((*index)*size), node + 1, size);
		(*count)++;
		(*index)++;
		BinaryTree_Node_MakeKeys(node->right, keys, count, index, size);
	}
}

void BinaryTree_DeleteAllItems(BinaryTree *binaryTree) {
	BinaryTree_Node_DeleteAllItems(binaryTree->root);
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

void BinaryTree_Node_DeleteAllItems(BinaryNode *node) {
	if (node != NULL) {
		BinaryTree_Node_DeleteAllItems(node->left);
		BinaryTree_Node_DeleteAllItems(node->right);
		if (node != NULL) {
			free(node);
			node = NULL;
		}
	}
}

void BinaryTree_MakeTree(BinaryTree *binaryTree, void(*keys), Long count, size_t size) {
	Long low = 0;
	Long high;
	Long remainder;
	high = count - 1;

	binaryTree->root = BinaryTree_Node_MakeTree(keys, low, high, size);
	binaryTree->length = count;
	remainder = count % 2;
	if (remainder != 0) {
		binaryTree->balance = 1;
	}
	else {
		binaryTree->balance = 0;
	}
}

BinaryNode* BinaryTree_Node_MakeTree(void(*keys), Long low, Long high, size_t size) {
	BinaryNode *node = NULL;
	Long middle;
	if (low <= high) {
		middle = (low + high) / 2;
		node = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
		memcpy(node + 1, ((char*)keys) + (middle*size), size);
		node->left = BinaryTree_Node_MakeTree(keys, low, middle - 1, size);
		node->right = BinaryTree_Node_MakeTree(keys, middle + 1, high, size);
	}
	return node;
}



void BinaryTree_Destroy(BinaryTree *binaryTree) {
	BinaryTree_Node_Destroy(binaryTree->root);
}


void BinaryTree_Node_Destroy(BinaryNode *node) {
	if (node != NULL) {
		BinaryTree_Node_Destroy(node->left);
		BinaryTree_Node_Destroy(node->right);
		if (node != NULL) {
			free(node);
			node = NULL;
		}
	}
}

void BinaryTree_GetAt(BinaryTree *binaryTree, BinaryNode *index, void *key, size_t size) {
	memcpy(key, index + 1, size);
}


void BinaryTree_Preorder(BinaryTree *binaryTree, void *(*keys), Long *count, size_t size) {
	Long index = 0;
	*count = 0;

	*keys = calloc(binaryTree->length, size);
	BinaryTree_Node_Preorder(binaryTree->root, *keys, count, &index, size);
}

void BinaryTree_Node_Preorder(BinaryNode *node, void(*keys), Long *count, Long *index, size_t size) {
    if (node != NULL) {
		memcpy(((char*)keys) + ((*index)*size), node + 1, size);
		(*count)++;
		(*index)++;
		BinaryTree_Node_Preorder(node->left, keys, count, index, size);
		BinaryTree_Node_Preorder(node->right, keys, count, index, size);
	}
}

