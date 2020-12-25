#pragma once
#include "MyStack.h"


template<typename T>
MyStack<T>::MyStack() {
	top = -1;
	data = new T[MAX_STACK];
}

template<typename T>
MyStack<T>::~MyStack()
{
	
};

template<typename T>
void MyStack<T>::init() {
	top = -1;
}

template<typename T>
void MyStack<T>::setTop(int n) {
	top = n;
}

template<typename T>
int MyStack<T>::isEmpty() {
	return (top == -1) ? 1 : 0;
}

template<typename T>
T MyStack<T>::topValue() {
	return data[top];
}

template<typename T>
void MyStack<T>::push(T n) {
	if (top == MAX_STACK - 1) {
		printf("Stack is full");
		return;
	}

	top++;
	data[top] = n;
}

template<typename T>
T MyStack<T>::pop() {
	T ret = NULL;
	if (top == -1) {
		printf("Stack is empty");
	}
	else {
		ret = data[top--];
	}
	return ret;
}

