#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
class Stack;

template <typename T>
class Visitor {
public:
	virtual void Visit(Stack<T>& stack) = 0;
};

template <typename T>
class SortDataStructureVisitor : public Visitor<T> {
	void Visit(Stack<T>& stack) override {
		std::vector<T> vec;
		int size = stack.Size();
		for (int i = 0; i < size; ++i) {
			vec.push_back(stack.Top());
			stack.Pop();
		}
		std::sort(vec.begin(), vec.end());

		for (auto element : vec) {
			stack.Push(element);
		}
	}
};

template<typename T>
class Stack {
public:

	class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
	public:
		T& operator*() const {
			return stack_->stack_[index_];
		}

		T* operator->() const {
			return &stack_[index_];
		}

		Iterator& operator++() {
			index_++;
			return *this;
		}

		const Iterator operator++(int) {
			index_++;
			return *this;
		}

		Iterator& operator--() {
			if (index_ == 0) {
				index_ = stack_->size_ - 1;
			}
			else {
				index_--;
			}
			return *this;
		}

		const Iterator operator--(int) {
			if (index_ == 0) {
				index_ = stack_->size_ - 1;
			}
			else {
				index_--;
			}
			return *this;
		}

		bool operator==(const Iterator& other) const {
			return stack_ == other.stack_ && index_ == other.index_;
		}

		bool operator!=(const Iterator& other) const {
			return !(*this == other);
		}

	private:
		friend class Stack;
		const Stack* const stack_;
		size_t index_;

		Iterator(const Stack* const stack, size_t index)
			: stack_(stack), index_(index) {}
	};

	class ConstIterator :
		public std::iterator<std::bidirectional_iterator_tag, T> {
	public:
		const T& operator*() const {
			return stack_[index_];
		}

		const T* operator->() const {
			return &stack_[index_];
		}

		ConstIterator& operator++() {
			index_++;
			return Iterator(stack_, index_);
		}

		const ConstIterator operator++(int) {
			index_++;
			return Iterator(stack_, index_);
		}

		ConstIterator& operator--() {
			if (index_ == 0) {
				index_ = stack_->size_ - 1;
			}
			else {
				index_--;
			}
			return *this;
		}

		const ConstIterator operator--(int) {
			if (index_ == 0) {
				index_ = stack_->size_ - 1;
			}
			else {
				index_--;
			}
			return *this;
		}

		bool operator==(const ConstIterator& other) const {
			return stack_ == other.stack_ && index_ == other.index_;
		}

		bool operator!=(const ConstIterator& other) const {
			return !(this == other);
		}

	private:
		friend class Stack;
		const Stack* const stack_;
		size_t index_;

		ConstIterator(const Stack* const stack, size_t index)
			: stack_(stack), index_(index) {}
	};

	Stack() : size_(0), maxsize_(1), stack_(new T[maxsize_]) {}

	explicit Stack(size_t size) : size_(size), maxsize_(2 * size),
		stack_(new T[maxsize_]) {
		for (int i = 0; i < size_; ++i) {
			stack_[i] = 0;
		}
	}

	~Stack() = default;

	Stack(std::initializer_list<T> list) noexcept : size_(list.size()),
		maxsize_(2 * list.size()), stack_(new T[maxsize_]) {
		int i = 0;
		for (auto it = list.begin(); it != list.end(); ++it, ++i) {
			stack_[i] = *it;
		}
	}

	void Accept(Visitor<T>& visitor) {
		visitor.Visit(*this);
	}

	Iterator begin() { return Iterator(this, 0); }

	Iterator end() { return Iterator(this, size_); }

	ConstIterator begin() const { return Iterator(this, 0); }

	ConstIterator end() const { return Iterator(this, size_); }

	Stack(Stack<T>&& stack) noexcept;

	Stack(Stack<T> const& stack);

	Stack<T>& operator=(Stack<T>&& stack) noexcept;

	Stack<T>& operator=(Stack<T> const& stack);

	bool operator==(Stack& lhs) const;

	bool operator!=(Stack& other) const;

	void operator+=(Stack<T>& other);

	Stack<T> operator+(Stack<T>& other);

	template<typename H>
	friend std::ostream& operator<<(std::ostream& out, Stack<H>& stack);

	template<typename U>
	friend std::istream& operator>>(std::istream& in, Stack<U>& stack);

	bool IsEmpty() const { return !static_cast<bool>(size_); }

	size_t Size() const { return size_; }

	T Top() const;

	void Relocate(size_t new_size);

	void Push(T element);

	void Pop();

	void Swap(Stack<T>& other);

	void Clear();

