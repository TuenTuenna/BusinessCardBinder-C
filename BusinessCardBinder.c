//BusinessCardBinder.c

#define _CRT_SECURE_NO_WARNINGS
#include "BusinessCardBinder.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
main�ó�����
1. ����ö�� �����. (BusinessCardBinder_Create, LinkedList_Create
2. ����ö�� �����.(IndexBinder_Create)
3. "ȫ�浿", "ȸ��","02", "hong@","����","�����","021", "022", "park.com"������ �����.
4. ����ö�� �ִ´�. (BusinessCardBinder_Put, LinkedList_AppendFromTail
5. ����ö�� �ִ´�. (IndexBinder_Put)
6. "��浿", "����","031", "kim@","����","�����","021", "022", "park.com"������ �����.
7. ����ö�� �ִ´�. (BusinessCardBinder_Put, LinkedList_AppendFromTail
8. ����ö�� �ִ´�. (IndexBinder_Put)
9. "ȫ�浿", "���","041", "hong2@","�Ｚ","�����","02", "02", "samsung.com"������ �����.
10. ����ö�� �ִ´�. (BusinessCardBinder_Put, LinkedList_AppendFromTail
11. ����ö�� �ִ´�. (IndexBinder_Put)
12. "�ڱ浿", "����","031", "park@","����","�����","022", "022", "hyundai.com"������ �����.
13. ����ö�� �ִ´�. (BusinessCardBinder_Put, LinkedList_AppendFromTail
14. ����ö�� �ִ´�. (IndexBinder_Put)
15. ȫ�浿�� ã�´�.(BusinessCardBinder_Find)
16. ������ ã�´�.(IndexBinder_Find)
17. �������������� �̵��Ѵ�.
18. ������������ ������. (BusinessCardBinder_Draw)
19. ����ö���� ������. (IndexBinder_Draw)
20. ����ö�� �ִ´�. (BusinessCardBinder_Put)
21. ����ö�� �ִ´�. (IndexBinder_Put)
22. ����ö�� �����ϴ�. (IndexBinder_Arrange)
23. ����ö ����Ʈ�� �����. (IndexBinder_MakeList)
24. ó���������� �̵��ϴ�. (BusinessCardBinder_First)
25. ����ö���� Ȯ���ϴ�. (IndexBinder_Find, Index_Find)
26. ������������ �̵��ϴ�. (BusinessCardBinder_Previous)
27. ����ö���� Ȯ���ϴ�. (IndexBinder_Find, Index_Find)
28. "�ڱ浿"�� ã��. (BusinessCardBinder_Find)
29. �ش���ġ�� ����. (BusinessCardBinder_Move)
30. ����ö���� Ȯ���ϴ�. (IndexBinder_Find, Index_Find)
31. �������������� �̵��ϴ�. (BusinessCardBinder_Last)
32. ����ö���� Ȯ���ϴ�. (IndexBinder_Find, Index_Find)
33. ������������ �̵��ϴ�. (BusinessCardBinder_Next)
34. ����ö���� Ȯ���ϴ�. (IndexBinder_Find, Index_Find)
35. ����ö�� ���ִ�. (IndexBinder_Destroy)
36. ����ö�� ���ִ�. (BusinessCardBinder_Destroy)
37. ������. (BusinessCardBinder_Destroy)
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


	//1. ����ö�� �����. (BusinessCardBinder_Create, LinkedList_Create
	BusinessCardBinder_Create(&businessCardBinder);

	//2. ����ö�� �����.(IndexBinder_Create)
	IndexBinder_Create(&indexBinder);

	//	Load(&businessCardBinder);

	
		//3. "ȫ�浿", "ȸ��", "02", "hong@", "����", "�����", "021", "022", "park.com"������ �����.
	strcpy(businessCard.personal.name, "ȫ�浿");
	strcpy(businessCard.personal.position, "ȸ��");
	strcpy(businessCard.personal.telephoneNumber, "02");
	strcpy(businessCard.personal.emailAddress, "hong@");
	strcpy(businessCard.company.name, "����");
	strcpy(businessCard.company.address, "�����");
	strcpy(businessCard.company.telephoneNumber, "021");
	strcpy(businessCard.company.faxNumber, "022");
	strcpy(businessCard.company.url, "park.com");

	//4. ����ö�� �ִ´�. (BusinessCardBinder_Put, LinkedList_AppendFromTail
	index = BusinessCardBinder_Put(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//5. ����ö�� �ִ´�. (IndexBinder_Put)
	indexLink = IndexBinder_Put(&indexBinder, index);
	printf("%s \n", indexLink->name);

	
	//6. "��浿", "����", "031", "kim@", "����", "�����", "021", "022", "park.com"������ �����.
	strcpy(businessCard.personal.name, "��浿");
	strcpy(businessCard.personal.position, "����");
	strcpy(businessCard.personal.telephoneNumber, "031");
	strcpy(businessCard.personal.emailAddress, "kim@");
	strcpy(businessCard.company.name, "����");
	strcpy(businessCard.company.address, "�����");
	strcpy(businessCard.company.telephoneNumber, "021");
	strcpy(businessCard.company.faxNumber, "022");
	strcpy(businessCard.company.url, "park.com");

	//7. ����ö�� �ִ´�. (BusinessCardBinder_Put, LinkedList_AppendFromTail
	index = BusinessCardBinder_Put(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//8. ����ö�� �ִ´�. (IndexBinder_Put)
	indexLink = IndexBinder_Put(&indexBinder, index);
	printf("%s \n", indexLink->name);

	//9. "ȫ�浿", "���","041", "hong2@","�Ｚ","�����","02", "02", "samsung.com"������ �����.
	strcpy(businessCard.personal.name, "ȫ�浿");
	strcpy(businessCard.personal.position, "���");
	strcpy(businessCard.personal.telephoneNumber, "041");
	strcpy(businessCard.personal.emailAddress, "hong2@");
	strcpy(businessCard.company.name, "�Ｚ");
	strcpy(businessCard.company.address, "�����");
	strcpy(businessCard.company.telephoneNumber, "02");
	strcpy(businessCard.company.faxNumber, "02");
	strcpy(businessCard.company.url, "samsung.com");

	//10. ����ö�� �ִ´�. (BusinessCardBinder_Put, LinkedList_AppendFromTail
	index = BusinessCardBinder_Put(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//11. ����ö�� �ִ´�. (IndexBinder_Put)
	indexLink = IndexBinder_Put(&indexBinder, index);
	printf("%s \n", indexLink->name);

	//12. "�ڱ浿", "����","031", "park@","����","�����","022", "022", "hyundai.com"������ �����.
	strcpy(businessCard.personal.name, "�ڱ浿");
	strcpy(businessCard.personal.position, "����");
	strcpy(businessCard.personal.telephoneNumber, "031");
	strcpy(businessCard.personal.emailAddress, "park@");
	strcpy(businessCard.company.name, "����");
	strcpy(businessCard.company.address, "�����");
	strcpy(businessCard.company.telephoneNumber, "022");
	strcpy(businessCard.company.faxNumber, "022");
	strcpy(businessCard.company.url, "hyundai.com");

	//13. ����ö�� �ִ´�. (BusinessCardBinder_Put, LinkedList_AppendFromTail
	index = BusinessCardBinder_Put(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//14. ����ö�� �ִ´�. (IndexBinder_Put)
	indexLink = IndexBinder_Put(&indexBinder, index);
	printf("%s \n", indexLink->name);

	//15. ȫ�浿�� ã�´�.(BusinessCardBinder_Find)
	BusinessCardBinder_Find(&businessCardBinder, "ȫ�浿", &indexes, &count);
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

	//16. ������ ã�´�.(IndexBinder_Find)
	indexLink = IndexBinder_Find(&indexBinder, "����");
	i = 0;
	while (i < indexLink->length)
	{
		index = Index_GetAt(indexLink, i);
		printf("%d %s %s %s %s %s %s %s %s %s\n", i + 1, index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
		i++;
	}

	
	//17. �������������� �̵��Ѵ�.
	index = BusinessCardBinder_Last(&businessCardBinder);

	//18. ������������ ������. (BusinessCardBinder_Draw)
	businessCard = BusinessCardBinder_Draw(&businessCardBinder, index);
	printf("%s %s %s %s %s %s %s %s %s\n", businessCard.personal.name, businessCard.personal.position, businessCard.personal.telephoneNumber, businessCard.personal.emailAddress, businessCard.company.name, businessCard.company.address, businessCard.company.telephoneNumber, businessCard.company.faxNumber, businessCard.company.url);

	//19. ����ö���� ������. (IndexBinder_Draw)
	indexLink = IndexBinder_Draw(&indexBinder, index, businessCard.company.name);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}

	
	//20. ����ö�� �ִ´�. (BusinessCardBinder_Put)
	index = BusinessCardBinder_Put(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//21. ����ö�� �ִ´�. (IndexBinder_Put)
	indexLink = IndexBinder_Put(&indexBinder, index);
	printf("%s \n", indexLink->name);

	
	//22. ����ö�� �����ϴ�. (IndexBinder_Arrange)
	IndexBinder_Arrange(&indexBinder);

	//23. ����ö ����Ʈ�� �����. (IndexBinder_MakeList)
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

	
	//24. ó���������� �̵��ϴ�. (BusinessCardBinder_First)
	index = BusinessCardBinder_First(&businessCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//25. ����ö���� Ȯ���ϴ�. (IndexBinder_Find, Index_Find)
	indexLink = IndexBinder_Find(&indexBinder, index->company.name);
	subscript = Index_Find(indexLink, index);
	index = Index_GetAt(indexLink, subscript);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	
	//26. ������������ �̵��ϴ�. (BusinessCardBinder_Previous)
	index = BusinessCardBinder_Previous(&businessCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);


	//27. ����ö���� Ȯ���ϴ�. (IndexBinder_Find, Index_Find)
	indexLink = IndexBinder_Find(&indexBinder, index->company.name);
	subscript = Index_Find(indexLink, index);
	index = Index_GetAt(indexLink, subscript);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	
	//28. "�ڱ浿"�� ã��. (BusinessCardBinder_Find)
	BusinessCardBinder_Find(&businessCardBinder, "�ڱ浿", &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s %s %s %s %s %s\n", indexes[i]->personal.name, indexes[i]->personal.position, indexes[i]->personal.telephoneNumber, indexes[i]->personal.emailAddress, indexes[i]->company.name, indexes[i]->company.address, indexes[i]->company.telephoneNumber, indexes[i]->company.faxNumber, indexes[i]->company.url);
		i++;
	}


	//29. �ش���ġ�� ����. (BusinessCardBinder_Move)
	index = BusinessCardBinder_Move(&businessCardBinder, indexes[0]);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	
	if (indexes != NULL)
	{
		free(indexes);
		indexes = NULL;
	}

	//30. ����ö���� Ȯ���ϴ�. (IndexBinder_Find, Index_Find)
	indexLink = IndexBinder_Find(&indexBinder, index->company.name);
	subscript = Index_Find(indexLink, index);
	index = Index_GetAt(indexLink, subscript);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	
	//31. �������������� �̵��ϴ�. (BusinessCardBinder_Last)
	index = BusinessCardBinder_Last(&businessCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//32. ����ö���� Ȯ���ϴ�. (IndexBinder_Find, Index_Find)
	indexLink = IndexBinder_Find(&indexBinder, index->company.name);
	subscript = Index_Find(indexLink, index);
	index = Index_GetAt(indexLink, subscript);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//33. ������������ �̵��ϴ�. (BusinessCardBinder_Next)
	index = BusinessCardBinder_Next(&businessCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//34. ����ö���� Ȯ���ϴ�. (IndexBinder_Find, Index_Find)
	indexLink = IndexBinder_Find(&indexBinder, index->company.name);
	subscript = Index_Find(indexLink, index);
	index = Index_GetAt(indexLink, subscript);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	

	//35. ����ö�� ���ִ�. (IndexBinder_Destroy)
	IndexBinder_Destroy(&indexBinder);

	//36. ����ö�� ���ִ�. (BusinessCardBinder_Destroy)
	BusinessCardBinder_Destroy(&businessCardBinder);

	//37. ������.
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
�Լ��� : Create
��  �� : ����ö�� �����.
��  �� : ����
��  �� : ����
*/
void BusinessCardBinder_Create(BusinessCardBinder *businessCardBinder)
{
	LinkedList_Create(&businessCardBinder->businessCards);
	businessCardBinder->length = 0;
	businessCardBinder->current = NULL;
}



/*
�Լ��� : Load
��  �� : �����͸� �����Ѵ�
��  �� : ����
��  �� : ��뷮 
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
�Լ��� : Put
��  �� : ������ �ִ´�.
��  �� : ����
��  �� : ��ġ
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
�Լ��� : Find
��  �� : ������ �Է¹޾� ������ ã�´�.
��  �� : ����
��  �� : ��ġ��,����
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
�Լ��� : Draw
��  �� : ������ ������
��  �� : ��ġ
��  �� : ����
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
�Լ��� : FindByCompanyName
��  �� : ��ȣ�� �Է¹޾� ������ ã�´�
��  �� : ��ȣ
��  �� : ��ġ
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
�Լ��� : Arrange
��  �� : ����ö�� �����Ѵ�
��  �� : ����
��  �� : ����
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
�Լ��� : First
��  �� : ù ��° ������ ã�´�.
��  �� : ����
��  �� : ��ġ
*/

BusinessCard* BusinessCardBinder_First(BusinessCardBinder *businessCardBinder)
{
	Node *node;
	node = LinkedList_First(&businessCardBinder->businessCards);
	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}


/*
�Լ��� : Previous
��  �� : ���� ������ ã�´�.
��  �� : ����
��  �� : ��ġ
*/

BusinessCard* BusinessCardBinder_Previous(BusinessCardBinder *businessCardBinder)
{
	Node *node;
	node = LinkedList_Previous(&businessCardBinder->businessCards);
	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}


/*
�Լ��� : Next
��  �� : ���� ������ ã�´�.
��  �� : ����
��  �� : ��ġ
*/

BusinessCard* BusinessCardBinder_Next(BusinessCardBinder *businessCardBinder)
{
	Node *node;
	node = LinkedList_Next(&businessCardBinder->businessCards);
	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}


/*
�Լ��� : Last
��  �� : ������ ������ ã�´�.
��  �� : ����
��  �� : ��ġ
*/


BusinessCard* BusinessCardBinder_Last(BusinessCardBinder *businessCardBinder)
{
	Node *node;
	node = LinkedList_Last(&businessCardBinder->businessCards);
	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}



/*
�Լ��� : Move
��  �� : Ư�� ��ġ�� ������ ã�´�.
��  �� : ��ġ
��  �� : ��ġ
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
�Լ��� : Save
��  �� : �����͸� �����Ѵ�
��  �� : ����
��  �� : ��뷮
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
�Լ��� : Destroy
��  �� : ����ö�� ���ش�.
��  �� : ����
��  �� : ����
*/
void BusinessCardBinder_Destroy(BusinessCardBinder *businessCardBinder)
{
	LinkedList_Destroy(&businessCardBinder->businessCards);
}