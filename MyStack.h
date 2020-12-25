#pragma once
#include <stdio.h>
#define MAX_STACK 100
#define MAX 100

template<typename T>
class MyStack
{
private:
	T* data;
	int top;

public:
	MyStack();
	virtual ~MyStack();
	void init();
	void setTop(int n);
	int isEmpty();
	T topValue();
	void push(T data);
	T pop();
};



