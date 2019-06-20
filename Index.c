// Index.c
#include"Index.h"
#include<string.h>

// 함수정의

/*
함수명: Index_Create
기능: Index Link 배열을 만든다.
입력: 할당량
출력: 없음
*/
void Index_Create(Index *indexLink, Long capacity) {
	Array_Create(&indexLink->businessCards, capacity, sizeof(BusinessCard*));
	strcpy(indexLink->name, "");
	indexLink->capacity = capacity;
	indexLink->length = 0;
}

/*
함수명: Index_Put
기능: BusinessCard Link를 입력받아 배열에 넣고 위치(첨자)를 출력한다.
입력: BusinessCard Link
출력: 첨자
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
함수명: Index_Draw
기능: 첨자를 입력받아 배열의 해당 위치를 지운다.
입력: 첨자
출력: 첨자(= 0)
*/
Long Index_Draw(Index *indexLink, Long subscript) {
	Long index;
	index = Array_Delete(&indexLink->businessCards, subscript, sizeof(BusinessCard*));
	indexLink->capacity--;
	indexLink->length--;
	return index;
}

/*
함수명: Index_Find
기능: BusinessCard Link를 입력받아 배열에서 일치하는 위치(첨자)를 출력한다.
입력: BusinessCard Link
출력: 위치(첨자)
*/
Long Index_Find(Index *indexLink, BusinessCard *index) {
	Long subscript;
	subscript = Array_LinearSearchUnique(&indexLink->businessCards, index, sizeof(BusinessCard*), ComparePointers);
	return subscript;
}

/*
함수명: Index_GetAt
기능: 위치(첨자)를 입력받아 해당 위치의 BusinessCard Link를 출력한다.
입력: 첨자
출력: BusinessCard Link
*/
BusinessCard* Index_GetAt(Index *indexLink, Long subscript) {
	BusinessCard *index;
	Array_GetAt(&indexLink->businessCards, subscript, &index, sizeof(BusinessCard*));
	return index;
}

/*
함수명: Index_Destroy
기능: Index Link 배열을 지운다.
입력: 없음
출력: 없음
*/
void Index_Destroy(Index *indexLink) {
	Array_Destroy(&indexLink->businessCards);
}

// 비교함수

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