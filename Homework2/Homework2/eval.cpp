#include <stack>
#include <string>
#include <iostream>
#include <cctype>
#include <cassert>
#include"Map.h"
using namespace std;

bool isope(char in)
{
	switch (in)
	{
	case '-':
	case '+':
	case '*':
	case '/':
		return true;
	default:
		return false;
	}
}


bool syntax(string in)
{
	char tmp = ' ';
	int button = 0;
	stack<char> bracket;
	for (int i = 0; i < in.size(); i++)
	{
		if (in[i] == ' ') continue;
		else if (in[i] == '(') {
			if (button == 1) return false;
			else bracket.push(in[i]);
		}
		else if (in[i] == ')') {
			if (bracket.empty()) return false;
			else if (button == 0) return false;
			else if (tmp == '(') return false;
			else bracket.pop();
		}
		else if (isope(in[i])) {
			if (button == 0) return false;
			else button = 0;
		}
		else if (islower(in[i])) {
			if (button == 1) return false;
			else button = 1;
		}
		else return false;
		tmp = in[i];
	}
	if (button == 0) return false;
	if (!bracket.empty()) return false;
	return true;
}

bool inmap(string in, const Map& values)
{
	for (int i = 0; i < in.size(); i++)
	{
		if (islower(in[i]))
			if (!values.contains(in[i])) return false;
	}
	return true;
}

bool ishigh(char top, char in)
{
	if (top == '(') return false;
	switch (in)
	{
	case '-':
	case '+':
		return true;
	case '*':
	case '/':
		if ((top == '/') || (top == '*')) return true;
		else return false;
	default:
		return false;
	}
}


string convert(string in)
{
	string post;
	stack<char> exp;
	for (int i = 0; i < in.size(); i++)
	{
		if (islower(in[i])) {
			post += in[i];
		}
		else if (in[i] == '(') exp.push(in[i]);
		else if (isope(in[i])) {
			while ((!exp.empty())&& ishigh(exp.top(), in[i]))
			{
				post += exp.top();
				exp.pop();
			}
			exp.push(in[i]);
		}
		else if (in[i] == ')') {
			while (exp.top() != '(')
			{
				post += exp.top();
				exp.pop();
			}
			exp.pop();
		}
	}
	while (!exp.empty())
	{
		post += exp.top();
		exp.pop();
	}
	return post;
}

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
	if (!syntax(infix)) return 1;
	postfix = convert(infix);
	if (!inmap(infix, values)) return 2;
	stack<int> numbers;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (islower(postfix[i])) {
			int tmp; 
			values.get(postfix[i],tmp);
			numbers.push(tmp);
		}
		else if (isope(postfix[i])) {
			int v2 = numbers.top();
			numbers.pop();
			int v1 = numbers.top();
			numbers.pop();
			switch (postfix[i]) {
			case '+':
				numbers.push(v1 + v2);
				break;
			case '-':
				numbers.push(v1 - v2);
				break;
			case '*':
				numbers.push(v1 * v2);
				break;
			case '/':
				if (v2 == 0) return 3;
				numbers.push(v1 / v2);
				break;
			default:
				break;
			}
		}
	}
	result = numbers.top();
	return 0;
}
// Evaluates an integer arithmetic expression
//   If infix is a syntactically valid infix integer expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values map), then postfix is set to the postfix
//   form of the expression; otherwise postfix may or may not be
//   changed, result is unchanged, and the function returns 1.  If
//   infix is syntactically valid but contains at least one lower
//   case letter operand that does not appear in the values map, then
//   result is unchanged and the function returns 2.  If infix is
//   syntactically valid and all its lower case operand letters
//   appear in the values map, then if evaluating the expression
//   (using for each letter in the expression the value in the map
//   that corresponds to it) attempts to divide by zero, then result
//   is unchanged and the function returns 3; otherwise, result is
//   set to the value of the expression and the function returns 0.

int main()
{
	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int  vals[] = { 3,  -9,   6,   2,   4,   1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
		m.insert(vars[k], vals[k]);
	string pf;
	int answer;
	assert(evaluate("a+ e", m, pf, answer) == 0 &&
		pf == "ae+"  &&  answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	// unary operators not allowed:
	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 &&
		pf == "ab*"  &&  answer == 999);
	assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
		pf == "yoau-*+"  &&  answer == -1);
	answer = 999;
	assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
		pf == "oyy-/"  &&  answer == 999);
	assert(evaluate(" a  ", m, pf, answer) == 0 &&
		pf == "a"  &&  answer == 3);
	assert(evaluate("((a))", m, pf, answer) == 0 &&
		pf == "a"  &&  answer == 3);
	assert(evaluate("((a/o))", m, pf, answer) == 0 &&
		pf == "ao/"  &&  answer == 1);
	assert(evaluate("((a/o)+i)+y", m, pf, answer) == 0 &&
		answer == 8);
	assert(evaluate("((a/o)+i)+#", m, pf, answer) == 1 &&
		answer == 8);
	assert(evaluate("((a/o())+i)+y", m, pf, answer) == 1 &&
		answer == 8);
	assert(evaluate("  )", m, pf, answer) == 1 &&
	answer == 8); 
	assert(evaluate("((a/o( ))+i)+y", m, pf, answer) == 1 &&
			answer == 8);
	assert(evaluate("((a/o+()i))+y", m, pf, answer) == 1 &&
		answer == 8);
	assert(evaluate("((a/o(+)i))+y", m, pf, answer) == 1 &&
		answer == 8);
	assert(evaluate("((a/o+(i)))+y", m, pf, answer) == 0 &&
		answer == 8);
	assert(evaluate("((a/o(+i)))+y", m, pf, answer) == 1 &&
		answer == 8);
	assert(evaluate("a/(o-((a+i)))+y", m, pf, answer) == 0 &&
		answer == 1);
	assert(evaluate(")(a-o", m, pf, answer) == 1 &&
		answer == 1);
	assert(evaluate("((a/o(a-a+i+)))a", m, pf, answer) == 1 &&
		answer == 1);
	assert(evaluate(" a   -  o   (   )", m, pf, answer) == 1 &&
		answer == 1);
	cout << "Passed all tests" << endl;
}