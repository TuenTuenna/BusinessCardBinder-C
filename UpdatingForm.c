//UpdatingForm.c
#include"BusinessCardBinder.h"
#include "UpdatingForm.h"
#include "PuttingForm.h"
#include "FindingForm.h"
#include "DrawingForm.h"
#include "resource.h"
#include <stdlib.h>
#include<string.h>
#include <commctrl.h>//CVM

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_UPDATINGFORM), NULL, UpdatingFormProc);
	return response;
}

BOOL CALLBACK UpdatingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG:
		ret = UpdatingForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = UpdatingForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_NOTIFY:
		ret = UpdatingForm_OnNotify(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = UpdatingForm_OnClose(hWnd, wParam, lParam);
		break;
	default: ret = FALSE;
		break;
	}
	return ret;
}

BOOL UpdatingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_PUT:
		ret = UpdatingForm_OnPutButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIND:
		ret = UpdatingForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_DRAW:
		ret = UpdatingForm_OnDrawButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_ARRANGE:
		ret = UpdatingForm_OnArrangeButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIRST:
		ret = UpdatingForm_OnFirstButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_PREVIOUS:
		ret = UpdatingForm_OnPreviousButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_NEXT:
		ret = UpdatingForm_OnNextButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_LAST:
		ret = UpdatingForm_OnLastButtonClicked(hWnd, wParam, lParam);
		break;
	default: ret = FALSE;
		break;
	}
	return ret;
}

/* (WPARAM)
TVGN_CARET(현재위치)
TVGN_NEXT(다음위치)
TVGN_PREVIOUS(이전위치)
TVGN_ROOT(뿌리위치)
TVGN_PARENT(부모위치)
TVGN_CHILD(첫번째 자식위치)
*/

//1.윈도우가 생성될때
BOOL UpdatingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	BusinessCard *index;
	Long i = 0;
	Long j = 0;
	Long count = 0;
	IndexBinder *indexBinder;
	TVINSERTSTRUCT tInsert = { 0, };
	HTREEITEM root;
	HTREEITEM tParent;
	HTREEITEM tChild;
	Index *indexLink;
	Index(*indexLinks);
	Long subscript;
	TCHAR comparison[64];
	BusinessCard *previous = NULL;
	TVITEM item = { 0, };

	//1.1 명함철을 만든다.
	businessCardBinder = (BusinessCardBinder*)malloc(sizeof(BusinessCardBinder));
	BusinessCardBinder_Create(businessCardBinder);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)businessCardBinder);

	//1.2 색인철을 만든다.
	indexBinder = (IndexBinder*)malloc(sizeof(IndexBinder));
	IndexBinder_Create(indexBinder);
	SetProp(hWnd, "indexBinder", (HANDLE)indexBinder);

	//1.3 TreeControl에 회사들 노드를 만든다.
	tInsert.item.mask = TVIF_TEXT;

	tInsert.hParent = NULL;
	tInsert.hInsertAfter = TVI_ROOT;
	tInsert.item.pszText = "회사들";
	tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
	
	//1.4 명함철에 명함들을 적재한다
	count = BusinessCardBinder_Load(businessCardBinder);

	//1.5 명함철의 개수만큼 색인철에 끼운다.
	if (count > 0) {
		index = BusinessCardBinder_First(businessCardBinder);
	}
	else {
		index = NULL;
	}

	while (index!=previous) {
		IndexBinder_Put(indexBinder, index);
		previous = index;
		index = BusinessCardBinder_Next(businessCardBinder);
	}

	//1.6 색인 리스트를 만든다.
	count = 0;
	IndexBinder_MakeList(indexBinder, &indexLinks, &count);

	//1.7 색인 개수만큼 반복한다.
	i = 0;
	while (i < count) {
		//1.7.1 해당 색인의 상호노드를 회사들 노드의 자식노드로 만든다.
		tInsert.hParent = tParent;
		tInsert.hInsertAfter = TVI_LAST;
		tInsert.item.pszText = indexLinks[i].name;
		tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
		//1.7.2 해당 색인의 사용량 만큼 반복한다.
		j = 0;
		while (j < indexLinks[i].length) {
			//1.7.2.1 성명노드를 상호노드의 자식노드로 만든다.
			tInsert.hParent = tChild;
			tInsert.hInsertAfter = TVI_LAST;
			index = Index_GetAt(indexLinks + i, j);
			tInsert.item.pszText = index->personal.name;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
			j++;
		}
		i++;
	}
	if (count > 0) {
		//1.8 명함철에서 맨처음 명함으로 이동한다.
		index = BusinessCardBinder_First(businessCardBinder);

		//1.9 맨처음 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);

		//1.10 색인철에서 현재 명함의 색인을 찾는다.
		indexLink = IndexBinder_Find(indexBinder, index->company.name);

		//1.11 색인에서 현재 명함의 위치를 찾는다.
		subscript = Index_Find(indexLink, index);

		//1.12 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
		root = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)NULL);
		tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)root);

		item.mask = TVIF_TEXT;
		item.cchTextMax = 64;
		item.pszText = comparison;
		item.hItem = tParent;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		while (tParent != NULL && strcmp(comparison, indexLink->name) != 0) {
			tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tParent);
			item.hItem = tParent;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		}

		//1.13 상호노드에서 찾은 위치번째의 자식노드를 이동한다.
		tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		i = 0;
		while (i < subscript) {
			tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
			i++;
		}
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);
		//1.14 마크한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)tChild);
	}
	if (indexLinks != NULL) {
		free(indexLinks);
		indexLinks = NULL;
	}
	
	return TRUE;
}

