#include "tree.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using std::cout;
using std::endl;
using std::ifstream;

// Обрабатывает очередной кБ, считанный из файла и обращается к библиотеке tree
// Первая версия используется по умолчанию, вторая - при обработке последнего слова
int process_line(CNode** ppRoot, const char* str, unsigned int& start);

// Вставляет новый элемент, удаляет или ищет узел в дереве
static class CNode* process_tree(CNode* pRoot, const char ch, const char* str);

int main(int argc, char* argv[]) {

	if (argc != 2) {

		cout << "Incorrect input! Enter './a.out (file.txt)'\n";
		return 1;
	}

	ifstream fp(argv[1]);

	if (!fp.is_open()) {

		cout << "File is not found!\n";
		return 2;
	}

	int next_char = fp.peek();

	if (next_char == EOF) {

		cout << "File is empty!\n";
		fp.close();
		return 3;
	}

	if ((next_char != static_cast<int>('+')) && (next_char != static_cast<int>('-')) && (next_char != static_cast<int>('?'))) {

		cout << "Incorrect input file!\n";
		fp.close();
		return 3;
	}

	char line[1024] = { 0 };
	unsigned int start = 0;

	CNode* pRoot = new CNode;

	while (!fp.eof()) {

		fp.seekg(start);

		fp.read(line, sizeof(line) - 1);
		//int flag = 0;
		int flag = process_line(&pRoot, line, start);
		
		if (flag == -1) {

			fp.close();
			cout << "Incorrect input file!\n";
			return 3;
		}

		if (flag == -2) {
			fp.close();

			cout << "Tree was removed. Create new tree.\n";

			return 4;
		}
	}

	fp.close();

	pRoot->print_tree();

	pRoot->destruct_tree();

	return 0;
}

int process_line(CNode** ppRoot, const char* str, unsigned int& start) {
	if ((!ppRoot) || (!(*ppRoot)))
		return -2;

	int len = strlen(str);
	if (len == 1)
		return 0;

	unsigned int word_count = 0;
	int word_start = 0;
	int word_end = 0;

	// Пропускаем все разделители в начале строки
	while (isspace(str[word_start++])) {

		++start;
	}
	--word_start;

	for (int i = word_start; i < len - 1; ++i)
		if ((isspace(str[i + 1])) && (!isspace(str[i])))
			++word_count;

	if (!word_count)
		return -1;
	
	for (unsigned int i = 0; i < word_count; ++i) {
		
		while (isspace(str[word_start++])) {

			++start;
		}
		--word_start;

		char ch = str[word_start++];
		++start;
		if ((ch != '+') && (ch != '-') && (ch != '?'))
			return -1;

		word_end = word_start;
		while (!isspace(str[word_end++])) {

			++start;
		}
		--word_end;
		++start;

		char word[word_end - word_start + 1] = { 0 };

		// Посимвольно копируем слово в буфер
		for (int i = word_start; i < word_end; ++i) {

			word[i - word_start] = str[i];
		}
		word[word_end - word_start] = '\0';

		word_start = word_end + 1;

		*ppRoot = process_tree(*ppRoot, ch, word);
		
		if (!(*ppRoot))
			return -2;
	}

	return 0;
}

static class CNode* process_tree(CNode* pRoot, const char ch, const char* word) {

	if (!pRoot)
		return nullptr;

	if (ch == '+') {
		pRoot = pRoot->insert(word);
	}

	else if (ch == '?') {
		if (pRoot->find_key(word))
			cout << "Node with key '"
				<< word << "' is found.\n";
		else 
			cout << "Node with key '"
				<< word << "' is not found.\n";
	}

	else if (ch == '-') {
		pRoot = remove_node(pRoot, word);
	}

	return pRoot;
}
