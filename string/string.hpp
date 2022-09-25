#pragma once

#include <cstring>
#include <cassert>
#include <iostream>

namespace qwq {
	class string {
	public:
		// type of iterator
		typedef char* iterator;
		typedef const char* const_iterator;
		static const size_t npos = -1;

		friend std::ostream& operator<<(std::ostream& out, string& str);

		friend std::istream& operator>>(std::istream& in, string& str);

		// --- Construct string object ----------------------------------

			// default (1)
		string()
			: _str(new char[initCapa + 1])
			, _capacity(initCapa)
			, _size(0)
		{
			_str[0] = '\0';
		}

		// copy (2)
		string(const string& str) {
			_str = new char[str._capacity + 1];
			_size = str._size;
			_capacity = str._capacity;
			strcpy(_str, str._str);
		}

		// substring (3)
		string(const string& src, size_t pos, size_t len = npos) {
			assert(pos <= src._size);
			_capacity = src._size - pos;
			if (len < _capacity)
				_capacity = len;
			_str = new char[_capacity + 1];
			_size = _capacity;
			size_t i;
			for (i = 0; i < _capacity; ++i) {
				_str[i] = src._str[pos + i];
			}
			_str[i] = '\0';
		}

		// from c-string (4)
		string(const char* src) {
			_size = strlen(src);
			_capacity = allocSize(_size);
			_str = new char[_capacity + 1];
			strcpy(_str, src);
		}

		// --- String destructor ----------------------------------------

		~string() {
			delete[] _str;
		}

		// --- String assignment ----------------------------------------

			// string = string
		string& operator=(const string& src) {
			if (this != &src) {
				delete[] _str;
				_str = new char[src._capacity + 1];
				_capacity = src._capacity;
				_size = src._size;
				strcpy(_str, src._str);
			}
			return *this;
		}

		// string = char*
		string& operator=(const char* src) {
			delete[] _str;
			_size = strlen(src);
			_capacity = allocSize(_size);
			_str = new char[_capacity + 1];
			strcpy(_str, src);
			return *this;
		}

		// string = char
		string& operator=(char ch) {
			delete[] _str;
			_size = 1;
			_capacity = initCapa;
			_str = new char[initCapa + 1];
			_str[0] = ch;
			_str[1] = '\0';
			return *this;
		}

		// --- Iterators ------------------------------------------------

		iterator begin() {
			return _str;
		}
		iterator end() {
			return _str + _size;
		}

		const_iterator begin() const {
			return _str;
		}
		const_iterator end() const {
			return _str + _size;
		}

		// --- Capacity -------------------------------------------------

		size_t size() {
			return _size;
		}
		size_t length() {
			return _size;
		}
		size_t capacity() {
			return _capacity;
		}

		void reserve(size_t n = 0) {
			if (n > _capacity) {
				_capacity = allocSize(n);
				char* tmp = new char[_capacity + 1];
				_str[_size] = '\0';
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
			}
		}

		void resize(size_t n, char c = '\0') {
			if (n > _size) {
				reserve(n);
				while (_size < n) {
					_str[_size++] = c;
				}
				_str[n] = '\0';
			}
			else {
				_str[n] = '\0';
			}
		}

		void clear() {
			_str[0] = '\0';
			_size = 0;
		}

		// --- Modifiers ------------------------------------------------

		string& operator+=(const string& str) {
			append(str);
			return *this;
		}

		string& operator+=(const char* str) {
			append(str);
			return *this;
		}

		string& operator+=(char c) {
			reserve(_size + 1);
			_str[_size++] = c;
			_str[_size] = '\0';
			return *this;
		}

		void push_back(char c) {
			if (_size == _capacity) {
				reserve(_capacity + 1);
			}
			_str[_size++] = c;
			_str[_size] = '\0';
		}

		void pop_back() {
			assert(_size > 0);
			_str[--_size] = '\0';
		}

		void append(const string& str) {
			char* cur = _str + _size;
			_size += str._size;
			reserve(_size);
			for (int i = 0; i < str._size; ++i)
				*cur++ = str._str[i];
			*cur = '\0';
		}