//2.넣기버튼을 클릭했을때
BOOL UpdatingForm_OnPutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 넣기윈도우가 생성된다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_PUTTINGFORM), NULL, PuttingFormProc);
	}
	return TRUE;
}

//3.찾기버튼을 클릭했을때
BOOL UpdatingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//3.1 찾기윈도우가 생성된다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}
	return TRUE;
}

//4.꺼내보기버튼을 클릭했을때
BOOL UpdatingForm_OnDrawButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//4.1꺼내보기 윈도우가 생성된다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DRAWINGFORM), NULL, DrawingFormProc);
	}
	return TRUE;
}

//5.정리하기버튼을 클릭했을때
BOOL UpdatingForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	BusinessCard *index;
	IndexBinder *indexBinder;
	Index *indexLink;
	Index(*indexLinks);
	Long count;
	TVINSERTSTRUCT tInsert = { 0, };
	TVITEM item = { 0, };
	HTREEITEM root;
	HTREEITEM tParent;
	HTREEITEM tChild;
	Long i;
	Long j;
	Long subscript;
	TCHAR comparison[64];

	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexBinder = (IndexBinder*)GetProp(hWnd, "indexBinder");

		//5.1 색인철에서 정리한다.
		IndexBinder_Arrange(indexBinder);

		//5.2 색인 리스트를 만든다.
		count = 0;
		IndexBinder_MakeList(indexBinder, &indexLinks, &count);

		//5.3 TreeControl에 모든 항목을 버린다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_DELETEITEM, (WPARAM)0, (LPARAM)NULL);

		//5.4 TreeControl에 회사들 노드를 만든다.
		tInsert.item.mask = TVIF_TEXT;
		tInsert.hParent = NULL;
		tInsert.hInsertAfter = TVI_ROOT;
		tInsert.item.pszText = "회사들";
		root = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);

		//5.5 색인 개수만큼 반복한다.
		i = 0;
		while (i < count) {
			//5.5.1 해당 색인의 상호노드를 회사들 노드의 자식노드로 만든다.
			tInsert.hParent = root;
			tInsert.hInsertAfter = TVI_LAST;
			tInsert.item.pszText = indexLinks[i].name;
			tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
			//5.5.2 해당 색인의 사용량 만큼 반복한다.
			j = 0;
			while (j < indexLinks[i].length) {
				//5.5.2.1 성명노드를 상호노드의 자식노드로 만든다.
				tInsert.hParent = tParent;
				tInsert.hInsertAfter = TVI_LAST;
				index = Index_GetAt(indexLinks + i, j);
				tInsert.item.pszText = index->personal.name;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
				j++;
			}
			i++;
		}
		if (count > 0) {
			//5.6 명함철에서 맨처음 명함으로 이동한다.
			index = BusinessCardBinder_First(businessCardBinder);

			//5.7 맨처음 명함을 출력한다.
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);

			//5.8 색인철에서 현재 명함의 색인을 찾는다.
			indexLink = IndexBinder_Find(indexBinder, index->company.name);

			//5.9 색인에서 현재 명함의 위치를 찾는다.
			subscript = Index_Find(indexLink, index);

			//5.10 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
			root = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)NULL);
			tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)root);

			item.mask = TVIF_TEXT;
			item.cchTextMax = 64;
			item.pszText = comparison;
			item.hItem = tParent;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
			while (tParent != NULL && strcmp(comparison, indexLink->name) != 0) {
				tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tParent);
				item.hItem = tParent;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
			}

			//5.11 상호노드에서 찾은 위치번째의 자식노드를 이동한다.
			tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
			i = 0;
			while (i < subscript) {
				tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
				i++;
			}

			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);

			//5.12 마크한다.
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)tChild);
		}
		if (indexLinks != NULL) {
			free(indexLinks);
			indexLinks = NULL;
		}
	}
	return TRUE;
}

