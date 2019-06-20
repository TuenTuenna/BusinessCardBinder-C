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

//1. �����찡 ������ ��
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


	//1.1 ����ö �����츦 ã�´�
	updatingForm = FindWindow("#32770", "����ö");
	businessCardBinder = (BusinessCardBinder*)GetWindowLong(updatingForm, GWL_USERDATA);
	indexBinder = (IndexBinder*)GetProp(updatingForm, "indexBinder");

	//1.2 ����ö �������� ����ö���� ������ġ�� �д´�.
	index = businessCardBinder->current;

	//1.3 ����ö �������� ����ö���� ������.
	businessCard = BusinessCardBinder_Draw(businessCardBinder, index);

	// 1.4���� ������ ����Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.emailAddress);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.faxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.url);

	//1.5 ����ö �������� ����ö���� ������ ����
	indexLink = IndexBinder_Draw(indexBinder, index, businessCard.company.name);

	//1.6 ����ö �������� ����ö���� ���θ���Ʈ�� �����
	count = 0;
	IndexBinder_MakeList(indexBinder, &indexLinks, &count);

	//1.7����ö �������� TreeControl�� ����� �����
	SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_DELETEITEM, (WPARAM)0, (LPARAM)NULL);

	//1.8����ö �������� TreeControl�� ȸ��� ��带 �����
	tInsert.item.mask = TVIF_TEXT;
	tInsert.hInsertAfter = TVI_ROOT;
	tInsert.item.pszText = "ȸ���";
	root = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);

	//1.9 ���ΰ�����ŭ �ݺ��Ѵ�
	i = 0;
	while (i < count) {
		//1.9.1 �ش� ������ ��ȣ��带 ȸ��� ����� �ڽĳ��� �����
		tInsert.hParent = root;
		tInsert.hInsertAfter = TVI_LAST;
		tInsert.item.pszText = indexLinks[i].name;
		tParent = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
		//1.9.2 �ش������ ��뷮 ��ŭ �ݺ��Ѵ٤�
		j = 0;
		while (j < indexLinks[i].length) {
			//1.9.2.1 �����带 ��ȣ����� �ڽĳ��� �����
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

	//1.15 ����ö �������� ����ö���� ������ġ�� �д´�
	index = businessCardBinder->current;

	//1.16 ������ ������ ����ö �����쿡 ������ ����Ѵ�
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
	

		//1. 10 ����ö�������� ����ö���� ��������� ������ ã�´�.
		indexLink = IndexBinder_Find(indexBinder, index->company.name);

		//1.11 ���ο��� ��������� ��ġ�� ã�´�.
		subscript = Index_Find(indexLink, index);

		//1.12 ã�������� ��ȣ�� TreeControl���� ��ȣ��带 ã�´�
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

		// 1.13 ��ȣ��忡�� ã����ġ��°�� �ڽĳ��� �̵��Ѵ�
		tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		i = 0; 
		while (i < subscript) {
			tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
			i++;
		}

		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);

		// 1.14 ��ũ�Ѵ�
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

//2. �ݱ� ��ư�� Ŭ������ ��
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

	//2.1 �޼��� �ڽ��� ����Ѵ�.
	confirm = MessageBox(hWnd, "����ðڽ��ϱ�?", "Ȯ��", MB_YESNOCANCEL | MB_ICONINFORMATION);

	//2.2 �� ��ư�� Ŭ������ ��
	if (confirm == IDYES) {
		//2.2.1 ������ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)32, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)32, (LPARAM)businessCard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.url);

		//2.2.2 ����ö �����츦 ã�´�.
		updatingForm = FindWindow("#32770", "����ö");

		//����ö�� �ִ´�
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(updatingForm, GWL_USERDATA);
		indexBinder = (IndexBinder*)GetProp(updatingForm, "indexBinder");
		index = BusinessCardBinder_Put(businessCardBinder, businessCard);

		//2.2.3 ����ö�������� ����ö�� �ִ´�.
		indexLink = IndexBinder_Put(indexBinder, index);

		//2.2.4 ����ö �������� ����ö���� ���θ���Ʈ�� �����.
		count = 0;
		IndexBinder_MakeList(indexBinder, &indexLinks, &count);

		//2.2.5 ����ö �������� TreeControl�� ����� �����.
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_DELETEITEM, (WPARAM)0, (LPARAM)NULL);

		//2.2.6 ����ö �������� TreeControl�� ȸ��� ��带 �����.
		tInsert.item.mask = TVIF_TEXT;
		tInsert.hParent = NULL;
		tInsert.hInsertAfter = TVI_ROOT;
		tInsert.item.pszText = "ȸ���";
		root = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);

		//2.2.7 ���� ������ŭ �ݺ��Ѵ�.
		i = 0;
		while (i < count) {
			//2.2.7.1 �ش� ������ ��ȣ��带 ȸ��� ����� �ڽĳ��� �����.
			tInsert.hParent = root;
			tInsert.hInsertAfter = TVI_LAST;
			tInsert.item.pszText = indexLinks[i].name;
			tParent = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);

			//2.2.7.2 �ش� ������ ��뷮 ��ŭ �ݺ��Ѵ�.
			j = 0;
			while (j < indexLinks[i].length) {
				//2.2.7.2.1 �����带 ��ȣ����� �ڽĳ��� �����.
				tInsert.hParent = tParent;
				tInsert.hInsertAfter = TVI_LAST;
				getIndex = Index_GetAt(indexLinks + i, j);
				tInsert.item.pszText = getIndex->personal.name;
				SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
				j++;
			}
			i++;
		}
		//2.2.8 ����ö �������� ���Կ� ������ ����Ѵ�.
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);

		//2.2.9 ����ö �������� ����ö���� ���� ������ ������ ã�´�.
		indexLink = IndexBinder_Find(indexBinder, index->company.name);

		//2.2.10 ���ο��� ���� ������ ��ġ�� ã�´�.
		subscript = Index_Find(indexLink, index);

		//2.2.11 ã�� ������ ��ȣ�� TreeControl���� ��ȣ��带 ã�´�.
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

		//2.2.12 ��ȣ��忡�� ã�� ��ġ��°�� �ڽĳ�带 �̵��Ѵ�.
		tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		i = 0;
		while (i < subscript) {
			tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
			i++;
		}
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);
		//2.2.13 ��ũ�Ѵ�.
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)tChild);

		if (indexLinks != NULL) {
			free(indexLinks);
			indexLinks = NULL;
		}

		//2.2.14 �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
	}

	//2.3 �ƴϿ� ��ư�� ������ ��
	else if (confirm == IDNO) {
		//2.3.1 �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
	}

	return TRUE;

}