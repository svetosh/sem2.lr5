#pragma once
#include <iterator>

template<typename T>
class iterator
{
    T* pos;

public:
    using value_type = T;                   
    using difference_type = std::ptrdiff_t; 
    using pointer = T*;                     
    using reference = T&;                   

    iterator(T* pos) : pos(pos) {}

    bool operator==(const iterator<T>& other) const
    {
        return pos == other.pos;
    }
    bool operator!=(const iterator<T>& other) const
    {
        return pos != other.pos;
    }
    pointer operator->() const
    {
        return pos;
    }
    reference operator*() const
    {
        return *pos;
    }
    iterator<T>& operator++()
    {
        ++pos;
        return *this;
    }
    iterator<T> operator++(int)
    {
        iterator<T> temp = *this;
        ++pos;
        return temp;
    }

    iterator<T>& operator--()
    {
        --pos;
        return *this;
    }
    iterator<T> operator--(int)
    {
        iterator<T> temp = *this;
        --pos;
        return temp;
    }
    reference operator[](size_t index) const
    {
        return pos[index];
    }
    iterator<T> operator+(const difference_type& diff) const
    {
        return iterator<T>(pos + diff);
    }
    template<typename TF>
    friend inline iterator<TF> operator+(const std::ptrdiff_t& diff, const iterator<TF>& iter);

    iterator<T> operator-(const difference_type& diff) const
    {
        return iterator<T>(pos - diff);
    }
    difference_type operator-(const iterator<T>& other) const
    {
        return std::distance(other.pos, pos);
    }
    iterator<T>& operator+=(const difference_type& diff)
    {
        pos += diff;
        return *this;
    }
    iterator<T>& operator-=(const difference_type& diff)
    {
        pos -= diff;
        return *this;
    }
    bool operator>(const iterator<T>& other) const
    {
        return pos > other.pos;
    }
    bool operator<(const iterator<T>& other) const
    {
        return pos < other.pos;
    }
    bool operator>=(const iterator<T>& other) const
    {
        return pos >= other.pos;
    }
    bool operator<=(const iterator<T>& other) const
    {
        return pos <= other.pos;
    }
    template<typename TF>
    friend std::ptrdiff_t distance(const iterator<TF>& iter_first, const iterator<TF>& iter_last);
};

template<typename TF>
iterator<TF>
operator+(const std::ptrdiff_t& diff, const iterator<TF>& iter)
{
    return iterator<TF>(iter.pos + diff);
}

template<typename TF>
std::ptrdiff_t
distance(const iterator<TF>& iter_first, const iterator<TF>& iter_last)
{
    std::ptrdiff_t diff = iter_last.pos - iter_first.pos;
    return diff;
}