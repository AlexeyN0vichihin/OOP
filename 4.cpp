#include <iostream>
using namespace std;
class BaseString
{
protected:
	int capacity;//Выделено
	int count;//Используем
	char* ptr;//Сам Массив
public:

	BaseString(const int Dimension = 100)//Встроенный конструктор
	{
		cout << "\nMyArray constructor";
		try
		{
			ptr = new char[Dimension];
		}
		catch (std::bad_alloc & ba)
		{
			throw string("Нет памяти");
		}
		capacity = Dimension;
		count = 0;
	}
	BaseString(const int capacity_,const int count_,const char* ptr_)//Наш конструктор
	{
		cout << "\nMyArray constructor" << endl;
		if (capacity_ < count_)
		{
			throw string("Память не выделенна");
		}
		char* a;
		try
		{
			a = new char[capacity_];
		}
		catch (std::bad_alloc & ba)
		{
			throw string("Нет памяти");
		}
		for (int i = 0; i < count_; i++)
		{
			if (ptr_[i] == NULL)
			{
				throw string("Пустой массив");
			}
			a[i] = ptr_[i];

		}
		ptr = a;
		capacity = capacity_;
		count = count_;
	}
	BaseString(const char* arr,const int len)//Конструктор, принимающий текущий массив
	{
		cout << "\nMyArray constructor";
		capacity = len + 10;
		count = len;
		char* a;
		try
		{
			a = new char[capacity];
		}
		catch (std::bad_alloc & ba)
		{
			throw string("Нет памяти");
		}
		for (int i = 0; i < count; i++)
		{
			if (arr[i] == NULL)
			{
				throw string("Пустой массив");
			}
			a[i] = arr[i];
		}
		ptr = a;
	}
	~BaseString()//Деструктор
	{
		cout << "\nMyArray destructor";
		if (ptr != NULL)
		{
			ptr = NULL;
		}
	}

	const int Capacity() { return capacity; }//Возвращение/изменение полей
	const int Size() { return count; }
	const char GetComponent(const int index)
	{
		if (index >= 0 && index < count)
			return ptr[index];
		else
			throw string("Выход за пределы массива");
	}
	void SetComponent(const int index,const char value)
	{
		if (index >= 0 && index < count)
			ptr[index] = value;
		else
			throw string("Выход за пределы массива");

	}
	void push(const char value)//Вставка элемента в конец массива
	{
		if (value == NULL)
		{
			throw string("Пустой эллемент");
		}
		if (count < capacity)
		{
			ptr[count] = value;
			count++;
		}
		else
		{
			throw string("Не выделенна память");
		}

	}
	void RemoveLastValue()//Удаление последнего элемента
	{
		if (count > 0)
			count--;
		else
			throw string("Пустой массив");

	}
	char& operator[](const int index)//Перегрузка[]
	{
		if (index >= 0 && index < count)
			return ptr[index];
		else
			throw string("Выход за пределы");
	}
	BaseString operator=(const BaseString& V)//Перегрузка=
	{
		cout << "\noperator = ";
		capacity = V.capacity;
		count = V.count;
		try
		{
			ptr = new char[capacity];
		}
		catch (std::bad_alloc & ba)
		{
			throw string("Нет памяти");
		}
		for (int i = 0; i < count; i++)
		{
			ptr[i] = V.ptr[i];
		}
	}
	BaseString(const BaseString& V)//Конструктор копий
	{
		cout << "\nCopy constructor";
		capacity = V.capacity;
		count = V.count;
		char* a;
		try
		{
			a = new char[capacity];
		}
		catch (std::bad_alloc & ba)
		{
			throw string("Нет памяти");
		}
		for (int i = 0; i < count; i++)
		{
			a[i] = V.ptr[i];
		}
		ptr = a;
	}
	const void print()//Принт
	{
		cout << "\nMyArr, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}" << endl;
	}
	const double IndexOff(const char value)//Поиск по индексу
	{
		for (int i = 0; i < count; i++)
		{
			if (ptr[i] == value)
			{
				return ptr[i];
			}
		}
		throw string("Отсутствует значение");
	}
};

class ChildString:public BaseString
{
public:
	ChildString(const int Dimension = 100) : BaseString(Dimension)//Переопределяемя конструкторы
	{
		cout << "\nMyArrayChild constructor";
	}
	ChildString(const char* arr,const int len) : BaseString(arr, len)//Переопределяемя конструкторы
	{
		cout << "\nMyArrayChild constructor";
	}
	ChildString(const int capacity_,const int count_,const char* ptr_) : BaseString(capacity_, count_, ptr_)
	{
		cout << "\nMyArrayChild constructor";
	}
	void RemoveAt(const int Index)//Удаленеи элемента
	{
		for (int i = Index; i < count - 1; i++)
		{
			ptr[i] = ptr[i + 1];
		}
		count = count - 1;
	}
	void remove()
	{
		for (int i=0; i < count; i++)
		{
			if (ptr[i] == ' ')
			{
				RemoveAt(i);
			}
		}
	}
};

void main()
{
	setlocale(LC_ALL, "ru");
	try
	{
		char m[4];
		m[0] = 'h';
		m[1] = 'a';
		m[2] = ' ';
		m[3] = 'e';
		ChildString a = ChildString(4, 4,m);
		a.print();
		a.remove();
		a.print();
		
	}
	catch (const string ex)
	{
		cout << ex << endl;
	}
}