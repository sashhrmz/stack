#include "controller.h"

Controller::Controller(Stack<int> *stack, View* view) : stack_(stack), view_(view) {}

void Controller::Init() {
	view_->Init();
}

void Controller::Render() {
	view_->ReDraw(stack_->begin(), stack_->IsEmpty(), stack_->Size());
}

void Controller::Push(std::wstring str) {
	std::wregex parser(L"\\s+");
	std::vector<std::wstring> vector{ std::wsregex_token_iterator(str.begin(), str.end(), parser, -1), {} };
	for (auto element : vector) {
		stack_->Push(std::stoi(element));
	}
	view_->ReDraw(stack_->begin(), stack_->IsEmpty(), stack_->Size());
}

void Controller::Pop() {
	stack_->Pop();
	view_->ReDraw(stack_->begin(), stack_->IsEmpty(), stack_->Size());
}

void Controller::Clear() {
	stack_->Clear();
	view_->ReDraw(stack_->begin(), stack_->IsEmpty(), stack_->Size());
}

void Controller::Sort() {
	SortDataStructureVisitor<int> visitor;
	stack_->Accept(visitor);
	view_->ReDraw(stack_->begin(), stack_->IsEmpty(), stack_->Size());
}

void Controller::Destruct() {
	view_->Destruct();
}
