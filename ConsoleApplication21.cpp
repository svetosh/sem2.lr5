#include "vector.h"
#include <iostream>

struct CustomType
{
    uint64_t smthu6[10];
    double smthd[10];
};

std::ostream&
operator<<(std::ostream& out, CustomType i)
{
    std::cout << i.smthd[1] << "," << i.smthu6[1];
    return out;
}

template<typename T>
std::ostream&
operator<<(std::ostream& out, Vector<T>& v)
{
    for (T& i : v)
    {
        std::cout << i << " ";
    }
    return out;
}

template<typename T>
void
print_info(Vector<T>& v)
{
    std::cout << "Vector: " << v << std::endl
        << " size = " << v.size() << std::endl
        << " capacity = " << v.capacity() << std::endl
        << std::endl;
}

int main()
{
    setlocale(LC_ALL, "ru");
    std::cout << " Инициализация пустого вектора " << std::endl;
    Vector<int> v0;
    print_info(v0);
    std::cout << " Добавление элемента в конец " << std::endl;
    v0.push_back(1);
    print_info(v0);
    v0.push_back(2);
    print_info(v0);
    v0.push_back(3);
    print_info(v0);
    v0.push_back(4);
    print_info(v0);
    v0.push_back(5);
    print_info(v0);
    std::cout << " Добавление одного элемента в вектор " << std::endl;
    v0.insert(3, 6);
    print_info(v0);
    std::cout << "  Добавление четырёх элемента в вектор " << std::endl;
    v0.insert(2, 7, 4);
    print_info(v0);
    std::cout << " Удаление 1го элемента с начала " << std::endl;
    v0.erase(v0.begin());
    print_info(v0);
    std::cout << " удаление в диапазоне  " << std::endl;
    v0.erase(v0.begin() + 2, v0.end() - 4);
    print_info(v0);
    std::cout << "  Использование конструктора копирования " << std::endl;
    Vector<int> v1(v0);
    print_info(v1);
    std::cout << " Использование конструктора vector (v_size) " << std::endl;
    Vector<int> v2(10);
    print_info(v2);
    std::cout << " Использование нестандартного типа " << std::endl;
    Vector<CustomType> vcu(3);
    print_info(vcu);
    std::cout << " Доступ к чему-либо через [] в векторе пользовательского типа " << std::endl;
    std::cout << "До:" << std::endl;
    std::cout << vcu[1] << std::endl; 
    vcu[1].smthd[1] = 5;              
    std::cout << "После:" << std::endl;
    std::cout << vcu[1] << std::endl << std::endl;
    std::cout << " Доступ к несуществующему элементу " << std::endl;
    try
    {
        v1.at(v1.size());
    }
    catch (const std::out_of_range& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << std::endl << " Удаление из конца " << std::endl;
    v1.pop_back();
    print_info(v1);
    std::cout << " Использование оператора = " << std::endl;
    print_info(v2);
    v2 = v0;
    print_info(v2);
    std::cout << " Смена векторов " << std::endl;
    v0.shrink_to_fit();
    v1.shrink_to_fit();
    std::cout << "До:" << std::endl;
    std::cout << "v0 = " << v0 << std::endl;
    std::cout << "v1 = " << v1 << std::endl;
    swap(v0, v1);
    std::cout << "После:" << std::endl;
    std::cout << "v0 = " << v0 << std::endl;
    std::cout << "v1 = " << v1 << std::endl;
    return 0;
}