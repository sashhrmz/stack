#pragma once
#include "Stack.h"
#include "mainwindowview.h"
#include <regex>

class View;

class Controller {
public:

	Controller(Stack<int> *stack, View *view);
    ~Controller() = default;

	void Init();
	void Render();
	void Destruct();

	void Push(std::wstring str);
	void Pop();
	void Clear();
	void Sort();

 private:

	View* view_;
	Stack<int>* stack_;
};

 