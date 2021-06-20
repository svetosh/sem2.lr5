#pragma once
#include <cmath>
#include <stdexcept>

#include "iterator.h"

template<typename T> 
class Vector
{
    T* fact;
    int Size;
    int allocated_size;

    float magnifier = 1.5; 

    void copy_data_to(T* new_fact, int csize, int ref_offset = 0, int copy_offset = 0) const 
    {
        for (int i = 0; i < csize; ++i) 
        {
            new_fact[i + copy_offset] = fact[i + ref_offset];
        }
    }

public:
    Vector()
    {
        fact = nullptr;
        Size = 0;
        allocated_size = 0;
    }

    explicit Vector(const int& new_size, float custom_magnifier = 1.5)
    {
        magnifier = custom_magnifier;
        Size = 0;
        allocated_size = new_size + 1;
        fact = new T[allocated_size];
    }

    explicit Vector(const Vector& origin_v, float custom_magnifier = 1.5)
    {
        magnifier = custom_magnifier;
        allocated_size = std::round(origin_v.size() * magnifier);
        fact = new T[allocated_size];
        Size = origin_v.size();
        origin_v.copy_data_to(fact, Size);
    }

    T& at(const int& index) // получить элемент по его позиции
    {
        if (index >= size())
            throw std::out_of_range( "Доступ к несуществующему элементу (index >= size()).");
        return fact[index];
    }

    T& operator[](const int& index)  //получить элемент по его позиции, без проверок
    {
        return fact[index];
    }

    T& front()
    {
        return fact[0];
    }

    T& back()
    {
        return fact[Size - 1];
    }

    T* data() //получить указатель первого
    {
        return fact;
    }

    int size() const
    {
        return Size;
    }

    int capacity() const
    {
        return allocated_size - 1;
    }

    // итераторы для range_based_for
    iterator<T> begin()
    {
        return iterator<T>(&fact[0]);
    }
    iterator<T> end()
    {
        return iterator<T>(&fact[Size]);
    }

    bool empty()
    {
        return Size == 0;
    }


    void reserve(int new_size)
    {
        if (new_size > capacity()) {
            T* new_fact = new T[new_size + 1];
            copy_data_to(new_fact, Size);
            delete[] fact;
            fact = new_fact;
            allocated_size = new_size + 1;
            Size = new_size;
        }
    }

    void push_back(T element)
    {
        if (allocated_size == 0) {
            allocated_size = std::round(magnifier);
            fact = new T[allocated_size];
            fact[0] = element;
            ++Size;
        }
        else if (Size == capacity()) 
        {
            allocated_size = std::round(allocated_size * magnifier);
            T* new_fact = new T[allocated_size];
            copy_data_to(new_fact, Size);
            delete[] fact;
            fact = new_fact;
            fact[Size] = element;
            ++Size;
        }
        else 
        {
            fact[Size] = element;
            ++Size;
        }
    }

    
    void shrink_to_fit() // функция, для очищения неиспользованного пространства 
    {
        if (Size == capacity()) 
        {
            return;
        }
        allocated_size = Size + 1;
        T* new_fact = new T[allocated_size];
        copy_data_to(new_fact, Size);
        delete[] fact;
        fact = new_fact;
    }

    void insert(int index, const T& element, int el_count = 1) // вставляем один или несколько элементов
    {
        if (index < Size) //сначала проверьте, находится ли индекс в векторе
        {
            if (Size + el_count - 1 < capacity())  //если емкости достаточно для хранения вектора и нового элемента, просто сдвиньте все элементы после определенного индекса
            {
                for (int i = Size - 1; i >= index; --i)
                {
                    fact[i + el_count] = fact[i];
                }
            }
            else
            {
                allocated_size = std::round((allocated_size + el_count) * magnifier);
                T* new_fact = new T[allocated_size];
                copy_data_to(new_fact, index);
                copy_data_to(new_fact, Size - index, index, index + el_count);
                delete[] fact;
                fact = new_fact;
            }
            for (int i = index; i < index + el_count; ++i) 
            {
                fact[i] = element;
            }
            Size += el_count;
        }
        else 
        {
            throw std::out_of_range("Индекс вне вектора");
        }
    }

    void erase(iterator<T> iter)
    {
        if (empty())
        {
            return;
        }
        int copy_offset = distance(begin(), iter);
        int ref_offset = copy_offset + 1;
        --Size;
        copy_data_to(fact, Size, ref_offset, copy_offset);
    }

    void erase(iterator<T> iter_first, iterator<T> iter_last)
    {
        if (empty())
        {
            return;
        }
        int esize = distance(iter_first, iter_last);
        int csize = distance(iter_last, end());
        int begin_pos = distance(begin(), iter_first);
        copy_data_to(fact, csize, begin_pos + esize, begin_pos);
        Size -= esize;
    }

    void pop_back()
    {
        if (!empty()) 
        {
            --Size;
        }
    }

    void resize(int new_size)
    {
        if (new_size == Size)
            return;
        if (new_size > capacity()) 
        {
            T* new_fact = new T[new_size + 1];
            copy_data_to(new_fact, Size);
            delete[] fact;
            fact = new_fact;
            allocated_size = new_size + 1;
        }
        Size = new_size;
    }

    void clear()
    {
        delete[] fact;
        fact = nullptr;
        Size = 0;
        allocated_size = 0;
    }

    Vector<T>& operator=(Vector& vec)
    {
        if (fact != nullptr)
            delete[] fact;
        Size = vec.Size;
        allocated_size = Size;
        if (allocated_size > 0)
        {
            fact = new T[allocated_size];
            for (int i = 0; i < Size; ++i)
            {
                fact[i] = vec.fact[i];
            }
        }
        else 
        {
            fact = nullptr;
        }
        return *this;
    }

    template<typename TF> friend void swap(Vector<TF>& v0, Vector<TF>& v1);

    ~Vector()
    {
        delete[] fact;
    }
};

template<typename TF>
void
swap(Vector<TF>& v0, Vector<TF>& v1)
{
    TF* tmp = v0.fact;
    v0.fact = v1.fact;
    v1.fact = tmp;

    int tmp_size = v0.Size;
    v0.Size = v1.Size;
    v1.Size = tmp_size;

    tmp_size = v0.allocated_size;
    v0.allocated_size = v1.allocated_size;
    v1.allocated_size = tmp_size;
}