private:
	size_t size_;
	size_t maxsize_;
	T* stack_;

	T* operator[](size_t index) const { return stack_[index]; }
};

template<typename T>
Stack<T>::Stack(Stack<T>&& stack) noexcept : size_(stack.size_),
maxsize_(stack.maxsize_),
stack_(stack.stack_) {
	stack.size_ = 0;
	stack.maxsize_ = 1;
	stack.stack_ = new T[stack.maxsize_];
}

template<typename T>
Stack<T>::Stack(Stack<T> const& stack) : size_(stack.size_),
maxsize_(stack.maxsize_),
stack_(stack.stack_) {}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& stack) noexcept {
	size_ = stack.size_;
	maxsize_ = stack.maxsize_;
	stack_ = stack.stack_;
	stack.size_ = 0;
	stack.maxsize_ = 1;
	stack.stack_ = new T[stack.maxsize_];
	return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T> const& stack) {
	size_ = stack.size_;
	maxsize_ = stack.maxsize_;
	stack_ = stack.stack_;
	return *this;
}

template<typename T>
bool Stack<T>::operator==(Stack<T>& lhs) const {
	if (size_ != lhs.Size()) {
		return false;
	}
	for (size_t i = 0; i < size_; ++i) {
		if (this->stack_[i] != lhs.stack_[i]) {
			return false;
		}
	}
	return true;
}

template<typename T>
bool Stack<T>::operator!=(Stack& other) const {
	return !(*this == other);
}

template<typename T>
void Stack<T>::operator+=(Stack<T>& other) {
	for (int i = 0; i < other.size_; ++i) {
		this->Push(other.stack_[i]);
	}
}

template<typename T>
Stack<T> Stack<T>::operator+(Stack<T>& other) {
	Stack<T> copy = Stack<T>();
	for (int i = 0; i < this->size_; ++i) {
		copy.Push(stack_[i]);
	}
	copy += other;
	return copy;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, Stack<T>& stack) {
	out << "size : " << stack.size_ << ", " << "stack : " << std::endl;
	for (int i = 0; i < stack.size_; ++i) {
		out << stack.stack_[stack.size_ - i - 1] << std::endl;
	}
	return out;
}

template<typename U>
std::istream& operator>>(std::istream& in, Stack<U>& stack) {
	std::cout << "Enter the number of items";
	int number;
	in >> number;
	if (number < 0) { return in; }
	U temp;
	for (int i = 0; i < number; ++i) {
		in >> temp;
		stack.Push(temp);
	}
	return in;
}

template<typename T>
T Stack<T>::Top() const {
	if (size_ > 0) {
		return stack_[size_ - 1];
	}
	return 5;
}

template<typename T>
void Stack<T>::Relocate(size_t new_size) {
	maxsize_ = new_size;
	T* temp = stack_;
	stack_ = new T[maxsize_];
	for (size_t i = 0; i < size_; ++i) {
		stack_[i] = temp[i];
	}
	delete[] temp;
}

template<typename T>
void Stack<T>::Push(T element) {
	if (size_ == maxsize_) {
		Relocate(2 * size_);
	}
	stack_[size_] = element;
	size_++;
}

template<typename T>
void Stack<T>::Pop() {
	if (size_ == 0) { return; }
	size_--;
}

template<typename T>
void Stack<T>::Swap(Stack<T>& other) {
	std::swap(*this, other);
}

template<typename T>
void Stack<T>::Clear() {
	delete[] stack_;
	maxsize_ = 1;
	size_ = 0;
	stack_ = new T[maxsize_];
}
