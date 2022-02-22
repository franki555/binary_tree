#pragma once
#define TREES_H
#ifdef TREES_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>


template <class T>
class tree
{
public:
	tree() : pParent(nullptr), pLeft(nullptr), pRight(nullptr), pObject(nullptr), pIndex(nullptr) {}
	~tree()
	{
		if (this->pLeft != nullptr)
		{
			delete this->pLeft;
			this->pLeft = nullptr;
		}
		if (this->pRight != nullptr)
		{
			delete this->pRight;
			this->pRight = nullptr;
		}
		if (this->pObject != nullptr)
		{
			delete this->pObject;
			this->pObject = nullptr;
		}
		if (this->pIndex != nullptr)
		{
			delete this->pIndex;
			this->pIndex = nullptr;
		}
	}
	void insert(int _index, T _object)
	{
		tree<T>* null = nullptr;	// ДЛЯ СРАВНЕНИЯ ТИПОВ
		T* null_t = nullptr;

		tree<T>* node = this;
		while (node != nullptr)
		{
			if (node->getObject() == null_t || *node->getIndex() == _index)
			{
				node->setIndex(_index);
				node->setObject(_object);
				node = nullptr;
			}
			else
			{
				if (_index < *node->getIndex())
				{
					if (node->getLeft() == null)
					{
						node->setLeft(new tree<T>());
						node->getLeft()->setParent(node);
					}
					node = node->getLeft();
				}
				else if (_index > *node->pIndex)
				{
					if (node->getRight() == null)
					{
						node->setRight(new tree<T>());
						node->getRight()->setParent(node);
					}
					node = node->getRight();
				}
			}
		}
	}
	T search(int _index)
	{
		if (this->pIndex == nullptr)
			throw - 1;
		tree<T>* node = new tree<T>(*this);
		while (1)
		{
			if (node == nullptr)
				throw - 1;
			else if (_index == *node->getIndex())
				return *node->getObject();
			else if (_index < *node->getIndex())
				node = node->getLeft();
			else if (_index > *node->getIndex())
				node = node->getRight();
		}
	}
	void remove(int _index)
	{
		if (this->pIndex == nullptr)	// ЕСЛИ НЕТ ЭЛЕМЕНТОВ
			throw - 1;
		if (this->isLeaf())
		{
			delete this->pObject;
			this->pObject = nullptr;
			delete this->pIndex;
			this->pIndex = nullptr;
		}
		else
		{
			tree<T>* node = this;
			while (1)	// ПОИСК УЗЛА С ИНДЕКСОМ _index
			{
				if (node == nullptr)
					throw -1;
				else if (_index == *node->getIndex())
					break;
				else if (_index < *node->getIndex())
					node = node->getLeft();
				else if (_index > *node->getIndex())
					node = node->getRight();
			}

			if (node->isLeaf())		// ЕСЛИ ЛИСТ
			{
				if (*node->getIndex() < *node->getParent()->getIndex())
					node->getParent()->setLeft(nullptr);
				else if (*node->getIndex() > *node->getParent()->getIndex())
					node->getParent()->setRight(nullptr);
			}

			else if (node->getLeft() == nullptr && node->getRight() != nullptr)
			{
				if (node->getParent() != nullptr)
				{
					if (*node->getIndex() < *node->getParent()->getIndex())
					{
						node->getParent()->setLeft(node->getRight());
						node->getRight()->setParent(node->getParent());			//  |
						node->setRight(nullptr);								//  0 <-delete
					}															//  |
					if (*node->getIndex() > *node->getParent()->getIndex())		//	+-----+
					{															//		  |
						node->getParent()->setRight(node->getRight());			//		  0
						node->getRight()->setParent(node->getParent());
						node->setRight(nullptr);
					}
				}
				else	// ЕСЛИ КОРЕНЬ
				{
					if (node->getLeft() != nullptr)
						node = node->getLeft();
					if (node->getRight() != nullptr)
						node = node->getRight();
					node->getParent()->setIndex(*node->getIndex());
					node->getParent()->setObject(*node->getObject());
					node->getParent()->setLeft(node->getLeft());
					node->getLeft()->setParent(node->getParent());
					node->setLeft(nullptr);
					node->getParent()->setRight(node->getRight());
					node->getRight()->setParent(node->getParent());
					node->setRight(nullptr);
				}
			}

			else if (node->getLeft() != nullptr && node->getRight() == nullptr)
			{
				if (node->getParent() != nullptr)
				{
					if (*node->getIndex() < *node->getParent()->getIndex())
					{
						node->getParent()->setLeft(node->getLeft());
						node->getLeft()->setParent(node->getParent());			//			|
						node->setLeft(nullptr);									// delete-> 0
					}															//          |
					if (*node->getIndex() > *node->getParent()->getIndex())		//    +-----+
					{															//	  |
						node->getParent()->setRight(node->getLeft());			//	  0
						node->getLeft()->setParent(node->getParent());
						node->setLeft(nullptr);
					}
				}
				else	// ЕСЛИ КОРЕНЬ
				{
					if (node->getLeft() != nullptr)
						node = node->getLeft();
					else if (node->getRight() != nullptr)
						node = node->getRight();
					node->getParent()->setIndex(*node->getIndex());
					node->getParent()->setObject(*node->getObject());
					node->getParent()->setLeft(node->getLeft());
					node->getLeft()->setParent(node->getParent());
					node->setLeft(nullptr);
					node->getParent()->setRight(node->getRight());
					node->getRight()->setParent(node->getParent());
					node->setRight(nullptr);
				}
			}

			else if (node->getLeft() != nullptr && node->getRight() != nullptr)	//       |
			{																	//  	 0 <-delete
				tree<T>* _node = node;											//		 |
				node = _node->getRight();										// +-----+-----+
				while (node->getLeft() != nullptr)	// ИЩЕМ САМЫЙ МАЛЕНЬКИЙ		// |           |
					node = node->getLeft();			// ЭЛЕМЕНТ ПОДДЕРЕВА		// 0           0

				_node->setIndex(*node->getIndex());
				_node->setObject(*node->getObject());
				if (node->isLeaf())
				{
					if (node->getParent() == _node)
						node->getParent()->setRight(nullptr);
					else
						node->getParent()->setLeft(nullptr);
				}
				else if (!node->isLeaf())
				{
					if (node->getParent() == _node)
						node->getParent()->setRight(node->getRight());
					else
						node->getParent()->setLeft(node->getRight());
					node->getRight()->setParent(node->getParent());
					node->setRight(nullptr);
				}
			}
			delete node;
		}
	}
	void print()
	{
		std::cout << this->tree_in_str();
	}
	void print_into_file(std::string file_name)
	{
		std::ofstream outf(file_name);
		if (!outf)
			throw -1;
		else
			outf << this->tree_in_str();
	}
	int min()
	{
		tree<T>* node = this;
		while (node->getLeft() != nullptr)
		{
			node = node->getLeft();
		}
		return *node->getIndex();
	}
	int max()
	{
		tree<T>* node = this;
		while (node->getRight() != nullptr)
		{
			node = node->getRight();
		}
		return *node->getIndex();
	}
	tree<T>* getParent() const { return this->pParent; }
	void setParent(tree<T> *parent) { this->pParent = parent; }
	tree<T>* getLeft() const { return this->pLeft; }
	void setLeft(tree<T> *left) { this->pLeft = left; }
	tree<T>* getRight() const { return this->pRight; }
	void setRight(tree<T> *right) { this->pRight = right; }
	T* getObject() const { return this->pObject; }
	void setObject(const T object) { this->pObject = new T(object); }
	int* getIndex() const { return this->pIndex; }
	void setIndex(const int index) { this->pIndex = new int(index); }
private:
	tree<T>* pParent;
	tree<T>* pLeft;
	tree<T>* pRight;

