#define _CRT_SECURE_NO_WARNINGS
#include "IndexBinder.h"
#include<string.h>

void IndexBinder_Create(IndexBinder *indexBinder) {
	BinaryTree_Create(&indexBinder->indexes);
	indexBinder->length;
}

Index* IndexBinder_Put(IndexBinder *indexBinder, BusinessCard *index) {
	Index key;
	BinaryNode *node;
	Index *indexLink;

	strcpy(key.name, index->company.name);
	node = BinaryTree_Search(&indexBinder->indexes, &key, sizeof(Index), CompareKeys);
	if (node == NULL) {
		Index_Create(&key, 10);
		strcpy(key.name, index->company.name);
		node = BinaryTree_Insert(&indexBinder->indexes, &key, sizeof(Index), CompareKeys);
		indexBinder->length++;
	}
	indexLink = (Index*)(node + 1);
	Index_Put(indexLink, index);

	return indexLink;
}

Index* IndexBinder_Find(IndexBinder *indexBinder, char(*companyName)) {
	BinaryNode *node;
	Index key;
	Index *indexLink = NULL;

	strcpy(key.name, companyName);
	node= BinaryTree_Search(&indexBinder->indexes, &key, sizeof(Index), CompareKeys);
	if (node != NULL) {
		indexLink = (Index*)(node + 1);
	}
	return indexLink;
}

Index* IndexBinder_Draw(IndexBinder *indexBinder, BusinessCard *index, char(*companyName)) {
	Index key;
	BinaryNode *node;
	Long subscript;
	Index *indexLink;

	strcpy(key.name, companyName);
	node= BinaryTree_Search(&indexBinder->indexes, &key, sizeof(Index), CompareKeys);
	indexLink = (Index*)(node + 1);
	subscript = Index_Find(indexLink, index);
	Index_Draw(indexLink, subscript);
	if (indexLink->length == 0) {
		Index_Destroy(indexLink);
		node = BinaryTree_Delete(&indexBinder->indexes, &key, sizeof(Index), CompareKeys);
		indexBinder->length--;
		indexLink = NULL;
	}

	return indexLink;
}

void IndexBinder_Arrange(IndexBinder *indexBinder) {
	BinaryTree_MakeBalance(&indexBinder->indexes, sizeof(Index));
}

void IndexBinder_MakeList(IndexBinder *indexBinder, Index *(*indexes), Long *count) {
	BinaryTree_MakeKeys(&indexBinder->indexes, indexes, count, sizeof(Index));
}

void Node_Index_Destroy(BinaryNode *node) {
	if (node != NULL) {
		Node_Index_Destroy(node->left);
		Node_Index_Destroy(node->right);
		Index_Destroy((Index*)(node + 1));
	}
}

void IndexBinder_Destroy(IndexBinder *indexBinder) {
	Node_Index_Destroy(indexBinder->indexes.root);
	BinaryTree_Destroy(&indexBinder->indexes);
}

int CompareKeys(void *one, void *other) {
	return strcmp(((Index*)one)->name, ((Index*)other)->name);
}