//6. 맨처음버튼을 클릭했을때
BOOL UpdatingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	BusinessCard* first;
	IndexBinder *indexBinder;
	HTREEITEM root;
	HTREEITEM tParent;
	HTREEITEM tChild;
	TVITEM item = { 0, };
	Index *indexLink;
	Long subscript;
	TCHAR comparison[64];
	Long i;

	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexBinder = (IndexBinder*)GetProp(hWnd, "indexBinder");

		//6.1 명함철에서 맨처음명함으로 이동하다.
		first = BusinessCardBinder_First(businessCardBinder);

		//6.2 맨처음명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)first->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)first->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)first->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)first->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)first->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)first->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)first->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)first->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)first->company.url);

		//6.3 색인철에서 현재명함의 색인을 찾는다.
		indexLink = IndexBinder_Find(indexBinder, first->company.name);

		//6.4 색인에서 현재 명함의 위치를 찾는다.
		subscript = Index_Find(indexLink, first);

		//6.5 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
		root = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)NULL);
		tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)root);
		item.mask = TVIF_TEXT;
		item.cchTextMax = 64;
		item.pszText = comparison;
		item.hItem = tParent;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		while (tParent != NULL && strcmp(comparison, indexLink->name) != 0) {
			tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tParent);
			item.hItem = tParent;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		}

		//6.6 상호노드에서 찾은 위치번째의 자식노드를 이동한다.
		tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		i = 0;
		while (i < subscript) {
			tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
			i++;
		}

		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);
		//6.7 마크한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)tChild);
	}
	return TRUE;
}

//7. 이전버튼을 클릭했을때
BOOL UpdatingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	BusinessCard* previous;
	IndexBinder *indexBinder;
	HTREEITEM root;
	HTREEITEM tParent;
	HTREEITEM tChild;
	TVITEM item = { 0, };
	Index *indexLink;
	Long subscript;
	TCHAR comparison[64];
	Long i;

	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexBinder = (IndexBinder*)GetProp(hWnd, "indexBinder");

		//7.1 명함철에서 이전명함으로 이동하다.
		previous = BusinessCardBinder_Previous(businessCardBinder);

		//7.2 이전명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)previous->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)previous->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)previous->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)previous->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)previous->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)previous->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)previous->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)previous->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)previous->company.url);

		//7.3 색인철에서 현재명함의 색인을 찾는다.
		indexLink = IndexBinder_Find(indexBinder, previous->company.name);

		//7.4 색인에서 현재 명함의 위치를 찾는다.
		subscript = Index_Find(indexLink, previous);

		//7.5 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
		root= (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)NULL);
		tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)root);
		item.mask = TVIF_TEXT;
		item.cchTextMax = 64;
		item.pszText = comparison;
		item.hItem = tParent;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		while (tParent != NULL && strcmp(comparison, indexLink->name) != 0) {
			tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tParent);
			item.hItem = tParent;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		}

		//7.6 상호노드에서 찾은 위치번째의 자식노드를 이동한다.
		tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		i = 0;
		while (i < subscript) {
			tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
			i++;
		}
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);
		//7.7 마크한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)tChild);
	}
	return TRUE;
}

//8. 다음버튼을 클릭했을때
BOOL UpdatingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

	BusinessCardBinder *businessCardBinder;
	BusinessCard* next;
	IndexBinder *indexBinder;
	HTREEITEM root;
	HTREEITEM tParent;
	HTREEITEM tChild;
	TVITEM item = { 0, };
	Index *indexLink;
	Long subscript;
	TCHAR comparison[64];
	Long i;

	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexBinder = (IndexBinder*)GetProp(hWnd, "indexBinder");

		//8.1 명함철에서 다음명함으로 이동하다.
		next = BusinessCardBinder_Next(businessCardBinder);

		//8.2 다음명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)next->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)next->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)next->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)next->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)next->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)next->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)next->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)next->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)next->company.url);

		//8.3 색인철에서 현재명함의 색인을 찾는다.
		indexLink = IndexBinder_Find(indexBinder, next->company.name);

		//8.4 색인에서 현재 명함의 위치를 찾는다.
		subscript = Index_Find(indexLink, next);

		//8.5 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
		root = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)NULL);
		tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)root);
		item.mask = TVIF_TEXT;
		item.cchTextMax = 64;
		item.pszText = comparison;
		item.hItem = tParent;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		while (tParent != NULL && strcmp(comparison, indexLink->name) != 0) {
			tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tParent);
			item.hItem = tParent;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		}

		//8.6 상호노드에서 찾은 위치번째의 자식노드를 이동한다.
		tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		i = 0;
		while (i < subscript) {
			tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
			i++;
		}
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);
		
		//8.7 마크한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)tChild);
	}
	return TRUE;
}

