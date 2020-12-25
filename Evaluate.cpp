#include "Evaluate.h"

///////////////////////////////////////
// Functions
/////////////////////////////////
bool Evaluate::isOperator(char c) {
	const char* operators = "+-*/%^\0";
	int length = strlen(operators);
	for (int i = 0; i < length; i++) {
		if (operators[i] == c) {
			return true;
		}
	}

	return false;
}

const char* Evaluate::token2text(char token) {
	return soperators[token - KEY];
}

char Evaluate::text2token(const char* text) {
	for (int i = 0; i < sizeof(soperators) / sizeof(*soperators); i++)
		if (strcmp(text, soperators[i]) == 0) return KEY + i;
	return NULL;
}

char* Evaluate::revertStr(char* str) {
	char newstr[8];
	int n = strlen(str);
	for (int i = 0; i < n; i++) {
		newstr[i] = str[n - i - 1];
	}
	newstr[n] = '\0';
	return newstr;
}

char* Evaluate::revertStr(const char* str) {
	char newstr[8];
	int n = strlen(str);
	for (int i = 0; i < n; i++) {
		newstr[i] = str[n - i - 1];
	}
	newstr[n] = '\0';
	return newstr;
}

bool Evaluate::isSOperator(char* str) {
	for (int i = 0; i < sizeof(soperators) / sizeof(*soperators); i++) {
		if (strcmp(str, soperators[i]) == 0) {
			return true;
		}
	}
	return false;
}

bool Evaluate::isSOperator(char token) {
	for (int i = 0; i <= sizeof(soperators) / sizeof(*soperators); i++) {
		if (token == KEY + i) return true;
	}
	return false;
}

int Evaluate::getPrecedence(char c) {
	if (c == '^' || c == SQRT || c == SIN || c == COS || c == TAN)
		return 4;
	if (c == '*' || c == '/' || c == '%')
		return 3;
	if (c == '+' || c == '-')
		return 2;
	return 0;
}

double Evaluate::evaluateSOP(char* txtOperator, int value) {
	double res;
	if (isSOperator(txtOperator)) {
		if (strcmp(txtOperator, "sqrt") == 0)
			res = sqrt(value);
		if (strcmp(txtOperator, "sin") == 0)
			res = sin(value);
		if (strcmp(txtOperator, "cos") == 0)
			res = cos(value);
		if (strcmp(txtOperator, "tan") == 0)
			res = tan(value);
		return(res);
	}
	else
	{
		throw ("Khong tinh duoc!!");
		return 0;
	}
}

void Evaluate::pushOperator2Stack(MyStack<char>* s, char*& postfix, int& j, char token, bool isPrefix) {
	if (!isPrefix) {
		while (!s->isEmpty() && getPrecedence(token) <= getPrecedence(s->topValue())) {
			if (!isSOperator(s->topValue())) {
				postfix[j++] = s->pop();
			}
			else {
				char c = s->pop();

				const char* strtxt = token2text(c);
				int n = strlen(strtxt);
				for (int k = 0; k < n; k++) {
					postfix[j++] = strtxt[k];
				}
			}
		}
	}
	else {

		while (!s->isEmpty() && getPrecedence(token) < getPrecedence(s->topValue())) {
			if (!isSOperator(s->topValue())) {
				postfix[j++] = s->pop();
			}
			else {
				char c = s->pop();
				const char* strtxt = token2text(c);

				int n = strlen(strtxt);
				for (int k = n - 1; k >= 0; k--) {
					postfix[j++] = strtxt[k];
				}
			}
		}
	}
	s->push(token);
}

void Evaluate::appendPostfix(char postfix[], int& j, char token, bool isPrefix) {
	if (!isSOperator(token)) {
		postfix[j++] = token;
	}
	else {
		const char* strtxt = token2text(token);
		char str[8];
		strcpy_s(str, strtxt);

		if (isPrefix)
			strcpy_s(str, revertStr(str));
		for (int k = 0; k < strlen(str); k++) {
			postfix[j++] = str[k];
		}
	}
}

