#include <windows.h>
#include "mainwindowview.h"
#include <string>
#include "resource.h"
#include "controller.h"

void View::ReDraw(Stack<int>::Iterator begin, bool is_stack_empty, int stack_size) {
	HWND hwndList = GetDlgItem(dialog_, IDC_LIST3);
	SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
	for (int i = 0; i < stack_size; ++i, begin++) {
		std::wstring element = std::to_wstring(*begin);
		SendMessage(hwndList, LB_ADDSTRING, 0, (WPARAM)element.c_str());
	}
	HWND hwnd_static_text = GetDlgItem(dialog_, IDC_STATIC);
	std::wstring size = L"Size: " + std::to_wstring(stack_size);
	SendMessage(hwnd_static_text, WM_SETTEXT, 0, (WPARAM)size.c_str());
}

void View::Init() {
	dialog_ = (HWND)CreateDialog(hInstance_, MAKEINTRESOURCE(IDD_DIALOG1), 0, dlgproc_);
	ShowWindow(dialog_, SW_SHOW);

	HACCEL hAccelTable = LoadAccelerators(hInstance_, MAKEINTRESOURCE(IDD_DIALOG1));

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void View::Destruct() {
	PostQuitMessage(0);
}