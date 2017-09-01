

//
// Created by tigertang on 17-8-31.
//

#include "dynamic_bitset.h"

dynamic_bitset::const_unit_reference dynamic_bitset::unit_at(size_type i) const
{
    return _v[i];
}

dynamic_bitset::dynamic_bitset() : dynamic_bitset(0) {}

dynamic_bitset::dynamic_bitset(size_type size) : _size(size)
{
    _v.resize((size + unit_size - 1) / unit_size);
    for (auto &iter : _v)
        iter = 0;
}

dynamic_bitset::reference dynamic_bitset::operator[](size_type i)
{
    return _v[i / unit_size][i % unit_size];
}

void dynamic_bitset::_push(size_type tot,
                           const_unit_reference u,
                           size_type s,
                           difference_type l)
{
    if (tot == 0)
    {
        unit temp((unsigned long long)(((unsigned __int128)1 << l) - 1));
        _v[0] = (u >> s) & temp;
    }
    else
    {
        size_type i = (tot - 1) / unit_size, j = (tot - 1) % unit_size;
        difference_type cp_len = std::min(l, unit_size - 1 - j);
        unit temp((unsigned long long)(((unsigned __int128)1 << cp_len) - 1));
        _v[i] |= ((u >> s) & temp) << (j + 1);
        s += cp_len;
        cp_len = l - cp_len;
        if (cp_len == 0)
            return;
        temp = (unsigned long long)(((unsigned __int128)1 << cp_len) - 1);
        _v[i + 1] = (u >> s) & temp;
    }
}

dynamic_bitset::size_type dynamic_bitset::size() const
{
    return _size;
}

dynamic_bitset::dynamic_bitset(const dynamic_bitset &other,
                               size_type s,
                               difference_type l) : dynamic_bitset(l)
{
    size_type tot = 0, last = s % unit_size;
    for (size_type i = s / unit_size; tot < l; i++)
    {
        if (tot + unit_size - last <= l)
        {
            _push(tot, other.unit_at(i), last, unit_size - last);
            tot += unit_size - last;
            last = 0;
        }
        else
        {
            _push(tot, other.unit_at(i), last, l - tot);
            tot = l;
        }
    }
}

std::string dynamic_bitset::to_string() const
{
    std::string res;
    for (size_type i = 0; i < _v.size() - 1; i++)
    {
        res = _v[i].to_string() + res;
    }
    for (size_type i = 0; i < _size % unit_size; i++)
        res = std::string(1, '0' + (_v.end() - 1)->test(i)) + res;
    return res;
}

void dynamic_bitset::resize(size_type size)
{
    if (size > _size && _size > 0)
    {
        size_type last = _size % unit_size;
        last = last == 0 ? unit_size : last;
        *(_v.end() - 1) &= (unsigned long long)(((unsigned __int128)1 << last) - 1);
    }
    _size = size;
    _v.resize((size + unit_size - 1) / unit_size);
}

dynamic_bitset &dynamic_bitset::reset()
{
    for (auto &iter : _v)
        iter.reset();
    return *this;
}

dynamic_bitset &dynamic_bitset::set()
{
    for (auto &iter : _v)
        iter.set();
    return *this;
}

dynamic_bitset dynamic_bitset::operator^(const dynamic_bitset &other) const
{
    size_type len = std::min(other.size(), _size);
    dynamic_bitset res(_size);
    for (size_type i = 0; i <= (len - 1) / unit_size; i++)
        res._v[i] = this->unit_at(i) ^ other.unit_at(i);
    return res;
}

dynamic_bitset &dynamic_bitset::operator^=(const dynamic_bitset &other)
{
    size_type len = std::min(other.size(), _size);
    for (size_type i = 0; i <= (len - 1) / unit_size; i++)
        _v[i] = this->unit_at(i) ^ other.unit_at(i);
    return *this;
}

bool dynamic_bitset::test(size_type i) const
{
    return (bool)unit_at(i / unit_size)[i % unit_size];
}