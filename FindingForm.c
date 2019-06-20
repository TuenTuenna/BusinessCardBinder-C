// FindingForm.c

#include"FindingForm.h"
#include"BusinessCardBinder.h"
#include"resource.h"
#include<stdlib.h>

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_COMMAND:
		ret = FindingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE:
		ret = FindingForm_OnClose(hWnd, wParam, lParam); break;
	default:
		ret = FALSE; break;
	}

	return ret;
}

BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIND:
		ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_SELECT:
		ret = FindingForm_OnSelectButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIRST:
		ret = FindingForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS:
		ret = FindingForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT:
		ret = FindingForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST:
		ret = FindingForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	default:
		ret = FALSE; break;
	}
	return ret;
}

// 1. 찾기 버튼을 클릭했을 때
BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBinder *businessCardBinder;
	BusinessCard* (*indexes);
	TCHAR personalName[11];
	HWND updatingForm;
	Long count;
	Long current = 0;
	if (HIWORD(wParam) == BN_CLICKED) {
		// 1.1. 성명을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)personalName);
		// 1.2. 명함철 윈도우를 찾는다.
		updatingForm = FindWindow("#32770", "명함철");
		// 1.3. 명함철 윈도우의 명함철에서 성명을 찾는다.
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(updatingForm, GWL_USERDATA);
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}
		BusinessCardBinder_Find(businessCardBinder, personalName, &indexes, &count);
		// 1.4. 찾은 명함이 있으면 첫번째 명함을 출력한다.
		if (count > 0) {
			SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes);
			SetProp(hWnd, "count", (HANDLE)count);
			SetProp(hWnd, "current", (HANDLE)current);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.position);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.emailAddress);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.url);
		}
		else {
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		}
	}
	return TRUE;
}

// 2. 선택하기 버튼을 클릭했을 때
BOOL FindingForm_OnSelectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBinder *businessCardBinder=NULL;
	BusinessCard *index;
	Index *indexLink;
	BusinessCard*(*indexes);
	Long current;
	HWND updatingForm = NULL;
	TVINSERTSTRUCT tInsert = { 0, };
	TCHAR comparison[64];
	IndexBinder *indexBinder=NULL;
	Long subscript;
	HTREEITEM root;
	HTREEITEM tParent;
	HTREEITEM tChild;
	TVITEM item = { 0, };
	Long i;

	if (HIWORD(wParam) == BN_CLICKED) {
		// 2.1. 명함의 위치를 읽는다.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "current");

		//2.2 명함철 윈도우를 찾는다.
		updatingForm = FindWindow("#32770", "명함철");
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(updatingForm, GWL_USERDATA);
		indexBinder = (IndexBinder*)GetProp(updatingForm, "indexBinder");

		//2.3. 명함철 윈도우의 명함철에서 특정 명함으로 이동한다.
		index = BusinessCardBinder_Move(businessCardBinder, indexes[current]);

		//2.4 명함철 윈도우의 색인철에서 넣은 명함의 색인을 찾는다.
		indexLink = IndexBinder_Find(indexBinder, index->company.name);

		//2.5 명함철 윈도우의 색인에서 현재 명함의 위치를 찾는다.
		subscript = Index_Find(indexLink, index);

		//2.6 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
		root = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)NULL);
		tParent = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)root);
		item.mask = TVIF_TEXT;
		item.cchTextMax = 64;
		item.pszText = comparison;
		item.hItem = tParent;
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		while (tParent != NULL && strcmp(comparison, indexLink->name) != 0) {
			tParent = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tParent);
			item.hItem = tParent;
			SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETITEM, (WPARAM)0, (LPARAM)&item);
		}

		//2.7 찾은 상호노드에서 찾은 위치번째의 자식노드를 이동한다.
		tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		i = 0;
		while (i < subscript) {
			tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
			i++;
		}

		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);

		//2.8 명함철 윈도우에서 해당 노드를 마크한다
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)tChild);

		//2.9 명함철 윈도우의 명함에 출력한다.
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);

		if (indexes != NULL) {
			free(indexes);
			indexes = NULL;
		}
		RemoveProp(hWnd, "current");
		RemoveProp(hWnd, "count");
		// 2.10 윈도우를 닫는다.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

// 3. 맨처음 버튼을 클릭했을 때
BOOL FindingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);
	Long i;
	if (HIWORD(wParam) == BN_CLICKED) {
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		// 3.1. 찾은 명함들에서 맨 처음 명함으로 이동한다.
		i = 0;
		// 3.2. 첫번째 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.url);
		SetProp(hWnd, "current", (HANDLE)i);
	}
	return TRUE;
}

// 4. 이전 버튼을 클릭했을 때
BOOL FindingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);
	Long current;
	if (HIWORD(wParam) == BN_CLICKED) {
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "current");
		// 4.1. 찾은 명함들에서 이전 명함으로 이동한다.
		current--;
		if (current < 0) {
			current = 0;
		}
		// 4.2. 이전 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.url);
		SetProp(hWnd, "current", (HANDLE)current);
	}
	return TRUE;
}

// 5. 다음 버튼을 클릭했을 때
BOOL FindingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);
	Long current;
	Long count;
	if (HIWORD(wParam) == BN_CLICKED) {
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "current");
		count = (Long)GetProp(hWnd, "count");
		// 5.1. 찾은 명함들에서 다음 명함으로 이동한다.
		if (current < count - 1) {
			current++;
		}
		// 5.2. 다음 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.url);
		SetProp(hWnd, "current", (HANDLE)current);
	}
	return TRUE;
}

// 6. 맨 끝 버튼을 클릭했을 때
BOOL FindingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);
	Long current;
	Long count;
	if (HIWORD(wParam) == BN_CLICKED) {
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "count");

		// 6.1. 찾은 명함들 중에서 마지막 명함으로 이동한다.
		current = count - 1;
		// 6.2. 마지막 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.url);
		SetProp(hWnd, "current", (HANDLE)current);
	}
	return TRUE;
}

// 7. 닫기 버튼을 클릭했을 때
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);
	indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
	if (indexes != NULL) {
		free(indexes);
	}
	// 7.1. 윈도우를 닫는다.
	RemoveProp(hWnd, "current");
	RemoveProp(hWnd, "count");
	EndDialog(hWnd, 0);
	return TRUE;
}