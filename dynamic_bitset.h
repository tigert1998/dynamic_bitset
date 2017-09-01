//
// Created by tigertang on 17-8-31.
//

#ifndef DYNAMIC_BITSET_DYNAMIC_BITSET_H
#define DYNAMIC_BITSET_DYNAMIC_BITSET_H

#include <bitset>
#include <vector>
class dynamic_bitset
{
    static const size_t unit_size = 64;

    typedef size_t size_type;
    typedef size_t difference_type;
    typedef std::bitset<unit_size> unit;
    typedef const unit &const_unit_reference;
    typedef unit::reference reference;

  private:
    size_type _size;
    std::vector<unit> _v;

    inline void _push(size_type, const_unit_reference, size_type, difference_type);

  public:
    dynamic_bitset();

    explicit dynamic_bitset(size_type);

    dynamic_bitset(const dynamic_bitset &, size_type, difference_type);

    const_unit_reference unit_at(size_type) const;

    reference operator[](size_type);

    size_type size() const;

    std::string to_string() const;

    void resize(size_type);

    dynamic_bitset &reset();

    dynamic_bitset &set();

    dynamic_bitset operator^(const dynamic_bitset &) const;

    dynamic_bitset &operator^=(const dynamic_bitset &);

    bool test(size_type) const;
};

#endif //DYNAMIC_BITSET_DYNAMIC_BITSET_H
