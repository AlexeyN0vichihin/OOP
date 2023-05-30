#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
using namespace std;
class Exception : public std::exception//Класс-исключение
{
protected:
	char* str; //сообщение об ошибке
public:
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика

	virtual void print()
	{
		cout << "Exception: " << str;
	}
};
class InvalidOperationException :public Exception
{
public:
	InvalidOperationException(const char* s) : Exception(s) {}
	virtual void print()
	{
		cout << "InvalidOperationException: " << str;
	}
};
class IndexOutOfBoundsException :public Exception
{
public:
	IndexOutOfBoundsException(const char* s) : Exception(s) {}
	virtual void print()
	{
		cout << "IndexOutOfBoundsException: " << str;
	}
};
class WrongSizeException :public Exception
{
public:
	WrongSizeException(const char* s) : Exception(s) {}
	WrongSizeException(const Exception& e):Exception(e) {}
	virtual void print()
	{
		cout << "WrongSizeException: " << str;
	}
};
class NonPositiveSizeException :public  WrongSizeException
{
public:
	NonPositiveSizeException(const char* s) :WrongSizeException(s) {}
	NonPositiveSizeException(const Exception& e) :WrongSizeException(e) {}
	virtual void print()
	{
		cout << "NonPositiveSizeException: " << str;
	}
};
class TooLargeSizeException :public  WrongSizeException
{
public:
	TooLargeSizeException(const char* s) :WrongSizeException(s) {}
	virtual void print()
	{
		cout << "TooLargeSizeException: " << str;
	}
};
class BaseMatrix//Основной класс
{
protected:
	double** ptr;//Наш двумерный массив
	int height;//Высота
	int width;//Ширина
public:
	BaseMatrix(int Height = 2, int Width = 2)
	{
		if (Height <= 0 || Width <= 0)
		{
			NonPositiveSizeException* k =new NonPositiveSizeException("");
			throw *k;
		}
		height = Height;
		width = Width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
			ptr[i] = new double[width];

	}
	BaseMatrix(double** a,int height_,int width_)
	{
		height = height_;
		width = width_;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new double[width];
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				ptr[i][j] = a[i][j];
			}
		}
	}
	BaseMatrix(const BaseMatrix& M)//Конструктор копий
	{
		height = M.height;
		width = M.width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new double[width];
			for (int j = 0; j < width; j++)
				ptr[i][j] = M.ptr[i][j];
		}
	}
	~BaseMatrix()//Деструктор
	{
		if (ptr != NULL)
		{
			for (int i = 0; i < height; i++)
				delete[] ptr[i];
			delete[] ptr;
			ptr = NULL;
		}
	}
	int Get_height()
	{
		return height;
	}
	int Get_width()
	{
		return width;
	}
	void print()//Вывод
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
				cout << ptr[i][j] << " ";
			cout << "\n";
		}
	}
	double& operator()(int row, int column)//Вывод элемента
	{
		if (row < 0 || column < 0 || row >= height || column >= width)
			throw Exception("Index is out of bounds");
		return ptr[row][column];
	}
	BaseMatrix operator =(BaseMatrix M)
	{
		return BaseMatrix(M);
	}
	friend ostream& operator << (ostream& ustream, BaseMatrix
		obj);
	friend istream& operator >> (istream& ustream, BaseMatrix&
		obj);
};
class ChildMatrix: public BaseMatrix
{
public:
	ChildMatrix(int Height=2,int width=2):BaseMatrix(Height,width){}
	ChildMatrix(double** a, int height_, int width_):BaseMatrix(a,height_,width_){}
	~ChildMatrix(){}
	void filing()
	{
		double** ptr_ = new double* [height];
		for (int i = 0; i < height; i++)
		{
			ptr_[i] = new double[width];
		}

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				ptr_[i][j] =i + j;
			}
		}
		ptr = ptr_;
	}
	double* sort_vector() const
	{
		int s;
		double* k = new double[height];
		for (int i = 0; i < height; i++)
		{
			s = 1;
			for (int j = 0; j < width-1; j++)
			{
				if (ptr[i][j] > ptr[i][j + 1])
				{
					s = 0;
				}
			}
			k[i] = s;
		}
		return k;
	}
	friend ostream& operator << (ostream& ustream, BaseMatrix
		obj);
	friend istream& operator >> (istream& ustream, BaseMatrix&
		obj);
};
ostream& operator << (ostream& ustream, BaseMatrix obj)//cout
{
	
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.height << " " << obj.width<<" ";
		for (int i = 0; i < obj.height; i++)
		{
			for (int j = 0; j < obj.width; j++)
				ustream << obj.ptr[i][j] << " ";
		}
		ustream << endl;
	}
	else
	{
		for (int i = 0; i < obj.height; i++)
		{
			for (int j = 0; j < obj.width; j++)
				ustream << obj.ptr[i][j] << " ";
			ustream << "\n";
		}
		return ustream;
	}
}
istream& operator >> (istream& ustream, BaseMatrix& obj)//cin
{
	if (typeid(ustream) == typeid(ifstream))
	{
		string k1, k2;
		ustream >> k1 >> k2;
		string k;
		for (int i = 0; i < obj.height; i++)
		{
			for (int j = 0; j < obj.width; j++)
			{
				ustream >> k;
				obj.ptr[i][j] = atof(k.c_str());
			}
		}
	}
	else
	{
		for (int i = 0; i < obj.height; i++)
			for (int j = 0; j < obj.width; j++)
				ustream >> obj.ptr[i][j];
		return ustream;
	}
}
ChildMatrix Reader(ifstream fin)
{
	string k,k1, k2;
	fin >> k1;
	fin >> k2;
	int height, width;
	height = atof(k1.c_str());
	width = atof(k2.c_str());
	double** ptr = new double* [height];
	for (int i = 0; i < height; i++)
		ptr[i] = new double[width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fin >> k;
			ptr[i][j] = atof(k1.c_str());
		}
	}
	return ChildMatrix(ptr, height, width);
}
int main()
{
	
	
	/*double** m = new double* [2];
		for (int i = 0; i < 2; i++)
			m[i] = new double[2];
		m[0][0] = 1;
		m[0][1] = 1;
		m[1][0] = 1;
		m[1][1] = 1;*/

	try
	{
		ChildMatrix M = ChildMatrix(2, 2);
		ChildMatrix M1 = M;
		ChildMatrix M2 = ChildMatrix(5, 5);
		M2.filing();
		M1.filing();
		ofstream fout;
		fout.open("MatrixFile.txt");
		fout << M1;
		fout << M2;
		fout.close();
		ifstream fin;
		fin.open("MatrixFile.txt");
		ChildMatrix f = ChildMatrix(2, 2);
		ChildMatrix f1 = ChildMatrix(5, 5);
		fin >> f;
		fin >> f1;
		cout << f;
		cout << f1;
		fin.close();
	}
	catch (WrongSizeException& e)
	{
		e.print();
	}
	
}