///////////////////////////////////////
// Convert
///////////////////////////////////
void Evaluate::infix2Postfix(char infix[], char postfix[], bool isPrefix) {
	MyStack<char>* s = new MyStack<char>();
	// Duyet tat ca cac ky tu trong infix
	int i = 0;
	int j = 0;
	while (infix[i] != '\0') {
		char token = infix[i];
		// Neu la alpha hoac num
		if (isalnum(token)) {
			if (isalpha(token)) {
				int k = i;
				char txt[8] = "";
				while (isalpha(infix[k])) {
					txt[k - i] = infix[k];
					k++;
				}

				if (isPrefix) {
					strcpy_s(txt, revertStr(txt));
				};

				if (isSOperator(txt)) {
					// Dua phep tinh SQRT vao stack

					token = text2token(txt);
					pushOperator2Stack(s, postfix, j, token, isPrefix);
				}
				else {
					throw "Khong phai SOP nen khong xu li duoc\n";
					return;
				}
				i = k - 1;

			}
			else {
				postfix[j++] = token;
				// Tach cac so voi nhau bang ' '
				if (isOperator(infix[i + 1])) {
					postfix[j++] = ' ';
				}
			}

		}
		else {
			// Neu la dau .
			if (token == '.') {
				postfix[j++] = token;
			}
			else
				// Neu la dau ngoac mo
				if (token == '(') {
					s->push('(');
					// Xet truong hop so am cho Postfix
					if (infix[i + 1] == '-') {
						postfix[j++] = '0';
						postfix[j++] = ' ';
					}
				}

				else {
					// Neu la ngoac dong va data trong stack
					if (token == ')' && !s->isEmpty()) {
						// Xet truong hop so am cho Prefix
						if (isPrefix && infix[i - 1] == '-') {
							postfix[j++] = '0';
						}

						char c;
						while ((c = s->pop()) != '(' && !s->isEmpty())
						{
							appendPostfix(postfix, j, c, isPrefix);
						}
					}
					else {
						// Neu la phep tinh
							// Neu la phep tinh co muc uu tien cao hoac bang
						pushOperator2Stack(s, postfix, j, token, isPrefix);
					}
				}
		}
		i++;
	}
	while (!s->isEmpty())
	{
		char token = s->pop();
		appendPostfix(postfix, j, token, isPrefix);
	}

	// Ket thuc Postfix
	postfix[j] = '\0';
}