	T* pObject;
	int* pIndex;

	bool isLeaf()
	{
		return (this->pLeft == nullptr && this->pRight == nullptr);
	}
	std::string tree_in_str()
	{
		if (this->pIndex == nullptr)
			return "";
		tree<T> *root = new tree<T>(*this);
		std::vector<std::vector<tree<T>*>> tree_levels;
		tree_levels = this->get_tree_levels(this);

		int num_lenght = this->num_lenght(this->max());	// СЧИТАЕМ СКОЛЬКО РАЗРЯДОВ В МАКСИМАЛЬНОМ ИНДЕКСЕ

		// СЧИТАЕМ КОЛЛИЧЕСТВО ОТСТУПОВ СПРАВА И СЛЕВА
		if (num_lenght % 2 == 0)
			num_lenght /= 2;
		else
			num_lenght = (num_lenght - 1) / 2;

		// АДАПТАЦИЯ ОТСТУПОВ ПОД КОЛЛИЧЕСТВО ЗНАКОВ В ЧИСЛЕ
		int count_indent = 1;
		{
			int degree_of_two = 1;
			for (int i = 2; i < num_lenght + 1; i *= 2, degree_of_two++);
			degree_of_two += tree_levels.size();	// ПРИБАВЛЯЕМ ВЫСОТУ ДЕРЕВА
			for (int i = 0; i < degree_of_two; i++, count_indent *= 2);
		}
		count_indent--;
		num_lenght = 0;

		std::string res = "";
		int _left = 0;	// СКОЛЬКО ОТСТУПОВ УДАЛИТЬ СЛЕВА
		int _right = 0;	// СПРАВА
		// СЧИТАЕМ ПОД КОРЕНЬ
		num_lenght = this->num_lenght(*tree_levels[0][0]->getIndex());
		if (num_lenght % 2 == 1)
		{
			_left = (num_lenght - 1) / 2;
			_right = (num_lenght - 1) / 2;
		}
		else
		{
			_left = (num_lenght / 2) - 1;
			_right = num_lenght / 2;
		}

		res += "+" + this->get_count_char("-", 2 * count_indent + 1) + "+\n";
		res += "|" + this->get_count_char(" ", count_indent - _left) + int_to_str(*tree_levels[0][0]->getIndex())
			+ this->get_count_char(" ", count_indent - _right) + "|\n";	// КОРЕНЬ
		for (int i = 1, _count_indent = count_indent; i < tree_levels.size(); i++)
		{
			_count_indent = (_count_indent - 1) / 2;

			res += "|" + get_count_char(" ", (_count_indent - 1) / 2 + 1);
			for (int j = 0; j < tree_levels[i].size(); j++)
			{
				res += get_str_el_arr(tree_levels[i][j], _count_indent);
				if (j != tree_levels[i].size() - 1)
					res += this->get_count_char(" ", _count_indent + 1);
				else	// ЕСЛИ ПОСЛЕДНИЙ ЭЛЕМЕНТ
					res += get_count_char(" ", (_count_indent - 1) / 2) + "|\n";
			}
		}
		res += "+" + this->get_count_char("-", 2 * count_indent + 1) + "+\n";
		return res;
	}
	std::vector<std::vector<tree<T>*>> get_tree_levels(tree<T>* root)
	{
		tree<T> *null = nullptr;
		std::vector<std::vector<tree<T>*>> tree_levels;
		std::vector<tree<T>*> buf;
		buf.push_back(root);
		tree_levels.push_back(buf);
		buf.clear();
		for (int i = 0; i < tree_levels.size(); i++)
		{
			int count_null = 0;
			for (tree<T> *item : tree_levels[i])	// СЧИТАЕМ nullptr ЭЛЕМЕНТЫ
			{
				if (item == null)
					count_null++;
			}
			if (count_null == tree_levels[i].size())	// ЕСЛИ ВСЯ СТРОКА nullptr, удаляем ее
			{
				tree_levels.pop_back();
				break;
			}
			else if (count_null > tree_levels[i].size())
				throw -1;
			else
			{
				for (tree<T> *item : tree_levels[i])	// ДОБАВЛЯЕМ СТРОКИ ДЕРЕВА
				{
					if (item == nullptr)
					{
						buf.push_back(nullptr);	// LEFT
						buf.push_back(nullptr);	// RIGHT
					}
					else
					{
						buf.push_back(item->getLeft());
						buf.push_back(item->getRight());
					}
				}
				tree_levels.push_back(buf);
				buf.clear();
			}
		}
		return tree_levels;
	}
	std::string get_count_char(const std::string _char, const int count)
	{
		std::string res = "";
		for (int i = 0; i < count; i++)
			res += _char;
		return res;
	}
	std::string get_str_el_arr(const tree<T>* tree_el, const int _count_indent)
	{
		std::string res = "";
		if (tree_el == nullptr)
			res += this->get_count_char(" ", (_count_indent - 1) / 2) + " " + this->get_count_char(" ", (_count_indent - 1) / 2) + " ";
		else
		{
			int _left;
			int _right;
			int num_lenght = this->num_lenght(*tree_el->getIndex());
			if (num_lenght % 2 == 1)
			{
				_left = (num_lenght - 1) / 2;
				_right = (num_lenght - 1) / 2;
			}
			else
			{
				_left = (num_lenght / 2) - 1;
				_right = num_lenght / 2;
			}
			res += this->get_count_char(" ", (_count_indent - 1) / 2 - _left) + int_to_str(*tree_el->getIndex())
				+ this->get_count_char(" ", (_count_indent - 1) / 2 + 1 - _right);
		}
		return res;
	}
	int num_lenght(const int _num)
	{
		int num = _num;
		int count_char = 1;
		if(num < 0)
			num *= -10;
		while (num >= 10)
		{
			count_char++;
			num /= 10;
		}
		return count_char;
	}

	std::string int_to_str(const int num)
	{
		std::stringstream os;
		os << num;
		std::string res;
		os >> res;
		return res;
	}
};

#endif // TREES_H
