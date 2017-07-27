#include <cstring>
#include <cstdio>
#include <iostream>

using std::cout;

class CNode;

class CNode {
	private:
		char* key;
		unsigned char height;
		class CNode* left;
		class CNode* right;

		// Установить высоту поддерева 
		void set_height();

		// Правый поворот
		class CNode* rotate_right();

		// Левый поворот
		class CNode* rotate_left();

		// Балансировка узла
		class CNode* balance();

		// Поиск узла с минимальным ключом в поддереве
		class CNode* find_min();

		// Удаление узла с минимальным ключом в поддереве
		class CNode* remove_min();

		// Функция для печати дерева на экран
		char* goto_next(const unsigned char number_of_stage, unsigned int pos);

		// Разность между высотами правой и левой ветвей поддерева
		int bfactor() const;

	public:
		// Получить высоту поддерева
		unsigned char get_height() const;

		// Вставка узла
		class CNode* insert(const char* k);

		// Поиск ключа в дереве
		bool find_key(const char* k);

		// Печать дерева на экран
		void print_tree();

		// Конструктор дерева
		CNode(const char* str = "Default") {
		
			asprintf(&key, "%s", str);
			height = 1;
			left = nullptr;
			right = nullptr;

			cout << "Constructor called.\n";

		}

		// Деструктор дерева
		void destruct_tree() {

			delete[] this->key;

			if (this->right)
				this->right->destruct_tree();

			if (this->left)
				this->left->destruct_tree();

			delete this;

			cout << "Destructor called.\n";
			return;
		}

		// Удаление узла с ключом k
		friend class CNode* remove_node(CNode* node, const char* k);

};
