#include "DrawingForm.h"
#include "BusinessCardBinder.h"
#include "resource.h"

BOOL CALLBACK DrawingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG:
		ret = DrawingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_CLOSE:
		ret = DrawingForm_OnClose(hWnd, wParam, lParam); break;
	default:
		ret = FALSE; break;
	}
	return ret;
}

//1. 윈도우가 생성될 때
BOOL DrawingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND updatingForm;
	BusinessCardBinder *businessCardBinder;
	IndexBinder *indexBinder;
	BusinessCard businessCard;
	BusinessCard *index;
	Long count;
	Index *indexLink;
	Index(*indexLinks);
	Long i;
	Long j;
	BusinessCard *getIndex;
	TVINSERTSTRUCT tInsert = { 0, };
	HTREEITEM root;
	HTREEITEM tParent;
	HTREEITEM tChild;
	Long subscript;
	TVITEM item = { 0, };
	TCHAR comparison[64];


	//1.1 명함철 윈도우를 찾는다
	updatingForm = FindWindow("#32770", "명함철");
	businessCardBinder = (BusinessCardBinder*)GetWindowLong(updatingForm, GWL_USERDATA);
	indexBinder = (IndexBinder*)GetProp(updatingForm, "indexBinder");

	//1.2 명함철 윈도우의 명함철에서 명함위치를 읽는다.
	index = businessCardBinder->current;

	//1.3 명함철 윈도우의 명함철에서 꺼낸다.
	businessCard = BusinessCardBinder_Draw(businessCardBinder, index);

	// 1.4꺼낸 명함을 출력한다.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.emailAddress);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.faxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.url);

	//1.5 명함철 윈도우의 색인철에서 색인을 뺀다
	indexLink = IndexBinder_Draw(indexBinder, index, businessCard.company.name);

	//1.6 명함철 윈도우의 색인철에서 색인리스트를 만든다
	count = 0;
	IndexBinder_MakeList(indexBinder, &indexLinks, &count);

	//1.7명함철 윈도우의 TreeControl의 목록을 지운다
	SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_DELETEITEM, (WPARAM)0, (LPARAM)NULL);

	//1.8명함철 윈도우의 TreeControl에 회사들 노드를 만든다
	tInsert.item.mask = TVIF_TEXT;
	tInsert.hInsertAfter = TVI_ROOT;
	tInsert.item.pszText = "회사들";
	root = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);

	//1.9 색인개수만큼 반복한다
	i = 0;
	while (i < count) {
		//1.9.1 해당 색인의 상호노드를 회사들 노드의 자식노드로 만든다
		tInsert.hParent = root;
		tInsert.hInsertAfter = TVI_LAST;
		tInsert.item.pszText = indexLinks[i].name;
		tParent = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
		//1.9.2 해당색인의 상용량 만큼 반복한다ㅏ
		j = 0;
		while (j < indexLinks[i].length) {
			//1.9.2.1 성명노드를 상호노드의 자식노드로 만든다
			tInsert.hParent = tParent;
			tInsert.hInsertAfter = TVI_LAST;
			getIndex = Index_GetAt(indexLinks + i, j);
			tInsert.item.pszText = getIndex->personal.name;
			SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
			j++;
		}
		i++;
	}
	if (indexLinks != NULL) {
		free(indexLinks);
		indexLink = NULL;
	}

	//1.15 명함철 윈도우의 명함철에서 명함위치를 읽는다
	index = businessCardBinder->current;

	//1.16 명함이 있으면 명함철 윈도우에 명함을 출력한다
	if (index != NULL) {
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);
	

		//1. 10 명함철윈도우의 색인철에서 현재명함의 색인을 찾는다.
		indexLink = IndexBinder_Find(indexBinder, index->company.name);

		//1.11 색인에서 현재명함의 위치를 찾는다.
		subscript = Index_Find(indexLink, index);

		//1.12 찾은색인의 상호로 TreeControl에서 상호노드를 찾는다
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

		// 1.13 상호노드에서 찾은위치번째의 자식노드로 이동한다
		tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		i = 0; 
		while (i < subscript) {
			tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
			i++;
		}

		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);

		// 1.14 마크한다
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)tChild);

	}
	else {
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	}
	return TRUE;
}

