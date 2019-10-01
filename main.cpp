// WindowsProject5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Resource.h"
#include "main.h"
#include "Stack.h"
#include <string>
#include "controller.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
INT_PTR CALLBACK    Router(HWND, UINT, WPARAM, LPARAM);
Controller* controller;
Stack<int>* stack;
View* view;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
	stack = new Stack<int>({ 0, 0, 0, 0, 0 });
	view = new View(hInstance, Router);
	controller = new Controller(stack, view);
	
	controller->Init();

	return 0;
}

INT_PTR CALLBACK Router(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    
	UNREFERENCED_PARAMETER(lParam);
	
	switch (message) {
	case WM_PAINT:
	{
		controller->Render();
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_PUSH:
		{
			TCHAR buff[1024];
			HWND hwndList = GetDlgItem(hDlg, IDC_PUSHELEMENT);
			GetWindowText(hwndList, buff, 1024);
			controller->Push(buff);
			return (INT_PTR)TRUE;
		}
		case IDC_CLEAR:
		{
			controller->Clear();
			return (INT_PTR)TRUE;
		}
		case IDC_POP:
		{
			controller->Pop();
			return (INT_PTR)TRUE;
		}
		case IDC_SORT:
		{
			controller->Sort();
			return (INT_PTR)TRUE;
		}

		case IDCANCEL:
		{
			controller->Destruct();
			return (INT_PTR)TRUE;
		}
		}
	}
	}
    return (INT_PTR)FALSE;
}
