//PuttingForm.c

#include "PuttingForm.h"
#include "resource.h"
#include "BusinessCardBinder.h"
#include <string.h>
#include <stdio.h>
#pragma warning(disable : 4996)

BOOL CALLBACK PuttingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG:
		ret = PuttingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND:
		ret = PuttingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE:
		ret = PuttingForm_OnClose(hWnd, wParam, lParam); break;
	default:
		ret = FALSE; break;
	}

	return ret;
}


BOOL PuttingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long i = 0;
	TCHAR* positions[7] = { "회장", "사장", "부장", "차장", "과장", "대리", "사원" };
	//1.1 직급 콘보박스에 목록을 만든다.
	while (i < 7) {
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)positions[i]);
		i++;
	}

	//1.2 이메일 주소 콤보박스에 목록을 만든다
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), CB_ADDSTRING, (WPARAM)0, (LPARAM) "naver.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), CB_ADDSTRING, (WPARAM)0, (LPARAM) "daum.net");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), CB_ADDSTRING, (WPARAM)0, (LPARAM) "nate.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), CB_ADDSTRING, (WPARAM)0, (LPARAM) "gmail.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), CB_ADDSTRING, (WPARAM)0, (LPARAM) "직접입력");

	return TRUE;

}


BOOL PuttingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_PUT:
		ret = PuttingForm_OnPutButtonClicked(hWnd, wParam, lParam); break;
	case IDC_EDIT_COMPANY_NAME:
		ret = PuttingForm_OnCompanyNameEditKillFocus(hWnd, wParam, lParam); break;
	default:
		ret = FALSE; break;
	}

	return ret;
}

//2.상호에디트가 포커스를 잃을 때
BOOL PuttingForm_OnCompanyNameEditKillFocus(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR companyName[64];
	BusinessCard *index;
	HWND updatingForm;
	IndexBinder *indexBinder;
	Index *indexLink;
	

	if (HIWORD(wParam) == EN_KILLFOCUS) {
		//2.1 상호를 읽는다
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)companyName);

		//2.2 명함철 윈도우를 찾는다
		updatingForm = FindWindow("#32770", "명함철");

		//2.3 명함철 윈도우의 색인철에서 상호를 찾는다.
		indexBinder = (IndexBinder*)GetProp(updatingForm, "indexBinder");
		indexLink = IndexBinder_Find(indexBinder, companyName);

		//2.4 상호가 있으면 첫번째 명함의 회사를 출력한다
		if (indexLink != NULL) {
			index = Index_GetAt(indexLink, 0);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);
		}
	}
	return TRUE;
}

//3.넣기버튼을 클릭했을 때
BOOL PuttingForm_OnPutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard businessCard;
	HWND updatingForm;
	BusinessCardBinder *businessCardBinder;
	IndexBinder *indexBinder;
	BusinessCard *index;
	Index *indexLink;
	Index(*indexLinks);
	Long indexLinkCount;
	TVINSERTSTRUCT tInsert = { 0, };
	Long i = 0;
	Long j = 0;
	HTREEITEM tParent;
	HTREEITEM tChild;
	HTREEITEM root;
	BusinessCard *getIndex;
	Long subscript;
	TCHAR comparison[64];
	TVITEM item = { 0, };
	TCHAR domain[16];

	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1 명함을 읽는다
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)32, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)32, (LPARAM)domain);

		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_URL), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.url);

		sprintf(businessCard.personal.emailAddress, "%s@%s", businessCard.personal.emailAddress, domain);

		//3.2 명함철 윈도우를 찾는다
		updatingForm = FindWindow("#32770", "명함철");

		//3.3 명함철 윈도우의 명함철에 넣는다
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(updatingForm, GWL_USERDATA);
		index = BusinessCardBinder_Put(businessCardBinder, businessCard);

		//3.4 명함철 윈도우의 색인철에 끼운다.
		indexBinder=(IndexBinder*)GetProp(updatingForm, "indexBinder");
		indexLink = IndexBinder_Put(indexBinder, index);

		//3.5 명함철 윈도우의 TreeControl의 목록을 지운다.
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_DELETEITEM, (WPARAM)0, (LPARAM)NULL);

		//3.6 명함철 윈도우의 색인철에서 색인 리스트를 만든다.
		IndexBinder_MakeList(indexBinder, &indexLinks, &indexLinkCount);

		//3.7 명함철 윈도우의 TreeControl에 회사들 노드를 만든다.
		tInsert.item.mask = TVIF_TEXT;

		tInsert.hParent = NULL;
		tInsert.hInsertAfter = TVI_ROOT;
		tInsert.item.pszText = "회사들";
		tParent = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);

		//3.8 색인 개수만큼 반복한다.
		i = 0;
		while (i < indexLinkCount) {
			//3.8.1 해당 색인의 상호노드를 명함철 윈도우의 TreeControl의 회사들 노드의 자식노드로 만든다.
			tInsert.hParent = tParent;
			tInsert.hInsertAfter = TVI_LAST;
			tInsert.item.pszText = indexLinks[i].name;
			tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
			
			//3.8.2 해당 색인의 사용량 만큼 반복한다.
			j = 0;
			while (j < indexLinks[i].length) {
				//3.8.2.1 성명노드를 명함철 윈도우의 TreeControl의 상호노드의 자식노드로 만든다.
				tInsert.hParent = tChild;
				tInsert.hInsertAfter = TVI_LAST;
				getIndex = Index_GetAt(indexLinks + i, j);
				tInsert.item.pszText = getIndex->personal.name;
				SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
				j++;
			}
			i++;
		}
		//3.9 명함철 윈도우에 명함을 출력한다.
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);

		//3.10 명함철 윈도우의 색인철에서 넣은 명함의 색인을 찾는다.
		indexLink = IndexBinder_Find(indexBinder, index->company.name);

		//3.11 명함철 윈도우의 색인철에서 찾은 색인에서 현재 명함의 위치를 찾는다.
		subscript = Index_Find(indexLink, index);

		//3.12 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
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

		//3.13 명함철 윈도우의 상호노드에서 찾은 위치번째의 자식노드를 이동한다.
		tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		i = 0;
		while (i < subscript) {
			tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
			i++;
		}
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);

		//3.14 마크한다.
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)tChild);
	}
	if (indexLinks != NULL) {
		free(indexLinks);
		indexLinks = NULL;
	}

	//3.15 윈도우를 닫는다
	EndDialog(hWnd, 0);

	return TRUE;
}

//4. 닫기버튼을 눌렀을 때
BOOL PuttingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//4.1 윈도우를 닫는다
	EndDialog(hWnd, 0);

	return TRUE;
}
