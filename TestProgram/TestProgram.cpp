
#include <iostream>
#include <Windows.h>
#include <winternl.h>


template <typename T>
struct node
{
	T obj;
	node<T>* fLink;
	node<T>* bLink;

	static node<T>* create(T* _obj = nullptr, node<T>* _bLink = nullptr) {
		if (_obj == nullptr) return nullptr;
		auto n = (node<T>*) malloc(sizeof(node<T>));
		if (n == nullptr) return nullptr;

		n->obj = *_obj;

		n->fLink = n;
		if (_bLink == nullptr)
			n->bLink = n;
		else
			n->bLink = _bLink;
		return n;
	};
};

//Here vector is a single linked list of which last node fLink points to itself
template <class T>
class vector
{
public:
	//Constructors - Destructors
	vector() {
		firstNode = (node<T>*)this;
		lastNode = firstNode;
		length = 0;
	}
	vector(T& obj) {
		firstNode = node<T>::create(&obj);
		lastNode = firstNode;
		length = 1;
	};
	vector(T obj) {
		firstNode = node<T>::create(&obj);
		lastNode = firstNode;
		length = 1;
	};
	//This will dispose of every node, but the vec obj must be disposed of manually
	void Dispose() {
		node<T>* curNode = firstNode;
		for (int i = 0; i < length; i++) {
			auto nextNode = curNode->fLink;
			delete((void*)curNode);
			curNode = nextNode;
		}
	};

	//Methods
	int Length() {
		return length;
	}
	bool Append(T& obj) {
		node<T>* n = node<T>::create(&obj, lastNode);
		lastNode = n;
		if (firstNode == (node<T>*)this)
			firstNode == lastNode;
		length++;
		return true;
	};
	template <class ... C>
	bool emplace_back(C ... c) {
		T obj(c ...);
		node<T>* n = node<T>::create(&obj, lastNode);
		if (lastNode == firstNode)
			lastNode = n;
		n->bLink = lastNode;
		lastNode->fLink = n;
		lastNode = n;
		n->fLink = n;

		if ((size_t)firstNode == (size_t)this)
			firstNode = lastNode; 
		if (firstNode->fLink == firstNode) {
			firstNode->fLink = lastNode;
		}
		length++;
		return true;
	}
	T Pop(unsigned int index = length) {
		T ret;
		if (index + 1 == length) {
			lastNode->bLink->fLink = lastNode->bLink;
			lastNode = lastNode->bLink;
			return lastNode->obj;
		}
		node<T>* curNode = nullptr;
		if (index < length / 2) {
			curNode = firstNode;
			int t = 0;
			while (t != index) {
				curNode = curNode->fLink;
				t++;
			}
			if (!t) {
				firstNode = firstNode->fLink;
				firstNode->fLink->bLink = firstNode->fLink;
			}
		}
		else {
			curNode = lastNode;
			int t = length - 1;
			while (t != index) {
				curNode = curNode->bLink;
				t--;
			}

		}
		ret = curNode->obj;
		curNode->bLink->fLink = curNode->fLink;
		curNode->fLink->bLink = curNode->bLink;
		delete(curNode);
		length--;
		return ret;
	};

	//Operators
	const T& operator[](int i) const {
		return BracketOverload(i);
	};
	T& operator[](int i) {
		return BracketOverload(i);
	};
	vector<T>& operator =(vector<T>& rhs) {
		this->firstNode = rhs->firstNode;
		this->lastNode = rhs->lastNode;
		this->length = rhs->length;

		return *this;
	}
private:
	//Private functions used by overloads
	T& BracketOverload(int i) {
		if (i > length)
			return lastNode->obj;

		node<T>* curNode;
		if (i < length / 2) {
			curNode = firstNode;
			int t = 0;
			while (t != i) {
				curNode = curNode->fLink;
				t++;
			}
		}
		else {
			curNode = lastNode;
			int t = length - 1;
			while (t != i) {
				curNode = curNode->bLink;
				t--;
			}

		}

		return curNode->obj;
	};

	//Variables
	node<T>* firstNode;
	node<T>* lastNode;
	int length;
};

template <class T, class Y>
struct DictionaryNode {
	T key;
	Y value;

	DictionaryNode(T& k, Y& v) {
		key = k;
		value = v;
	}
};

