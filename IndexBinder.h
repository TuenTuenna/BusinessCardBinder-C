#ifndef _INDEXBINDER_H
#define _INDEXBINDER_H
#include "BinaryTree.h"
#include"Index.h"
#include"BusinessCardBinder.h"

typedef struct _index Index;
typedef signed long int Long;
typedef struct _businessCard BusinessCard;
typedef struct _indexBinder {
	BinaryTree indexes;
	Long length;
} IndexBinder;

//함수선언
void IndexBinder_Create(IndexBinder *indexBinder);
Index* IndexBinder_Put(IndexBinder *indexBinder, BusinessCard *index);
Index* IndexBinder_Find(IndexBinder *indexBinder, char(*companyName));
Index* IndexBinder_Draw(IndexBinder *indexBinder, BusinessCard *index, char(*companyName));
void IndexBinder_Arrange(IndexBinder *indexBinder);
void IndexBinder_MakeList(IndexBinder *indexBinder, Index *(*indexes), Long *count);
void IndexBinder_Destroy(IndexBinder *indexBinder);
void Node_Index_Destroy(BinaryNode *node);
int CompareKeys(void *one, void *other);

#endif //_INDEXBINDER_H