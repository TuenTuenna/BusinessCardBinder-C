//Array.c

#include "Array.h"
#include <stdlib.h>
#include <memory.h>
#pragma warning(disable : 4996)

/*
���ϸ�Ī : Array.c
��    �� : ����, ����, ����, ����, Ŭ����, ����, �˻�, ����, �ı��Ѵ�
�� �� �� : ������
�ۼ����� : 2018. 2. 22.  */

/*
�Լ���Ī : Create
��    �� : capacity��ŭ �迭�� �Ҵ��Ѵ�
��    �� : �Ҵ緮
��    �� : ����  */
void Array_Create(Array *array, Long capacity, size_t size) {
	array->front = calloc(capacity, size);
	array->capacity = capacity;
	array->length = 0;
}

/*
�Լ���Ī : Store
��    �� : object�� �ش���ġ�� ���´�
��    �� : index, object
��    �� : index  */
Long Array_Store(Array *array, Long index, void *object, size_t size) {
	memcpy(((char*)array->front) + (index * size), object, size);
	array->length++;

	return index;
}

/*
�Լ���Ī : Insert
��    �� : object�� �ش���ġ�� �߰��Ѵ�
��    �� : index, object
��    �� : index  */
Long Array_Insert(Array *array, Long index, void *object, size_t size) {
	Long i = 0;
	void(*temps);
	temps = calloc(array->capacity + 1, size);
	while (i < index) {
		memcpy(((char*)temps) + (i*size), ((char*)array->front) + (i * size), size);
		i++;
	}
	i = index + 1;
	while (i < array->length + 1) {
		memcpy(((char*)temps) + (i*size), ((char*)array->front) + ((i - 1)*size), size);
		i++;
	}

	if (array->front != NULL) {
		free(array->front);

	}

	array->front = temps;
	array->capacity++;
	memcpy(((char*)array->front) + (index*size), object, size);
	array->length++;

	return index;
}

/*
�Լ���Ī : AppendFromFront
��    �� : object�� �տ� �߰��Ѵ�
��    �� : object
��    �� : index  */
Long Array_AppendFromFront(Array *array, void *object, size_t size) {
	Long index = 0;
	Long i = 0;
	Long j = 1;
	void(*temps);

	temps = calloc(array->capacity + 1, size);

	while (i < array->length) {
		memcpy(((char*)temps) + (j*size), ((char*)array->front) + (i*size), size);
		j++;
		i++;
	}

	if (array->front != NULL) {
		free(array->front);

	}

	array->front = temps;
	array->capacity++;
	memcpy(((char*)array->front) + (index*size), object, size);
	array->length++;

	return index;
}

