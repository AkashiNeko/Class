#define _CRT_SECURE_NO_WARNINGS

#define _MY_STRING_TEST_

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#ifdef _MY_STRING_TEST_
#include "string.hpp"
using qwq::string;
#else
using std::string;
#endif

int main() {
	// test
	string s = "Hello World";
	cout << s;
	return 0;
}
