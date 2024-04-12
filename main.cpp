#include<hashtable.h>

int main()
{
    setlocale(LC_ALL, "Russian");
    HashTable<int, string> h1(3);
    h1.insert(0, "Вова");
    h1.insert(1, "Петя");
    h1.insert(2, "Саша");
    h1.print();
    ioLine();
}