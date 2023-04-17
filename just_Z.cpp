

#include <iostream>
int modul(int num, int mod)
{
    int c = num % mod;
    if (c < 0)
    {
        c = mod + c;
    }
    return c;
}
using namespace std;
class Z
{
    int num;
    int mod;
public:
    Z(int _num, int _mod)//Основной конструктор
    {
        this->mod = _mod;
        this->num = modul(_num,_mod);
    }
    Z(const Z& p)//Конструктор копирования
    {
        this->mod = p.mod;
        this->num = p.num;
    }
    Z operator =(Z p)//Оператор =
    {
        return (Z(p));
    }
    int operator [](int k)//Oператор []
    {
        if (k == 1)
        {
            return num;
        }
        if (k == 2)
        {
            return mod;
        }
    }
    string IndexOff(int n)
    {
        if (mod == n)
        {
            return "mod";
        }
        if (num == n)
        {
            return "num";
        }
        if (num != n && mod!=n)
        {
            return "-";
        }
    }
    void print()
    {
        cout << num << " (mod " << mod << ")"<<endl;
    }
};
class Zchild :public Z
{
public:
    Zchild(int _num, int _mod) : Z(_num,_mod)
    {
        cout << "\nMyArrayChild constructor"<<endl;
    }

};
int main()
{
    
    Zchild z1 = Zchild(2, 5);
    z1.print();
}


