#pragma once

#include "cpp.h"

template <typename T>
struct node
{
	T obj;
	node<T>* fLink;
	node<T>* bLink;

	static node<T> create(T& _obj = NULL, node<T>* _bLink = nullptr) {
		n = (node<T>*) kMalloc(sizeof(node<T>));
		if (_obj == NULL) {
			T o;
			n->o;
		}
		else
			n->obj = _obj;
		n->fLink = n;
		if (_bLink == nullptr)
			n->bLink = n;
		else
			n->bLink = _bLink;
		return n;
	};
};

//Here vector is a single linked list of which last node fLink points to itself
template <typename T>
class vector
{
public:
	vector() {
		firstNode = node::create();
		lastNode = firstNode;
		length = 1;
	};
	bool Append(T& obj) {
		node<T>* n = node::create(obj, lastNode);
		lastNode = n;
		length++;
	};
	T Pop(unsigned int index = length) {
		T ret;
		if (index + 1 == length) {
			lastNode->bLink->fLink = lastNode->bLink;
			ret = lastNode->obj;
			kDelete(lastNode); 
			return ret;
		}
		node<T>* curNode = nullptr;
		if (index < length / 2) {
			curNode = firstNode;
			int t = 0;
			while (t != index) {
				curNode = curNode->fLink;
				t++;
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
		kDelete(curNode);
		return ret;
	};
	void Dispose() {
		node<T>* curNode = firstNode;
		do {
			auto nextNode = curNode->fLink;
			kDelete((void*)curNode);
			curNode = nextNode;
		} while (curNode->fLink != curNode);

		kDelete(this);
	};

	T operator[](int i) {
		if (i > length)
			return lastNode;

		int t = 0;
		node<T>* pCurNode = firstNode;
		do {
			pCurNode = pCurNode->fLink;
			t++;
		} while (t < i);

		return *pCurNode;
	};
	T& operator[](int i) {
		if (i > length)
			return lastNode;

		int t = 0;
		node<T>* pCurNode = firstNode;
		do {
			pCurNode = pCurNode->fLink;
			t++;
		} while (t < i);

		return *pCurNode;
	};
private:
	node<T>* firstNode; //node index 0
	node<T>* lastNode;
	int length;
};

