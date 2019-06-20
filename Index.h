// Index.h

#ifndef _INDEX_H
#define _INDEX_H
#include"Array.h"

// �ڷ��� ����
typedef signed long int Long;
typedef struct _businessCard BusinessCard;
typedef struct _index {
	char name[64];
	Array businessCards;
	Long capacity;
	Long length;
} Index;

// �Լ�����
void Index_Create(Index *indexLink, Long capacity);
Long Index_Put(Index *indexLink, BusinessCard *index);
Long Index_Draw(Index *indexLink, Long subscript);
Long Index_Find(Index *indexLink, BusinessCard *index);
BusinessCard* Index_GetAt(Index *indexLink, Long subscript);
void Index_Destroy(Index *indexLink);
int ComparePointers(void *one, void *other);

#endif // _INDEX_H
