// Index.c
#include"Index.h"
#include<string.h>

// �Լ�����

/*
�Լ���: Index_Create
���: Index Link �迭�� �����.
�Է�: �Ҵ緮
���: ����
*/
void Index_Create(Index *indexLink, Long capacity) {
	Array_Create(&indexLink->businessCards, capacity, sizeof(BusinessCard*));
	strcpy(indexLink->name, "");
	indexLink->capacity = capacity;
	indexLink->length = 0;
}

/*
�Լ���: Index_Put
���: BusinessCard Link�� �Է¹޾� �迭�� �ְ� ��ġ(÷��)�� ����Ѵ�.
�Է�: BusinessCard Link
���: ÷��
*/
Long Index_Put(Index *indexLink, BusinessCard *index) {
	Long subscript;
	if (indexLink->capacity > indexLink->length) {
		subscript = Array_Store(&indexLink->businessCards, indexLink->length, &index, sizeof(BusinessCard*));
	}
	else {
		subscript = Array_AppendFromRear(&indexLink->businessCards, &index, sizeof(BusinessCard*));
		indexLink->capacity++;
	}
	indexLink->length++;
	return subscript;
}

/*
�Լ���: Index_Draw
���: ÷�ڸ� �Է¹޾� �迭�� �ش� ��ġ�� �����.
�Է�: ÷��
���: ÷��(= 0)
*/
Long Index_Draw(Index *indexLink, Long subscript) {
	Long index;
	index = Array_Delete(&indexLink->businessCards, subscript, sizeof(BusinessCard*));
	indexLink->capacity--;
	indexLink->length--;
	return index;
}

/*
�Լ���: Index_Find
���: BusinessCard Link�� �Է¹޾� �迭���� ��ġ�ϴ� ��ġ(÷��)�� ����Ѵ�.
�Է�: BusinessCard Link
���: ��ġ(÷��)
*/
Long Index_Find(Index *indexLink, BusinessCard *index) {
	Long subscript;
	subscript = Array_LinearSearchUnique(&indexLink->businessCards, index, sizeof(BusinessCard*), ComparePointers);
	return subscript;
}

/*
�Լ���: Index_GetAt
���: ��ġ(÷��)�� �Է¹޾� �ش� ��ġ�� BusinessCard Link�� ����Ѵ�.
�Է�: ÷��
���: BusinessCard Link
*/
BusinessCard* Index_GetAt(Index *indexLink, Long subscript) {
	BusinessCard *index;
	Array_GetAt(&indexLink->businessCards, subscript, &index, sizeof(BusinessCard*));
	return index;
}

/*
�Լ���: Index_Destroy
���: Index Link �迭�� �����.
�Է�: ����
���: ����
*/
void Index_Destroy(Index *indexLink) {
	Array_Destroy(&indexLink->businessCards);
}

// ���Լ�

int ComparePointers(void *one, void *other) {
	int ret;
	if (*((BusinessCard**)one) < other) {
		ret = -1;
	}
	else if (*((BusinessCard**)one) == other) {
		ret = 0;
	}
	else if (*((BusinessCard**)one) > other) {
		ret = -1;
	}
	return ret;
}