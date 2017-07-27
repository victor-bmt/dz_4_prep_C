#include "tree.h"
#include <cstring>
#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

unsigned char CNode::get_height() const {

	return (this ? height : 0);
}

void CNode::set_height() {

	unsigned char h_left = left->get_height();
	unsigned char h_right = right->get_height();

	height = (h_left > h_right ? h_left : h_right) + 1;

	return;
}

class CNode* CNode::rotate_right() {

	CNode* q = this->left;
	this->left = q->right;
	q->right = this;

	this->set_height();
	q->set_height();

	return q;
}

class CNode* CNode::rotate_left() {

	CNode* p = this->right;
	this->right = p->left;
	p->left = this;

	this->set_height();
	p->set_height();

	return p;
}

class CNode* CNode::balance() {

	this->set_height();

	if ((this->bfactor()) == 2) {
		if ((right->bfactor()) < 0)
			this->right = right->rotate_right();
		return (this->rotate_left());
	}

	if ((this->bfactor()) == -2) {
		if ((left->bfactor()) > 0)
			this->left = left->rotate_left();
		return (this->rotate_right());
	}

	// Поддерево уже сбалансировано
	return this;
}

int CNode::bfactor() const {

	return (right->get_height() - left->get_height());
}

class CNode* CNode::insert(const char* k) {

	if (!strcmp(k, this->key)) {

		cout << "Attempt to create existing node with key '"
			<< k << "'\n";
		
		return this;
	}

	if (strcmp(k, this->key) > 0) {
		if (!(this->right)) {

			CNode* pDummy = new CNode(k);
			this->right = pDummy;
			return (this->balance());
		}

		this->right = right->insert(k);
	}

	else {
		if (!(this->left)) {

			CNode* pDummy = new CNode(k);
			this->left = pDummy;
			return (this->balance());
		}

		this->left = left->insert(k);
	}

	return (this->balance());
}

class CNode* remove_node(CNode* node, const char* k) {

	if (!node) {

		cout << "Attempt to remove unexisting node with key '"
			<< k << "'\n";

		return nullptr;
	}

	if (strcmp(k, node->key) > 0)
		node->right = remove_node(node->right, k);

	else if (strcmp(k, node->key) < 0)
		node->left = remove_node(node->left, k);

	else {

		CNode* q = node->left;
		CNode* r = node->right;

		if (!r) {
		
			delete[] node->key;
			delete node;

			return q;
		}

		CNode* min = r->find_min();
		min->right = r->remove_min();
		min->left = q;

		delete[] node->key;
		delete node;

		return min->balance();
	}

	return node->balance();
}

class CNode* CNode::find_min() {

	return (this->left ? left->find_min() : this);
}

class CNode* CNode::remove_min() {

	if (!(this->left))
		return this->right;

	this->left = left->remove_min();

	return this->balance();
}

bool CNode::find_key(const char* k) {

	if (!this)
		return false;

	if (!strcmp(k, this->key))
		return true;

	if (strcmp(k, this->key) > 0)
		return right->find_key(k);

	else
		return left->find_key(k);
}

void CNode::print_tree() {

	unsigned char height = this->get_height();

	// Число элементов в текущей строке
	unsigned int num = 1;

	for (unsigned char i = 1; i <= height; ++i) {
		// Текущая позиция
		unsigned int pos = 0;

		cout << " ";

		while (pos < num) {

			char* cur_key = goto_next(i, pos);

			if (cur_key)
				cout << cur_key << "\t";

			else
				cout << "N\t";

			delete[] cur_key;
			cur_key = nullptr;

			++pos;
		}

		num *= 2;
		cout << endl << endl;
	}
}

char* CNode::goto_next(const unsigned char number_of_stage, unsigned int pos) {

	unsigned int max = 1;
	CNode* pDummy = this;

	for (unsigned char i = 1; i < number_of_stage; ++i)
		max *= 2;

	for (unsigned char i = 1; i < number_of_stage; ++i) {

		if (pos < (max / 2)) {

			if (pDummy->left)
				pDummy = pDummy->left;
			else
				return 0;
		}

		else {

			if (pDummy->right)
				pDummy = pDummy->right;
			else
				return 0;
		}

		max /= 2;
		pos %= max;
	}

	char* next_key = nullptr;
       	asprintf(&next_key, "%s", pDummy->key);

	return next_key;
}