void Evaluate::infix2Prefix(char infix[], char prefix[]) {
	int infixLength = strlen(infix);
	// Dao chuoi
	char temp;

	for (int i = 0; i < infixLength / 2; i++) {
		temp = infix[i];
		infix[i] = infix[infixLength - 1 - i];
		infix[infixLength - 1 - i] = temp;
	}

	// Doi ngoac
	for (int i = 0; i < infixLength; i++)
		if (infix[i] == '(')
			infix[i] = ')';
		else if (infix[i] == ')')
			infix[i] = '(';
	// Chuyen sang hau to
	infix2Postfix(infix, prefix, true);

	// Dao nguoc lai
	int prefixLength = strlen(prefix);
	for (int i = 0; i < prefixLength / 2; i++) {
		temp = prefix[i];
		prefix[i] = prefix[prefixLength - 1 - i];
		prefix[prefixLength - 1 - i] = temp;
	}
}
//////////////////////////////
// Evaluate
double Evaluate::evaluatePostfix(char* postfix) {
	MyStack<double>* s = new MyStack<double>();
	char* p = &postfix[0];
	double a, b, res;

	while (*p != '\0') {
		while (*p == ' ') {
			p++;
		}
		if (isalnum(*p)) {
			// Xet truong hop so
			if (isdigit(*p))
			{
				double num = 0;
				while (isdigit(*p)) {
					num *= 10;
					num += (double)*p - '0';
					p++;
				}
				// Xet phan thap phan
				if (*p == '.') {
					p++;
					int n = 0;
					while (isdigit(*p)) {
						n++;
						num += ((double)*p - '0') * pow(10, -n);
						p++;
					}
				}
				p--;
				s->push(num);
			}
			// Xet la chu
			else
			{
				int i = 0;
				char txtOperator[10];
				txtOperator[i++] = *p;
				while (isalpha(*(p + 1))) {
					p++;
					txtOperator[i++] = *p;
				}

				txtOperator[i] = '\0';
				res = evaluateSOP(txtOperator, s->pop());
				s->push(res);
			}
		}
		// xet la toan tu
		else
		{
			a = s->pop();
			b = s->pop();

			switch (*p)
			{
			case '+':
				res = b + a;
				break;
			case '-':
				res = b - a;
				break;
			case '*':
				res = b * a;
				break;
			case '/':
				res = b / a;
				break;
			case '%':
				res = (int)b % (int)a;
				break;
			case '^':
				res = pow(b, a);
				break;
			default:
				throw ("\nLoi ky tu");
				return 0;
			}
			s->push(res);
		}
		p++;
	}
	res = s->pop();
	return res;
}

double Evaluate::evaluatePrefix(char* prefix)
{
	MyStack<double>* s = new MyStack<double>();
	char* p;
	double a, b, res;
	int prefixLength = strlen(prefix);
	p = &prefix[prefixLength - 1];

	while (p >= &prefix[0])
	{

		// Xet truong hop dau " "
		while (*p == ' ')
		{
			p--;
		}

		if (isalnum(*p)) {
			// Xet truong hop so
			if (isdigit(*p))
			{
				int i = 0;
				int product;
				double num = 0;
				// Kiem tra xem co phai so thap phan
				char* p1 = p;
				bool isReal = false;
				int nAfterDot = 0;
				while (!isOperator(*p1) && *p1 != ' ') {
					if (*p1 == '.') {
						isReal = true;
						break;
					}
					nAfterDot++;
					p1--;
				};

				// Phan thap phan
				if (isReal) {
					int n = nAfterDot;
					while (isdigit(*p)) {
						num += ((double)*p - '0') * pow(10, -n);
						n--;
						p--;
					}
					p--;
				}

				while (isdigit(*p)) {
					product = pow(10, i++);
					num += product * ((double)*p - '0');
					p--;
				}

				p++;
				s->push(num);
			}
			// Xet la chu
			else
			{
				int i = 0;
				char txtOperator[8];
				txtOperator[i++] = *p;
				while (p > & prefix[0] && isalpha(*(p - 1))) {
					p--;
					txtOperator[i++] = *p;
				}

				txtOperator[i] = '\0';
				strcpy_s(txtOperator, revertStr(txtOperator));
				res = evaluateSOP(txtOperator, s->pop());
				s->push(res);
			}
		}
		// xet la toan tu
		else
		{
			a = s->pop();
			b = s->pop();

			switch (*p)
			{
			case '+':
				res = a + b;
				break;
			case '-':
				res = a - b;
				break;
			case '*':
				res = a * b;
				break;
			case '/':
				res = (double)a / b;
				break;
			case '%':
				res = (int)a % (int)b;
				break;
			case '^':
				res = pow(a, b);
				break;
			default:
				printf("\nLoi ky tu");
				return 0;
			}
			s->push(res);
		}
		p--;
	}
	res = s->pop();
	return res;
}

double Evaluate::calc(char exp[])
{
	char post[50];
	infix2Postfix(exp, post);
	double res = evaluatePostfix(post);
	return res;
}

double Evaluate::calc(const char* exp) {
	char temp[50];
	strcpy_s(temp, exp);
	return calc(temp);
}
