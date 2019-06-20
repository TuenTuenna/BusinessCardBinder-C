//BusinessCardBinder.h

#ifndef _BUSINESSCARDBINDER_H
#define _BUSINESSCARDBINDER_H
#include "LinkedList.h"
#include "IndexBinder.h"
#include "Index.h"


//자료형선언

typedef signed long int Long;
typedef struct _personal {
	char name[11];
	char position[32];
	char telephoneNumber[12];
	char emailAddress[64];
} Personal;

typedef struct _company {
	char name[32];
	char address[64];
	char telephoneNumber[12];
	char faxNumber[12];
	char url[64];
} Company;

typedef struct _businessCard BusinessCard;
typedef struct _businessCard {
	Personal personal;
	Company company;
} BusinessCard;

typedef struct _businessCardBinder {
	LinkedList businessCards;
	Long length;
	BusinessCard* current;
} BusinessCardBinder;

//함수선언
void BusinessCardBinder_Create(BusinessCardBinder *businessCardBinder); 
Long BusinessCardBinder_Load(BusinessCardBinder *businessCardBinder);
BusinessCard* BusinessCardBinder_Put(BusinessCardBinder *businessCardBinder, BusinessCard businessCard);
void BusinessCardBinder_Find(BusinessCardBinder *businessCardBinder, char(*name), BusinessCard**(*indexes), Long *count);
BusinessCard BusinessCardBinder_Draw(BusinessCardBinder *businessCardBinder, BusinessCard* index);
BusinessCard* BusinessCardBinder_FindByCompanyName(BusinessCardBinder *businessCardBinder, char(*companyName));
//void Arrange(BusinessCardBinder *businessCardBinder);
BusinessCard* BusinessCardBinder_First(BusinessCardBinder *businessCardBinder);
BusinessCard* BusinessCardBinder_Previous(BusinessCardBinder *businessCardBinder);
BusinessCard* BusinessCardBinder_Next(BusinessCardBinder *businessCardBinder);
BusinessCard* BusinessCardBinder_Last(BusinessCardBinder *businessCardBinder);
BusinessCard* BusinessCardBinder_Move(BusinessCardBinder *businessCardBinder, BusinessCard* index);
int CompareNames(void *one, void *other);
int CompareCompanyNames(void *one, void *other);
int CompareIndexes(void *one, void *other);
Long BusinessCardBinder_Save(BusinessCardBinder *businessCardBinder);
void BusinessCardBinder_Destroy(BusinessCardBinder *businessCardBinder);

#endif //_BUSINESSCARDBINDER_H