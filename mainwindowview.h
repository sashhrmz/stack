#pragma once
#include "controller.h"
#include "framework.h"
#include <windows.h>
#include "resource.h"

class View {
public:
	View(HINSTANCE hInstance, DLGPROC dlgproc) : hInstance_(hInstance), dlgproc_(dlgproc) {}

	View() = default;
	~View() = default;

	void Init();
	void ReDraw(Stack<int>::Iterator begin, bool is_stack_empty, int stack_size);
	void Destruct();

private:
	HINSTANCE hInstance_;
	DLGPROC dlgproc_;
	HWND dialog_;
	//INT_PTR CALLBACK Process(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};