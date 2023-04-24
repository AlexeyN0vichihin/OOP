#include <iostream>
using namespace std;
class MyArrayParent
{
protected:
	int capacity;//Выделено
	int count;//Используем
	double* ptr;//Сам Массив
public:
	
	MyArrayParent(int Dimension = 100)//Встроенный конструктор
	{
		cout << "\nMyArray constructor";
		try
		{
			ptr = new double[Dimension];
		}
		catch (std::bad_alloc& ba)
		{
			throw string("Нет памяти");
		}
		capacity = Dimension;
		count = 0;
	}
	MyArrayParent(int capacity_,int count_,double* ptr_)//Наш конструктор
	{
		cout << "\nMyArray constructor"<<endl;
		if (capacity_ < count_)
		{
			throw string("Память не выделенна");
		}
		double* a;
		a = new double[capacity_];
		for (int i = 0; i < count_; i++)
		{
			a[i] = ptr_[i];
		}
		ptr = a;
		capacity = capacity_;
		count = count_;
	}
	MyArrayParent(double* arr, int len)//Конструктор, принимающий текущий массив
	{
		cout << "\nMyArray constructor";
		capacity = len+1;
		count = len;
		double* a;
		a = new double[capacity];
		for (int i = 0; i < count; i++)
		{
			a[i] = arr[i];
		}
		ptr = a;
	}
	~MyArrayParent()//Деструктор
	{
		cout << "\nMyArray destructor";
		if (ptr != NULL)
		{
			delete[] ptr;
			ptr = NULL;
		}
	}
	
	int Capacity() { return capacity; }//Возвращение/изменение полей
	int Size() { return count; }
	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
			return ptr[index];
		else
			throw string("Выход за пределы массива");
	}
	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
			ptr[index] = value;
		else
			throw"";
		
	}
	void push(double value)//Вставка элемента в конец массива
	{
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
			throw"";
		
	}
	double& operator[](int index)//Перегрузка[]
	{
		if (index >= 0 && index < count)
			return ptr[index];
		else
			throw string("Выход за пределы");
	}
	MyArrayParent operator=(const MyArrayParent& V)//Перегрузка=
	{
		cout << "\noperator = ";
		int capacity_ = V.capacity;
		int count_ = V.count;
		double* a;
		a = new double[capacity];
		for (int i = 0; i < count; i++)
		{
			a[i] = V.ptr[i];
		}
		
		return MyArrayParent(capacity_, count_, a);
	}
	MyArrayParent (const MyArrayParent& V)//Конструктор копий
	{
		cout << "\nCopy constructor";
		capacity = V.capacity;
		count = V.count;
		double* a;
		a = new double[capacity];
		for (int i = 0; i < count; i++)
		{
			a[i] = V.ptr[i];
		}
		ptr = a;
	}
	void print()//Принт
	{
		cout << "\nMyArr, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}"<<endl;
	}
	int IndexOff(double value)//Поиск по индексу
	{
		for (int i = 0; i < count; i++)
		{
			if (ptr[i] == value)
			{
				return i;
			}
		}
		throw string("Отсутствует значение");
	}
};
class MyArrayChild : public MyArrayParent
{
public:
	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension)//Переопределяемя конструкторы
	{
		cout << "\nMyArrayChild constructor";
	}
	MyArrayChild(int capacity_, int count_, double* ptr_) : MyArrayParent(capacity_,  count_,  ptr_)
	{
		cout << "\nMyArrayChild constructor";
	}
	void RemoveAt(int Index)//Удаленеи элемента
	{
		for (int i = Index; i < count - 1; i++)
		{
			ptr[i] = ptr[i + 1];
		}
		count=count-1;
	}
	void InsertAt(int Index, double value)//Вставка элемента(починить)
	{
		double mem1=value;
		double mem2;
		for (int i = Index; i < count ; i++)
		{
			mem2 = ptr[i];
			ptr[i] = mem1;
			mem1 = ptr[i + 1];
			ptr[i + 1] = mem2;
		}
		
		count = count + 1;
	}
	MyArrayChild def(double Value)//Наша функция
	{
		double* a = ptr;
		int j = 0;
		double k;
		for (int i = 0; i < count; i++)
		{
			if (a[i] < count)
			{
				k = a[i];
				a[i] = a[j];
				a[j] = k;
				j++;
			}
		}
		return  MyArrayChild(capacity, count, a);
	}
	~MyArrayChild() //Деструктор
	{ 
		cout << "\nMyArrayChild destructor\n"; 
		if (ptr != NULL)
		{
			delete[] ptr;
			ptr = NULL;
		}
	}

};

class MySortedArray :public MyArrayChild
{
public:
	MySortedArray(int Dimension = 100) : MyArrayChild(Dimension)
	{
		cout << "\nMySort constructor";
	}
	MySortedArray(int capacity_, int count_, double* ptr_) : MyArrayChild(capacity_, count_, ptr_)
	{
		cout << "\nMySort constructor";
	}
	~MySortedArray() 
	{
		cout << "\nMySort destructor\n"; 
		if (ptr != NULL)
		{
			delete[] ptr;
			ptr = NULL;
		}
	}
	MyArrayChild def(int Value)//Переопределяем нашу функция
	{
		double* a = ptr;
		return  MySortedArray(capacity, count, a);
	}
};

void main()
{
	setlocale(LC_ALL, "ru");
	try
	{
		double m[4];
		m[0] = 1;
		m[1] = 2;
		m[2] = 6;
		m[3] = 7;
		MyArrayParent a = MyArrayParent();
		
		a.print();
	}
	catch (const string ex)
	{
		cout << ex << endl;
	}
}
