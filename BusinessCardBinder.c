//BusinessCardBinder.c

#define _CRT_SECURE_NO_WARNINGS
#include "BusinessCardBinder.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
main시나리오
1. 명함철을 만든다. (BusinessCardBinder_Create, LinkedList_Create
2. 색인철을 만든다.(IndexBinder_Create)
3. "홍길동", "회장","02", "hong@","박컴","서울시","021", "022", "park.com"명함을 만든다.
4. 명함철에 넣는다. (BusinessCardBinder_Put, LinkedList_AppendFromTail
5. 색인철에 넣는다. (IndexBinder_Put)
6. "김길동", "과장","031", "kim@","박컴","서울시","021", "022", "park.com"명함을 만든다.
7. 명함철에 넣는다. (BusinessCardBinder_Put, LinkedList_AppendFromTail
8. 색인철에 넣는다. (IndexBinder_Put)
9. "홍길동", "사원","041", "hong2@","삼성","서울시","02", "02", "samsung.com"명함을 만든다.
10. 명함철에 넣는다. (BusinessCardBinder_Put, LinkedList_AppendFromTail
11. 색인철에 넣는다. (IndexBinder_Put)
12. "박길동", "사장","031", "park@","현대","서울시","022", "022", "hyundai.com"명함을 만든다.
13. 명함철에 넣는다. (BusinessCardBinder_Put, LinkedList_AppendFromTail
14. 색인철에 넣는다. (IndexBinder_Put)
15. 홍길동을 찾는다.(BusinessCardBinder_Find)
16. 박컴을 찾는다.(IndexBinder_Find)
17. 마지막명함으로 이동한다.
18. 마지막명함을 꺼낸다. (BusinessCardBinder_Draw)
19. 색인철에서 꺼낸다. (IndexBinder_Draw)
20. 명함철에 넣는다. (BusinessCardBinder_Put)
21. 색인철에 넣는다. (IndexBinder_Put)
22. 색인철을 정리하다. (IndexBinder_Arrange)
23. 색인철 리스트를 만들다. (IndexBinder_MakeList)
24. 처음명함으로 이동하다. (BusinessCardBinder_First)
25. 색인철에서 확인하다. (IndexBinder_Find, Index_Find)
26. 이전명함으로 이동하다. (BusinessCardBinder_Previous)
27. 색인철에서 확인하다. (IndexBinder_Find, Index_Find)
28. "박길동"을 찾다. (BusinessCardBinder_Find)
29. 해당위치로 간다. (BusinessCardBinder_Move)
30. 색인철에서 확인하다. (IndexBinder_Find, Index_Find)
31. 마지막명함으로 이동하다. (BusinessCardBinder_Last)
32. 색인철에서 확인하다. (IndexBinder_Find, Index_Find)
33. 다음명함으로 이동하다. (BusinessCardBinder_Next)
34. 색인철에서 확인하다. (IndexBinder_Find, Index_Find)
35. 색인철을 없애다. (IndexBinder_Destroy)
36. 명함철을 없애다. (BusinessCardBinder_Destroy)
37. 끝내다. (BusinessCardBinder_Destroy)
*/

int main(int argc, char *argv[])
{
	BusinessCardBinder businessCardBinder;
	IndexBinder indexBinder;
	BusinessCard businessCard;
	BusinessCard* (*indexes);
	Index (*indexLinks);
	Long count = 0;
	Long indexLinkCount;
	BusinessCard *index;
	Index *indexLink;
	Long i = 0;
	Long subscript;


	//1. 명함철을 만든다. (BusinessCardBinder_Create, LinkedList_Create
	BusinessCardBinder_Create(&businessCardBinder);

	//2. 색인철을 만든다.(IndexBinder_Create)
	IndexBinder_Create(&indexBinder);

	//	Load(&businessCardBinder);

	
		//3. "홍길동", "회장", "02", "hong@", "박컴", "서울시", "021", "022", "park.com"명함을 만든다.
	strcpy(businessCard.personal.name, "홍길동");
	strcpy(businessCard.personal.position, "회장");
	strcpy(businessCard.personal.telephoneNumber, "02");
	strcpy(businessCard.personal.emailAddress, "hong@");
	strcpy(businessCard.company.name, "박컴");
	strcpy(businessCard.company.address, "서울시");
	strcpy(businessCard.company.telephoneNumber, "021");
	strcpy(businessCard.company.faxNumber, "022");
	strcpy(businessCard.company.url, "park.com");

	//4. 명함철에 넣는다. (BusinessCardBinder_Put, LinkedList_AppendFromTail
	index = BusinessCardBinder_Put(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//5. 색인철에 넣는다. (IndexBinder_Put)
	indexLink = IndexBinder_Put(&indexBinder, index);
	printf("%s \n", indexLink->name);

	
	//6. "김길동", "과장", "031", "kim@", "박컴", "서울시", "021", "022", "park.com"명함을 만든다.
	strcpy(businessCard.personal.name, "김길동");
	strcpy(businessCard.personal.position, "과장");
	strcpy(businessCard.personal.telephoneNumber, "031");
	strcpy(businessCard.personal.emailAddress, "kim@");
	strcpy(businessCard.company.name, "박컴");
	strcpy(businessCard.company.address, "서울시");
	strcpy(businessCard.company.telephoneNumber, "021");
	strcpy(businessCard.company.faxNumber, "022");
	strcpy(businessCard.company.url, "park.com");

	//7. 명함철에 넣는다. (BusinessCardBinder_Put, LinkedList_AppendFromTail
	index = BusinessCardBinder_Put(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//8. 색인철에 넣는다. (IndexBinder_Put)
	indexLink = IndexBinder_Put(&indexBinder, index);
	printf("%s \n", indexLink->name);

	//9. "홍길동", "사원","041", "hong2@","삼성","서울시","02", "02", "samsung.com"명함을 만든다.
	strcpy(businessCard.personal.name, "홍길동");
	strcpy(businessCard.personal.position, "사원");
	strcpy(businessCard.personal.telephoneNumber, "041");
	strcpy(businessCard.personal.emailAddress, "hong2@");
	strcpy(businessCard.company.name, "삼성");
	strcpy(businessCard.company.address, "서울시");
	strcpy(businessCard.company.telephoneNumber, "02");
	strcpy(businessCard.company.faxNumber, "02");
	strcpy(businessCard.company.url, "samsung.com");

	//10. 명함철에 넣는다. (BusinessCardBinder_Put, LinkedList_AppendFromTail
	index = BusinessCardBinder_Put(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//11. 색인철에 넣는다. (IndexBinder_Put)
	indexLink = IndexBinder_Put(&indexBinder, index);
	printf("%s \n", indexLink->name);

	//12. "박길동", "사장","031", "park@","현대","서울시","022", "022", "hyundai.com"명함을 만든다.
	strcpy(businessCard.personal.name, "박길동");
	strcpy(businessCard.personal.position, "사장");
	strcpy(businessCard.personal.telephoneNumber, "031");
	strcpy(businessCard.personal.emailAddress, "park@");
	strcpy(businessCard.company.name, "현대");
	strcpy(businessCard.company.address, "서울시");
	strcpy(businessCard.company.telephoneNumber, "022");
	strcpy(businessCard.company.faxNumber, "022");
	strcpy(businessCard.company.url, "hyundai.com");

	//13. 명함철에 넣는다. (BusinessCardBinder_Put, LinkedList_AppendFromTail
	index = BusinessCardBinder_Put(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//14. 색인철에 넣는다. (IndexBinder_Put)
	indexLink = IndexBinder_Put(&indexBinder, index);
	printf("%s \n", indexLink->name);

	//15. 홍길동을 찾는다.(BusinessCardBinder_Find)
	BusinessCardBinder_Find(&businessCardBinder, "홍길동", &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s %s %s %s %s %s\n", indexes[i]->personal.name, indexes[i]->personal.position, indexes[i]->personal.telephoneNumber, indexes[i]->personal.emailAddress, indexes[i]->company.name, indexes[i]->company.address, indexes[i]->company.telephoneNumber, indexes[i]->company.faxNumber, indexes[i]->company.url);
		i++;
	}
	
	if (indexes != NULL)
	{
		free(indexes);
		indexes = NULL;
	}

	//16. 박컴을 찾는다.(IndexBinder_Find)
	indexLink = IndexBinder_Find(&indexBinder, "박컴");
	i = 0;
	while (i < indexLink->length)
	{
		index = Index_GetAt(indexLink, i);
		printf("%d %s %s %s %s %s %s %s %s %s\n", i + 1, index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
		i++;
	}

	
	//17. 마지막명함으로 이동한다.
	index = BusinessCardBinder_Last(&businessCardBinder);

	//18. 마지막명함을 꺼낸다. (BusinessCardBinder_Draw)
	businessCard = BusinessCardBinder_Draw(&businessCardBinder, index);
	printf("%s %s %s %s %s %s %s %s %s\n", businessCard.personal.name, businessCard.personal.position, businessCard.personal.telephoneNumber, businessCard.personal.emailAddress, businessCard.company.name, businessCard.company.address, businessCard.company.telephoneNumber, businessCard.company.faxNumber, businessCard.company.url);

	//19. 색인철에서 꺼낸다. (IndexBinder_Draw)
	indexLink = IndexBinder_Draw(&indexBinder, index, businessCard.company.name);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}

	
	//20. 명함철에 넣는다. (BusinessCardBinder_Put)
	index = BusinessCardBinder_Put(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//21. 색인철에 넣는다. (IndexBinder_Put)
	indexLink = IndexBinder_Put(&indexBinder, index);
	printf("%s \n", indexLink->name);

	
	//22. 색인철을 정리하다. (IndexBinder_Arrange)
	IndexBinder_Arrange(&indexBinder);

	//23. 색인철 리스트를 만들다. (IndexBinder_MakeList)
	IndexBinder_MakeList(&indexBinder, &indexLinks, &indexLinkCount);
	i = 0;
	while (i < indexLinkCount)
	{
		printf("%d %s\n", i + 1, indexLinks[i].name);
		i++;
	}
	if (indexLinks != NULL)
	{
		free(indexLinks);
		indexLinks = NULL;
	}

	
	//24. 처음명함으로 이동하다. (BusinessCardBinder_First)
	index = BusinessCardBinder_First(&businessCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//25. 색인철에서 확인하다. (IndexBinder_Find, Index_Find)
	indexLink = IndexBinder_Find(&indexBinder, index->company.name);
	subscript = Index_Find(indexLink, index);
	index = Index_GetAt(indexLink, subscript);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	
	//26. 이전명함으로 이동하다. (BusinessCardBinder_Previous)
	index = BusinessCardBinder_Previous(&businessCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);


	//27. 색인철에서 확인하다. (IndexBinder_Find, Index_Find)
	indexLink = IndexBinder_Find(&indexBinder, index->company.name);
	subscript = Index_Find(indexLink, index);
	index = Index_GetAt(indexLink, subscript);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	
	//28. "박길동"을 찾다. (BusinessCardBinder_Find)
	BusinessCardBinder_Find(&businessCardBinder, "박길동", &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s %s %s %s %s %s\n", indexes[i]->personal.name, indexes[i]->personal.position, indexes[i]->personal.telephoneNumber, indexes[i]->personal.emailAddress, indexes[i]->company.name, indexes[i]->company.address, indexes[i]->company.telephoneNumber, indexes[i]->company.faxNumber, indexes[i]->company.url);
		i++;
	}


	//29. 해당위치로 간다. (BusinessCardBinder_Move)
	index = BusinessCardBinder_Move(&businessCardBinder, indexes[0]);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	
	if (indexes != NULL)
	{
		free(indexes);
		indexes = NULL;
	}

	//30. 색인철에서 확인하다. (IndexBinder_Find, Index_Find)
	indexLink = IndexBinder_Find(&indexBinder, index->company.name);
	subscript = Index_Find(indexLink, index);
	index = Index_GetAt(indexLink, subscript);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	
	//31. 마지막명함으로 이동하다. (BusinessCardBinder_Last)
	index = BusinessCardBinder_Last(&businessCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//32. 색인철에서 확인하다. (IndexBinder_Find, Index_Find)
	indexLink = IndexBinder_Find(&indexBinder, index->company.name);
	subscript = Index_Find(indexLink, index);
	index = Index_GetAt(indexLink, subscript);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//33. 다음명함으로 이동하다. (BusinessCardBinder_Next)
	index = BusinessCardBinder_Next(&businessCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//34. 색인철에서 확인하다. (IndexBinder_Find, Index_Find)
	indexLink = IndexBinder_Find(&indexBinder, index->company.name);
	subscript = Index_Find(indexLink, index);
	index = Index_GetAt(indexLink, subscript);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	

	//35. 색인철을 없애다. (IndexBinder_Destroy)
	IndexBinder_Destroy(&indexBinder);

	//36. 명함철을 없애다. (BusinessCardBinder_Destroy)
	BusinessCardBinder_Destroy(&businessCardBinder);

	//37. 끝내다.
	return 0;
}


int CompareNames(void *one, void *other)
{
	return strcmp(((BusinessCard*)one)->personal.name, (char(*))other);
}

int CompareCompanyNames(void *one, void *other)
{
	return strcmp(((BusinessCard*)one)->company.name, (char(*))other);
}

int CompareIndexes(void *one, void *other)
{
	Long ret;
	if (one == other)
	{
		ret = 0;
	}
	else if (one < other)
	{
		ret = -1;
	}
	else
	{
		ret = 1;
	}
	return ret;
}

/*
함수명 : Create
기  능 : 명함철을 만든다.
입  력 : 없음
출  력 : 없음
*/
void BusinessCardBinder_Create(BusinessCardBinder *businessCardBinder)
{
	LinkedList_Create(&businessCardBinder->businessCards);
	businessCardBinder->length = 0;
	businessCardBinder->current = NULL;
}



/*
함수명 : Load
기  능 : 데이터를 적재한다
입  력 : 없음
출  력 : 사용량 
*/

Long BusinessCardBinder_Load(BusinessCardBinder *businessCardBinder) {
	BusinessCard businessCard;
	Node *node;
	Long index;
	Long i;
	int personalFlag;
	int companyFlag;
	FILE *personalFile;
	FILE *companyFile;

	personalFile = fopen("Personals.dat", "rb");
	companyFile = fopen("Companies.dat", "rb");
	if (personalFile != NULL && companyFile != NULL) {
		personalFlag = fread(&index, sizeof(Long), 1, personalFile);
		personalFlag = fread(&businessCard.personal, sizeof(Personal), 1, personalFile);
		while (!feof(personalFile) && personalFlag != 0) {
			i = 1;
			fseek(companyFile, 0L, SEEK_SET);
			companyFlag = fread(&businessCard.company, sizeof(Company), 1, companyFile);
			while (!feof(companyFile) && companyFlag != 0 && i < index) {
				i++;
				companyFlag = fread(&businessCard.company, sizeof(Company), 1, companyFile);
			}
			node = LinkedList_AppendFromTail(&businessCardBinder->businessCards, &businessCard, sizeof(BusinessCard));
			businessCardBinder->current = (BusinessCard*)(node + 1);
			businessCardBinder->length++;
			personalFlag = fread(&index, sizeof(Long), 1, personalFile);
			personalFlag = fread(&businessCard.personal, sizeof(Personal), 1, personalFile);

		}
		fclose(companyFile);
		fclose(personalFile);
	}
	return businessCardBinder->length;
}


/*
함수명 : Put
기  능 : 명함을 넣는다.
입  력 : 명함
출  력 : 위치
*/
BusinessCard* BusinessCardBinder_Put(BusinessCardBinder *businessCardBinder, BusinessCard businessCard)
{
	Node *node;

	node = LinkedList_AppendFromTail(&businessCardBinder->businessCards, &businessCard, sizeof(BusinessCard));
	businessCardBinder->current = (BusinessCard*)(node + 1);

	businessCardBinder->length++;

	return businessCardBinder->current;
}


/*
함수명 : Find
기  능 : 성명을 입력받아 명함을 찾는다.
입  력 : 성명
출  력 : 위치들,개수
*/
void BusinessCardBinder_Find(BusinessCardBinder *businessCardBinder, char(*name), BusinessCard**(*indexes), Long *count)
{
	Node*(*nodes);
	Long i;

	*indexes = (BusinessCard*(*))calloc(businessCardBinder->length, sizeof(BusinessCard*));
	LinkedList_LinearSearchDuplicate(&businessCardBinder->businessCards, name, &nodes, count, sizeof(BusinessCard), CompareNames);

	i = 0;
	while (i < *count)
	{
		(*indexes)[i] = (BusinessCard*)((nodes[i]) + 1);
		i++;
	}
	if (nodes != NULL)
	{
		free(nodes);
		nodes = NULL;
	}
}


/*
함수명 : Draw
기  능 : 명함을 꺼낸다
입  력 : 위치
출  력 : 명함
*/
BusinessCard BusinessCardBinder_Draw(BusinessCardBinder *businessCardBinder, BusinessCard* index)
{
	BusinessCard businessCard;
	Node *node;

	node = LinkedList_LinearSearchUnique(&businessCardBinder->businessCards, index, sizeof(BusinessCard),CompareIndexes);
	LinkedList_GetAt(&businessCardBinder->businessCards, node, &businessCard, sizeof(BusinessCard));
	LinkedList_Delete(&businessCardBinder->businessCards, node);

	businessCardBinder->length--;
	businessCardBinder->current = (BusinessCard*)(businessCardBinder->businessCards.current + 1);

	return businessCard;
}


/*
함수명 : FindByCompanyName
기  능 : 상호를 입력받아 명함을 찾는다
입  력 : 상호
출  력 : 위치
*/
BusinessCard* BusinessCardBinder_FindByCompanyName(BusinessCardBinder *businessCardBinder, char(*companyName))
{
	Node *node;
	BusinessCard *index = NULL;

	node = LinkedList_LinearSearchUnique(&businessCardBinder->businessCards, companyName, sizeof(BusinessCard), CompareCompanyNames);
	if (node != NULL)
	{
		index = (BusinessCard*)(node + 1);
	}

	return index;
}


/*
함수명 : Arrange
기  능 : 명함철을 정리한다
입  력 : 없음
출  력 : 없음
*/

/*
void Arrange(BusinessCardBinder *businessCardBinder)
{
	BusinessCard *compare;
	BusinessCard *previous = NULL;
	Long flag = 1;
	Long i = 1;
	Long j;

	while (i < businessCardBinder->length&&flag != 0)
	{
		businessCardBinder->current = businessCardBinder->first;
		compare = businessCardBinder->current->next;
		j = 1;
		flag = 0;
		while (j <= businessCardBinder->length - i)
		{
			if (strcmp(businessCardBinder->current->personal.name, compare->personal.name) > 0) {
				if (businessCardBinder->current != businessCardBinder->first) {
					previous->next = compare;
				}

				else {
					businessCardBinder->first = compare;
				}
				previous = compare;
				businessCardBinder->current->next = compare->next;
				compare->next = businessCardBinder->current;
				compare = businessCardBinder->current->next;
				flag++;
			}
			else {
				businessCardBinder->current = businessCardBinder->current->next;
				compare = compare->next;
			}
			j++;
		}
		i++;
	}

}
*/


/*
함수명 : First
기  능 : 첫 번째 명함을 찾는다.
입  력 : 없음
출  력 : 위치
*/

BusinessCard* BusinessCardBinder_First(BusinessCardBinder *businessCardBinder)
{
	Node *node;
	node = LinkedList_First(&businessCardBinder->businessCards);
	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}


/*
함수명 : Previous
기  능 : 이전 명함을 찾는다.
입  력 : 없음
출  력 : 위치
*/

BusinessCard* BusinessCardBinder_Previous(BusinessCardBinder *businessCardBinder)
{
	Node *node;
	node = LinkedList_Previous(&businessCardBinder->businessCards);
	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}


/*
함수명 : Next
기  능 : 다음 명함을 찾는다.
입  력 : 없음
출  력 : 위치
*/

BusinessCard* BusinessCardBinder_Next(BusinessCardBinder *businessCardBinder)
{
	Node *node;
	node = LinkedList_Next(&businessCardBinder->businessCards);
	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}


/*
함수명 : Last
기  능 : 마지막 명함을 찾는다.
입  력 : 없음
출  력 : 위치
*/


BusinessCard* BusinessCardBinder_Last(BusinessCardBinder *businessCardBinder)
{
	Node *node;
	node = LinkedList_Last(&businessCardBinder->businessCards);
	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}



/*
함수명 : Move
기  능 : 특정 위치의 명함을 찾는다.
입  력 : 위치
출  력 : 위치
*/


BusinessCard* BusinessCardBinder_Move(BusinessCardBinder *businessCardBinder, BusinessCard* index)
{
	Node *node;
	node = LinkedList_LinearSearchUnique(&businessCardBinder->businessCards, index, sizeof(BusinessCard), CompareIndexes);
	node = LinkedList_Move(&businessCardBinder->businessCards, node);
	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}




/*
함수명 : Save
기  능 : 데이터를 저장한다
입  력 : 없음
출  력 : 사용량
*/

Long BusinessCardBinder_Save(BusinessCardBinder *businessCardBinder) {
	BusinessCard businessCard;
	Company company;
	Node *node;
	Node *previous = NULL;
	Long index;
	Long flag;
	FILE *personalFile = fopen("Personals.dat", "wb");
	FILE *companyFile = fopen("Companies.dat", "wb+");

	if (personalFile != NULL && companyFile != NULL) {
		node = LinkedList_First(&businessCardBinder->businessCards);
		businessCardBinder->current = (BusinessCard*)(node + 1);
		while (node!=previous) {
			LinkedList_GetAt(&businessCardBinder->businessCards, node, &businessCard, sizeof(BusinessCard));
			index = 1;
			fseek(companyFile, 0L, SEEK_SET);

			flag = fread(&company, sizeof(Company), 1, companyFile);
			while (!feof(companyFile) && flag != 0 && strcmp(businessCard.company.name, company.name) != 0) {
				index++;
				flag = fread(&company, sizeof(Company), 1, companyFile);
			}
			if (flag == 0) {
				fwrite(&businessCard.company, sizeof(Company), 1, companyFile);
			}
			fwrite(&index, sizeof(Long), 1, personalFile);
			fwrite(&businessCard.personal, sizeof(Personal), 1, personalFile);

			previous = node;
			node = LinkedList_Next(&businessCardBinder->businessCards);
		}
		fclose(companyFile);
		fclose(personalFile);
	}
	return businessCardBinder->length;
}


/*
함수명 : Destroy
기  능 : 명함철을 없앤다.
입  력 : 없음
출  력 : 없음
*/
void BusinessCardBinder_Destroy(BusinessCardBinder *businessCardBinder)
{
	LinkedList_Destroy(&businessCardBinder->businessCards);
}