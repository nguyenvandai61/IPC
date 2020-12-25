#pragma once
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "MyStack.cpp"
#define KEY 101

class Evaluate
{
private:
	const char* soperators[4] = { "sqrt", "sin", "cos", "tan" };

	enum soperator {
		SQRT = KEY,
		SIN,
		COS,
		TAN,
	};

	bool isOperator(char c);
	const char* token2text(char token);
	char text2token(const char* text);
	char* revertStr(char* str);
	char* revertStr(const char* str);
	bool isSOperator(char* str);
	bool isSOperator(char token);
	int getPrecedence(char c);
	double evaluateSOP(char* txtOperator, int value);
	void pushOperator2Stack(MyStack<char>* s, char*& postfix, int& j, char token, bool isPrefix = false);
	void appendPostfix(char postfix[], int& j, char token, bool isPrefix = false);
	void infix2Postfix(char infix[], char postfix[], bool isPrefix = false);
	void infix2Prefix(char infix[], char prefix[]);
	double evaluatePostfix(char* postfix);
	double evaluatePrefix(char* prefix);


public:
	double calc(char exp[]);
	double calc(const char* exp);
};

// int main(int argc, char **argv) {
// 	Evaluate* eval = new Evaluate();
// 	printf("Bieu thuc %s", argv[1]);
// 	printf("\nCo ket qua: %lf", eval->calc(argv[1]));
// }
