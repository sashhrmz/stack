#include "test.h"

int main() {
Test();
Stack<int> stack = {1, 2, 3, 4, 10, 1, 5, 2};
SortDataStructureVisitor<int> v;
stack.Accept(dynamic_cast<Visitor<int>&>(v));
std::cout << stack <<std::endl;
return 0;
}