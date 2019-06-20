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
	TCHAR* positions[7] = { "ȸ��", "����", "����", "����", "����", "�븮", "���" };
	//1.1 ���� �ܺ��ڽ��� ����� �����.
	while (i < 7) {
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)positions[i]);
		i++;
	}

	//1.2 �̸��� �ּ� �޺��ڽ��� ����� �����
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), CB_ADDSTRING, (WPARAM)0, (LPARAM) "naver.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), CB_ADDSTRING, (WPARAM)0, (LPARAM) "daum.net");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), CB_ADDSTRING, (WPARAM)0, (LPARAM) "nate.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), CB_ADDSTRING, (WPARAM)0, (LPARAM) "gmail.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_EMAILADDRESS), CB_ADDSTRING, (WPARAM)0, (LPARAM) "�����Է�");

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

//2.��ȣ����Ʈ�� ��Ŀ���� ���� ��
BOOL PuttingForm_OnCompanyNameEditKillFocus(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR companyName[64];
	BusinessCard *index;
	HWND updatingForm;
	IndexBinder *indexBinder;
	Index *indexLink;
	

	if (HIWORD(wParam) == EN_KILLFOCUS) {
		//2.1 ��ȣ�� �д´�
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)companyName);

		//2.2 ����ö �����츦 ã�´�
		updatingForm = FindWindow("#32770", "����ö");

		//2.3 ����ö �������� ����ö���� ��ȣ�� ã�´�.
		indexBinder = (IndexBinder*)GetProp(updatingForm, "indexBinder");
		indexLink = IndexBinder_Find(indexBinder, companyName);

		//2.4 ��ȣ�� ������ ù��° ������ ȸ�縦 ����Ѵ�
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

//3.�ֱ��ư�� Ŭ������ ��
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
		//3.1 ������ �д´�
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

		//3.2 ����ö �����츦 ã�´�
		updatingForm = FindWindow("#32770", "����ö");

		//3.3 ����ö �������� ����ö�� �ִ´�
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(updatingForm, GWL_USERDATA);
		index = BusinessCardBinder_Put(businessCardBinder, businessCard);

		//3.4 ����ö �������� ����ö�� �����.
		indexBinder=(IndexBinder*)GetProp(updatingForm, "indexBinder");
		indexLink = IndexBinder_Put(indexBinder, index);

		//3.5 ����ö �������� TreeControl�� ����� �����.
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_DELETEITEM, (WPARAM)0, (LPARAM)NULL);

		//3.6 ����ö �������� ����ö���� ���� ����Ʈ�� �����.
		IndexBinder_MakeList(indexBinder, &indexLinks, &indexLinkCount);

		//3.7 ����ö �������� TreeControl�� ȸ��� ��带 �����.
		tInsert.item.mask = TVIF_TEXT;

		tInsert.hParent = NULL;
		tInsert.hInsertAfter = TVI_ROOT;
		tInsert.item.pszText = "ȸ���";
		tParent = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);

		//3.8 ���� ������ŭ �ݺ��Ѵ�.
		i = 0;
		while (i < indexLinkCount) {
			//3.8.1 �ش� ������ ��ȣ��带 ����ö �������� TreeControl�� ȸ��� ����� �ڽĳ��� �����.
			tInsert.hParent = tParent;
			tInsert.hInsertAfter = TVI_LAST;
			tInsert.item.pszText = indexLinks[i].name;
			tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
			
			//3.8.2 �ش� ������ ��뷮 ��ŭ �ݺ��Ѵ�.
			j = 0;
			while (j < indexLinks[i].length) {
				//3.8.2.1 �����带 ����ö �������� TreeControl�� ��ȣ����� �ڽĳ��� �����.
				tInsert.hParent = tChild;
				tInsert.hInsertAfter = TVI_LAST;
				getIndex = Index_GetAt(indexLinks + i, j);
				tInsert.item.pszText = getIndex->personal.name;
				SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tInsert);
				j++;
			}
			i++;
		}
		//3.9 ����ö �����쿡 ������ ����Ѵ�.
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);

		//3.10 ����ö �������� ����ö���� ���� ������ ������ ã�´�.
		indexLink = IndexBinder_Find(indexBinder, index->company.name);

		//3.11 ����ö �������� ����ö���� ã�� ���ο��� ���� ������ ��ġ�� ã�´�.
		subscript = Index_Find(indexLink, index);

		//3.12 ã�� ������ ��ȣ�� TreeControl���� ��ȣ��带 ã�´�.
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

		//3.13 ����ö �������� ��ȣ��忡�� ã�� ��ġ��°�� �ڽĳ�带 �̵��Ѵ�.
		tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)tParent);
		i = 0;
		while (i < subscript) {
			tChild = (HTREEITEM)SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)tChild);
			i++;
		}
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)root);
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)tParent);

		//3.14 ��ũ�Ѵ�.
		SendMessage(GetDlgItem(updatingForm, IDC_TREE_INDEXBINDER), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)tChild);
	}
	if (indexLinks != NULL) {
		free(indexLinks);
		indexLinks = NULL;
	}

	//3.15 �����츦 �ݴ´�
	EndDialog(hWnd, 0);

	return TRUE;
}

//4. �ݱ��ư�� ������ ��
BOOL PuttingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//4.1 �����츦 �ݴ´�
	EndDialog(hWnd, 0);

	return TRUE;
}