/*
�Լ���Ī : AppendFromRear
��    �� : object�� �ڿ� �߰��Ѵ�
��    �� : object
��    �� : index  */
Long Array_AppendFromRear(Array *array, void *object, size_t size) {
	Long index;
	Long i = 0;
	void(*temps);
	temps = calloc(array->capacity + 1, size);
	while (i < array->length) {
		memcpy(((char*)temps) + (i*size), ((char*)array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	array->front = temps;
	array->capacity++;
	index = array->capacity - 1;
	memcpy(((char*)array->front) + (index*size), object, size);
	array->length++;

	return index;
}

/*
�Լ���Ī : Delete
��    �� : �ش���ġ�� object�� �����
��    �� : object
��    �� : index  */
Long Array_Delete(Array *array, Long index, size_t size) {
	void(*temps) = 0;
	Long i = 0;
	Long j = 0;

if (array->capacity > 1) {
	temps = calloc(array->capacity - 1, size);
}
while (i < index) {
	memcpy(((char*)temps) + (j*size), ((char*)array->front) + (i*size), size);
	j++;
	i++;
}
i = index + 1;
while (i < array->length) {
	memcpy(((char*)temps) + (j*size), ((char*)array->front) + (i*size), size);
	j++;
	i++;
}
if (array->front != NULL) {
	free(array->front);
	array->front = NULL;
}
if (array->capacity > 1) {
	array->front = temps;
}
array->capacity--;
array->length--;
index = -1;

return index;
}

/*
�Լ���Ī : DeleteFromFront
��    �� : �տ� �ִ� object�� �����
��    �� :
��    �� : index  */
Long Array_DeleteFromFront(Array *array, size_t size) {
	void(*temp) = 0;
	Long index = -1;
	Long i = 1;
	Long j = 0;

	if (array->capacity > 1) {
		temp = calloc(array->capacity - 1, size);
	}
	while (i < array->length) {
		memcpy(((char *)temp) + (j*size), ((char*)array->front) + (i*size), size);
		j++;
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = temp;
	}
	array->capacity--;
	array->length--;

	return index;
}

/*
�Լ���Ī : DeleteFromRear
��    �� : �ڿ� �ִ� object�� �����
��    �� :
��    �� : index  */
Long Array_DeleteFromRear(Array *array, size_t size) {
	void(*temps) = 0;
	Long index;
	Long i = 0;

	if (array->capacity > 1) {
		temps = calloc(array->capacity - 1, size);
	}
	while (i < array->length - 1) {
		memcpy(((char*)temps) + (i*size), ((char*)array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = temps;
	}
	array->capacity--;
	array->length--;
	index = -1;

	return index;
}

/*
�Լ���Ī : Modify
��    �� : object�� �����Ѵ�
��    �� : index, object
��    �� : index  */
Long Array_Modify(Array *array, Long index, void *object, size_t size) {
	memcpy(((char*)array->front) + (index*size), object, size);

	return index;
}

/*
�Լ���Ī : Clear
��    �� : ǥ�� �����
��    �� : object
��    �� : index  */
void Array_Clear(Array *array) {
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->capacity = 0;
	array->length = 0;
}

/*
�Լ���Ī : LinearSearchUnique
��    �� : �����˻��Ѵ�
��    �� : key
��    �� : index  */
Long Array_LinearSearchUnique(Array *array, void *key, size_t size, int(*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;

	while (i < array->length && compare(((char*)array->front) + (i*size), key) != 0) {
		i++;
	}
	if (i < array->length) {
		index = i;
	}

	return index;
}

/*
�Լ���Ī : LinearSearchDuplicate
��    �� : �����˻��Ѵ�
��    �� : ����
��    �� : ����  */
void Array_LinearSearchDuplicate(Array *array, void *key, size_t size, Long *(*indexes), Long *count, Long(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;

	*count = 0;
	*indexes = (Long(*)) calloc(array->capacity, sizeof(Long));
	while (i < array->length) {
		if (compare(((char*)array->front) + (i*size), key) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}


/*
�Լ���Ī : BinarySearchUnique
��    �� : �����˻��Ѵ�
��    �� : key
��    �� : index  */
Long Array_BinarySearchUnique(Array *array, void *key, size_t size, Long(*compare)(void*, void*)) {
	Long index = -1;
	Long left = 0;
	Long right;
	Long middle;

	right = array->length - 1;
	middle = (left + right) / 2;
	while (left <= right && compare(((char*)array->front) + (middle*size), key) != 0) {
		if (compare(((char*)array->front) + (middle*size), key) < 0) {
			left = middle + 1;
		}
		else {
			right = middle - 1;
		}
		middle = (left + right) / 2;
	}
	if (left <= right) {
		index = middle;
	}
	return index;
}

/*
�Լ���Ī : BinarySearchDuplicate
��    �� : �����˻��Ѵ�
��    �� : key
��    �� : indexes, count  */
void Array_BinarySearchDuplicate(Array *array, void *key, size_t size, Long *(*indexes), Long *count, Long(*compare)(void*, void*)) {
	Long left = 0;
	Long right;
	Long middle;
	Long i;
	Long j;
	Long k = 0;

	*count = 0;

	right = array->length - 1;
	middle = (left + right) / 2;
	while (left <= right && compare(((char*)array->front) + (middle*size), key) != 0) {
		if (compare(((char*)array->front) + (middle*size), key) < 0) {
			left = middle + 1;
		}
		else {
			right = middle - 1;
		}
		middle = (left + right) / 2;
	}
	if (left <= right) {
		i = middle;
		while (i >= 0 && compare(((char*)array->front) + (i*size), key) == 0) {
			i--;
		}
		j = i + 1;
		while (j < array->length&&compare(((char*)array->front) + (j*size), key) == 0) {
			(*count)++;
			j++;
		}
		*indexes = (Long(*))calloc(*count, sizeof(Long));
		middle = i + 1;
		while (k < *count) {
			(*indexes)[k] = middle;
			middle++;
			k++;
		}
	}
}

/*
�Լ���Ī : SelectionSort
��    �� : ���������Ѵ�
��    �� : ����
��    �� : ����  */
void Array_SelectionSort(Array *array, size_t size, Long(*compare)(void*, void*)) {
	Long i = 0;
	Long j;
	void *temp;

	temp = malloc(size);
	while (i < array->length - 1) {
		j = i + 1;
		while (j < array->length) {
			if (compare(((char *)array->front) + (i*size), ((char*)array->front) + (j*size)) > 0) {
				memcpy(temp, ((char*)array->front) + (i*size), size);
				memcpy(((char*)array->front) + (i*size), ((char*)array->front) + (j*size), size);
				memcpy(((char*)array->front) + (j*size), temp, size);
			}
			j++;
		}
		i++;
	}
	if (temp != NULL) {
		free(temp);
	}
}

/*
�Լ���Ī : BubbleSort
��    �� : ���������Ѵ�
��    �� : ����
��    �� : ����  */
void Array_BubbleSort(Array *array, size_t size, Long(*compare)(void*, void*)) {
	void *temp;
	Long flag = 1;
	Long i = 1;
	Long j;

	temp = malloc(size);
	while (flag > 0 && i <= array->length - 1) {
		flag = 0;
		j = 0;
		while (j < array->length - i) {
			if (compare(((char*)array->front) + (j*size), ((char*)array->front) + ((j + 1)*size)) > 0) {
				memcpy(temp, ((char*)array->front) + (j*size), size);
				memcpy(((char*)array->front) + (j*size), ((char*)array->front) + ((j + 1)*size), size);
				memcpy(((char*)array->front) + ((j + 1)*size), temp, size);

				flag++;
			}
			j++;
		}
		i++;
	}
	if(temp!=NULL){
		free(temp);
	}
}

/*
�Լ���Ī : InsertSort
��    �� : ���������Ѵ�
��    �� : ����
��    �� : ����  */
void Array_InsertSort(Array *array, size_t size, Long(*compare)(void*, void*)) {
	void *temp;
	Long i = 1;
	Long j;

	temp = malloc(size);
	while (i < array->length) {
		memcpy(temp, ((char*)array->front) + (i*size), size);
		j = i - 1;

		while (j >= 0 && compare(((char*)array->front) + (j*size), temp) > 0) {
			memcpy(((char*)array->front) + ((j + 1)*size), ((char*)array->front) + (j*size), size);
			j--;
		}
		memcpy(((char*)array->front) + ((j + 1)*size), temp, size);
		i++;
	}
	if (temp != NULL) {
		free(temp);
	}
}
/*
�Լ���Ī : MergeSort
��    �� : �ι迭�� ���������Ѵ�.
��    �� : ����	
��    �� : ����  */
void Array_MergeSort(Array *array, Array *one, Array *other, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;

	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->front = calloc(one->length + other->length, size);
	array->capacity = one->length + other->length;
	while (i < one->length && j < other->length) {
		if (compare(((char*)one->front) + (i*size), ((char *)other->front) + (j*size)) < 0) {
			memcpy(((char*)array->front) + (k*size), ((char*)one->front) + (i*size), size);
			k++;
			i++;
		}
		else {
			memcpy(((char*)array->front) + (k*size), ((char*)other->front) + (j*size), size);
			k++;
			j++;
		}
	}
	while (j < other->length) {
		memcpy(((char*)array->front) + (k*size), ((char*)other->front) + (j*size), size);
		k++;
		j++;
	}
	while (i < one->length) {
		memcpy(((char*)array->front) + (k*size), ((char*)one->front) + (i*size), size);
		k++;
		i++;
	}
	array->length = one->length + other->length;
}

/*
�Լ���Ī : Destroy
��    �� : ǥ�� ������
��    �� : ����
��    �� : ����  */
void Array_Destroy(Array *array) {
	if (array->front != NULL) {
		free(array->front);
	}
}

/*
�Լ���Ī : GetAt
��    �� : �ι迭�� ���������Ѵ�.
��    �� : ����
��    �� : ����  */
void Array_GetAt(Array *array, Long index, void *object, size_t size) {
	memcpy(object, ((char*)array->front) + (index*size), size);
}