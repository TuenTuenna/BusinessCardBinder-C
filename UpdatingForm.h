//UpdatingForm.h
#ifndef _UPDATINGFORM_H
#define _UPDATINGFORM_H // Guard
#include <windows.h>//LVM

BOOL CALLBACK UpdatingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnPutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnDrawButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnTreeControlItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif //_UPDATINGFORM_H