//2. 닫기 버튼을 클릭했을 때
BOOL DrawingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	IndexBinder *indexBinder = NULL;
	BusinessCardBinder *businessCardBinder;
	Index *indexLink;
	Index(*indexLinks);
	BusinessCard *index = NULL;
	BusinessCard businessCard;
	BusinessCard *getIndex;
	TCHAR comparison[64];
	TVINSERTSTRUCT tInsert = { 0, };
	TVITEM item = { 0, };
	HTREEITEM root;
	HTREEITEM tParent;
	HTREEITEM tChild;
	Long subscript;
	Long i = 0;
	Long j = 0;
	Long count = 0;
	int confirm;
	HWND updatingForm;

	//2.1 메세지 박스를 출력한다.
	confirm = MessageBox(hWnd, "끼우시겠습니까?", "확인", MB_YESNOCANCEL | MB_ICONINFORMATION);

	//2.2 예 버튼을 클릭했을 때
	if (confirm == IDYES) {
		//2.2.1 명함을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)32, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)32, (LPARAM)businessCard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.url);

		//2.2.2 명함철 윈도우를 찾는다.
		updatingForm = FindWindow("#32770", "명함철");

		//명함철에 넣는다
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(updatingForm, GWL_USERDATA);
		indexBinder = (IndexBinder*)GetProp(updatingForm, "indexBinder");
		index = BusinessCardBinder_Put(businessCardBinder, businessCard);

		//2.2.3 명함철윈도우의 색인철에 넣는다.
		indexLink = IndexBinder_Put(indexBinder, index);

		//2.2.4 명함철 윈도우의 색인철에서 색인리스트를 만든다.
		count = 0;
		IndexBinder_MakeList(indexBinder, &indexLinks, &count);

		//2.2.5 명함철 윈도우의 TreeControl의 목록을 지운다.
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_DELETEITEM, (WPARAM)0, (LPARAM)NULL);

		//2.2.6 명함철 윈도우의 TreeControl에 회사들 노드를 만든다.
		tInsert.item.mask = TVIF_TEXT;
		tInsert.hParent = NULL;
		tInsert.hInsertAfter = TVI_ROOT;
		tInsert.item.pszText = "회사들";
		root = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);

		//2.2.7 색인 개수만큼 반복한다.
		i = 0;
		while (i < count) {
			//2.2.7.1 해당 색인의 상호노드를 회사들 노드의 자식노드로 만든다.
			tInsert.hParent = root;
			tInsert.hInsertAfter = TVI_LAST;
			tInsert.item.pszText = indexLinks[i].name;
			tParent = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);

			//2.2.7.2 해당 색인의 사용량 만큼 반복한다.
			j = 0;
			while (j < indexLinks[i].length) {
				//2.2.7.2.1 성명노드를 상호노드의 자식노드로 만든다.
				tInsert.hParent = tParent;
				tInsert.hInsertAfter = TVI_LAST;
				getIndex = Index_GetAt(indexLinks + i, j);
				tInsert.item.pszText = getIndex->personal.name;
				SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
				j++;
			}
			i++;
		}
		//2.2.8 명함철 윈도우의 명함에 명함을 출력한다.
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);

		//2.2.9 명함철 윈도우의 색인철에서 넣은 명함의 색인을 찾는다.
		indexLink = IndexBinder_Find(indexBinder, index->company.name);

		//2.2.10 색인에서 현재 명함의 위치를 찾는다.
		subscript = Index_Find(indexLink, index);

		//2.2.11 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
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

		//2.2.12 상호노드에서 찾은 위치번째의 자식노드를 이동한다.
		tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		i = 0;
		while (i < subscript) {
			tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
			i++;
		}
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);
		//2.2.13 마크한다.
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)tChild);

		if (indexLinks != NULL) {
			free(indexLinks);
			indexLinks = NULL;
		}

		//2.2.14 윈도우를 닫는다.
		EndDialog(hWnd, 0);
	}

	//2.3 아니오 버튼을 눌렀을 때
	else if (confirm == IDNO) {
		//2.3.1 윈도우를 닫는다.
		EndDialog(hWnd, 0);
	}

	return TRUE;

}