template <class T, class Y>
class Dictionary {
private:
	vector<DictionaryNode<T, Y>> internalVector;
public:
	Dictionary() {
		//new (&internalVector) vector<DictionaryNode<T, Y>>;
	};
	~Dictionary() {
		internalVector.Dispose();
	};
	void Append(T key, Y value) {
		internalVector.emplace_back(key, value);
	};
	const Y& operator [](const T&& key) const {
		for (size_t i = 0; i < internalVector.Length(); i++) {
			auto pNode = &internalVector[i];
			if (pNode->key == key)
				return pNode->value;
		}
		return internalVector[0];
	}
	Y& operator [](const T&& key) {
		for (size_t i = 0; i < internalVector.Length(); i++) {
			auto pNode = &internalVector[i];
			if (pNode->key == key)
				return pNode->value;
		}
		return internalVector[0].value;
	}
};
void mbstowcs(wchar_t* dst, char* src, size_t len);
void wcstombs(char* dst, wchar_t* src, size_t len);

//This class supposes it is being initialized from a cstring const char* (for now at least)
struct string {
public:
	int len;
	const char* pBuffer;

	string();
	//Constructors-Desctructors
	string(const char* pString);
	string(string& obj);
	static string* create(const char* pString);
	~string();
	void Dispose(); //c# style memory free
	//Other functions 
	const char* c_str();
	UNICODE_STRING unicode();
	string* substring(int index);
	string* substring(int index, int length);
	int last_of(char to_find);
	//Operators
	string& operator+(const char* LpCStr) {
		if (LpCStr == nullptr)
			return *this;

		auto length = len + (int)strlen(LpCStr);
		auto buffer = (char*)malloc((size_t)length + 1);
		if (pBuffer == nullptr) return *this;
		ZeroMemory((void*)buffer, (size_t)length + 1);
		memcpy((void*)buffer, pBuffer, len);
		strcat((char*)buffer, LpCStr);
		pBuffer = buffer;
		len = length;

		return *this;
	};
	void operator=(const string& obj) {
		if (&obj == this)
			return;
		Dispose();
		pBuffer = (char*)malloc((size_t)obj.len + 1);
		ZeroMemory((void*)pBuffer, (size_t)obj.len + 1);
		memcpy((void*)pBuffer, obj.pBuffer, obj.len);
		len = obj.len;
	};
};

//Length without null terminator
void mbstowcs(wchar_t* dst, char* src, size_t len)
{
	for (size_t i = 0; i < len + 1; i++) {
		*(char*)&dst[i] = src[i];
		*((char*)&dst[i] + 1) = 0x00;
	}
}

void wcstombs(char* dst, wchar_t* src, size_t len) {
	for (size_t i = 0; i < len + 1; i++) {
		dst[i] = *(char*)&src[i];
	}
}

string::string()
{
	len = 0;
	pBuffer = nullptr;
}

string::string(const char* pString) {
	len = strlen(pString);
	pBuffer = (char*)malloc((size_t)len + 1);
	strcpy((char*)pBuffer, pString);
}

string::string(string& obj)
{
	len = obj.len;
	pBuffer = obj.pBuffer;
}

void string::Dispose()
{
	if (pBuffer != nullptr) {
		delete((void*)pBuffer);
		pBuffer = nullptr;
	}
}

string* string::create(const char* pString)
{
	auto pNewString = (string*)malloc((size_t)sizeof(string));
	pNewString->len = strlen(pString);
	pNewString->pBuffer = (char*)malloc((size_t)pNewString->len + 1);
	strcpy((char*)pNewString->pBuffer, pString);
	return pNewString;
}

string::~string()
{
	Dispose();
}

UNICODE_STRING string::unicode()
{
	UNICODE_STRING retValue;
	wchar_t buf[255];
	mbstowcs(buf, (char*)pBuffer, (size_t)len + 1);
	return retValue;
}

string* string::substring(int index)
{
	char* char_arr = (char*)malloc((size_t)len - index + 1);
	memcpy(char_arr, pBuffer + index, (size_t)len - index);
	char_arr[len - index] = 0;
	string* pRetValue = string::create(char_arr);

	delete(char_arr);
	return pRetValue;
}

string* string::substring(int index, int length)
{
	char* char_arr = (char*)malloc((size_t)len - index + 1);
	if (len > index + length) {
		memcpy(char_arr + index, pBuffer, (size_t)len - index);
		char_arr[len - index + 1] = 0;
	}
	else {
		memcpy(char_arr, pBuffer, length);
		char_arr[length + 1] = 0;
	}
	string* pRetValue = string::create(char_arr);
	delete(char_arr);
	return pRetValue;
}

int string::last_of(char to_find)
{
	for (int i = len; i > 0; i--) {
		if (pBuffer[i] == to_find)
			return i;
	}
	return 0;
}

const char* string::c_str() {
	return pBuffer;
}

int main()
{
	string mystr("Hello ");
	string mystr1 = mystr + "world!";
	std::cout << mystr1.c_str();
    return 0;
}