//9. 맨끝버튼을 클릭했을때
BOOL UpdatingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	BusinessCard* last;
	IndexBinder *indexBinder;
	HTREEITEM root;
	HTREEITEM tParent;
	HTREEITEM tChild;
	TVITEM item = { 0, };
	Index *indexLink;
	Long subscript;
	TCHAR comparison[64];
	Long i;

	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexBinder = (IndexBinder*)GetProp(hWnd, "indexBinder");

		//9.1 명함철에서 맨끝명함으로 이동하다.
		last = BusinessCardBinder_Last(businessCardBinder);
		//9.2 맨끝명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)last->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)last->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)last->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)last->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)last->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)last->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)last->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)last->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)last->company.url);

		//9.3 색인철에서 현재명함의 색인을 찾는다.
		indexLink = IndexBinder_Find(indexBinder, last->company.name);

		//9.4 색인에서 현재 명함의 위치를 찾는다.
		subscript = Index_Find(indexLink, last);

		//9.5 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
		root = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)NULL);
		tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)root);
		item.mask = TVIF_TEXT;
		item.cchTextMax = 64;
		item.pszText = comparison;
		item.hItem = tParent;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		while (tParent != NULL && strcmp(comparison, indexLink->name) != 0) {
			tParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tParent);
			item.hItem = tParent;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		}

		//9.6 상호노드에서 찾은 위치번째의 자식노드를 이동한다.
		tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		i = 0;
		while (i < subscript) {
			tChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
			i++;
		}


		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);
		//9.7 마크한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)tChild);
	}
	return TRUE;
}

BOOL UpdatingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (wParam) {
	case IDC_TREE_INDEXBINDER:
		ret = UpdatingForm_OnTreeControlItemDoubleClicked(hWnd,wParam,lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

//10. TreeControl에서 성명을 더블클릭 했을때
BOOL UpdatingForm_OnTreeControlItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBinder *businessCardBinder=NULL;
	BusinessCard *index;
	IndexBinder *indexBinder=NULL;
	HTREEITEM tParent;
	HTREEITEM tChild;
	HTREEITEM tMark;
	Index *indexLink;
	Long subscript = 0;
	TCHAR name[64];
	TVITEM item = { 0, };

	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexBinder = (IndexBinder*)GetProp(hWnd, "indexBinder");

		//10.1 마크된 노드를 읽는다.
		tMark= (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CARET, (LPARAM)0);

		//10.2 마크된 노드의 부모노드를 찾는다.
		tParent= (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_PARENT, (LPARAM)tMark);

		//10.3 부모노드의 마크된 노드까지 위치를 센다.
		tChild= (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		while (tMark != tChild) {
			subscript++;
			tChild= (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
		}

		//10.4 부모노드의 상호로 색인철에서 찾는다.
		item.mask = TVIF_TEXT;

		item.cchTextMax = 64;
		item.pszText = name;
		tParent= (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_PARENT, (LPARAM)tChild);
		item.hItem = tParent;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		indexLink = IndexBinder_Find(indexBinder, name);

		//10.5 찾은 색인에서 센위치번째의 명함을 읽는다.
		index = Index_GetAt(indexLink, subscript);
	
		//10.6 명함철의 명함에 현재 명함을 출력한다.
		index = BusinessCardBinder_Move(businessCardBinder, index);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);
	}
	return TRUE;
}

//11. 닫기버튼을 클릭했을때
BOOL UpdatingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	IndexBinder *indexBinder;

	businessCardBinder = (BusinessCardBinder *)GetWindowLong(hWnd, GWL_USERDATA);
	indexBinder = (IndexBinder*)GetProp(hWnd, "indexBinder");


	if (businessCardBinder != NULL)
	{
		//11.1 명함철을 저장한다.
		BusinessCardBinder_Save(businessCardBinder);

		//11.2 명함철을 지운다.
		BusinessCardBinder_Destroy(businessCardBinder);
		free(businessCardBinder);
	}

	//11.3 색인철을 지운다.
	if (indexBinder != NULL) {
		IndexBinder_Destroy(indexBinder);
		free(indexBinder);
	}

	//11.4 윈도우를 닫는다.
	RemoveProp(hWnd, "indexBinder");
	EndDialog(hWnd, 0);
	return TRUE;
}