		void append(const char* str) {
			size_t len = strlen(str);
			reserve(_size + len);
			char* cur = _str + _size;
			_size += len;
			strcpy(cur, str);
		}

		void append(size_t n, char c) {
			reserve(_size + n);
			while (n--) {
				_str[_size++] = c;
			}
			_str[_size] = '\0';
		}

		string& insert(size_t pos, const string& str) {
			assert(pos <= _size);
			reserve(_size + str._size);
			for (int i = _size - 1; i >= pos; --i) {
				_str[i + str._size] = _str[i];
			}
			for (int i = 0; i < str._size; ++i) {
				_str[i + pos] = str._str[i];
			}
			_size += str._size;
			_str[_size] = '\0';
			return *this;
		}

		string& insert(size_t pos, const char* s) {
			assert(pos <= _size);
			size_t len = strlen(s);
			reserve(_size + len);
			for (int i = _size - 1; i >= pos; --i) {
				_str[i + len] = _str[i];
			}
			for (int i = 0; i < len; ++i) {
				_str[i + pos] = s[i];
			}
			_size += len;
			_str[_size] = '\0';
			return *this;
		}

		string& insert(size_t pos, size_t n, char c) {
			assert(pos <= _size);
			reserve(_size + n);
			for (int i = _size - 1; i >= pos; --i) {
				_str[i + n] = _str[i];
			}
			for (int i = 0; i < n; ++i) {
				_str[i + pos] = c;
			}
			_size += n;
			_str[_size] = '\0';
			return *this;
		}

		string& erase(size_t pos = 0, size_t len = npos) {
			assert(pos < _size);
			if (len == npos || pos + len >= _size) {
				_str[pos] = '\0';
				_size = pos;
			}
			else {
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
			return *this;
		}

		// --- String operations ----------------------------------------

		const char* c_str() const {
			return _str;
		}

		size_t find(char c, size_t pos = 0) const {
			assert(pos < _size);
			while (pos < _size) {
				if (_str[pos] == c)
					return pos;
			}
			return npos;
		}

		size_t find(const char* sub, size_t pos = 0) const {
			assert(sub);
			assert(pos < _size);
			const char* ptr = strstr(_str + pos, sub);
			if (ptr)
				return ptr - _str;
			else
				return npos;
		}

		string substr(size_t pos = 0, size_t len = npos) const {
			assert(pos < _size);
			size_t realLen = (len == npos || pos + len > _size) ? _size - pos : len;
			string sub;
			sub.reserve(realLen);
			sub._size = realLen;
			for (size_t i = 0; i < realLen; ++i)
				sub._str[i] = _str[pos + i];
			sub._str[sub._size] = '\0';
			return sub;
		}

		// --- Element access -------------------------------------------

		char& operator[](size_t pos) {
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos) const {
			assert(pos < _size);
			return _str[pos];
		}

		// --- Non-member function overloads ------------------------------

		// relational operators
		bool operator>(string& str) {
			return strcmp(_str, str._str) > 0;
		}
		bool operator<(string& str) {
			return strcmp(_str, str._str) < 0;
		}
		bool operator==(string& str) {
			return strcmp(_str, str._str) == 0;
		}
		bool operator>=(string& str) {
			return *this > str || *this == str;
		}
		bool operator<=(string& str) {
			return *this < str || *this == str;
		}
		bool operator!=(string& str) {
			return !(strcmp(_str, str._str) == 0);
		}

	private:
		// private member variable
		char* _str;
		size_t _size;
		size_t _capacity;
		
		// private member function
		const static int initCapa = 15;
		size_t allocSize(size_t n) {
			size_t ret = initCapa + 1;
			while (ret - 1 < n) {
				ret *= 2;
			}
			return ret - 1;
		}
	};
	
	std::ostream& operator<<(std::ostream& out, string& str) {
		for (int i = 0; i < str._size; ++i) {
			out << str._str[i];
		}
		return out;
	}
	std::istream& operator>>(std::istream& in, string& str) {
		str.clear();
		char ch = in.get();
		while (ch != ' ' && ch != '\n') {
			str += ch;
			ch = in.get();
		}
		//str._str[str._size] = '\0';
		return in;
	}
}