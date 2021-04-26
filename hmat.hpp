#pragma once
#include <stddef.h>
#include <stdint.h>
#include <concepts>
#include <type_traits>

//unsigned add long
template <typename T>
concept UIntegral = std::is_integral_v<T> &&std::is_unsigned_v<T>;

template <UIntegral T>
struct uadd_long : std::type_identity<T>
{
};
template <>
struct uadd_long<uint8_t> : std::type_identity<uint16_t>
{
};
template <>
struct uadd_long<uint16_t> : std::type_identity<uint32_t>
{
};
template <>
struct uadd_long<uint32_t> : std::type_identity<uint64_t>
{
};
template <>
struct uadd_long<uint64_t> : std::type_identity<uint64_t>
{
};

template <typename T>
using uadd_long_t = typename uadd_long<T>::type;

template <typename T, UIntegral sz_t = size_t>
class hMat
{
private:
    T *internal = nullptr;
    sz_t w = 0, h = 0;

public:
    using type = T;
    using size_type = sz_t;
    using msize_type = uadd_long_t<sz_t>; //max size type

    hMat() = default;
    explicit hMat(sz_t w, sz_t h) : w(w), h(h)
    {
        this->internal = new T[w * h]{}; //allocate and default initialize
    }
    hMat(const hMat &m) : w(m.w), h(m.h)
    {
        this->internal = new T[w * h]{}; //allocate and default initialize
        for (msize_type i = 0; i < this->Area(); ++i)
        {
            this->internal[i] = m.internal[i];
        }
    }
    hMat(hMat &&m) : w(m.w), h(m.h)
    {
        this->internal = std::move(m.internal); //moving
        m.w = m.h = 0;                          //clean up
    }

    //Iterators
    T *begin() { return &internal[0]; }
    T *end() { return &internal[this->Area() - 1]; }
    const T *begin() const { return &internal[0]; }
    const T *end() const { return &internal[this->Area() - 1]; }
    T *data() { return internal; }

    //Size
    msize_type Area() const { return Width() * Height(); }
    sz_t Width() const { return w; }
    sz_t Height() const { return h; }
    void Resize(sz_t new_w, sz_t new_h)
    {
        msize_type new_area = new_w * new_h;
        T *temp = new T[new_area]{};
        for (msize_type i = 0; i < this->Area() && i < new_area; ++i)
        {
            temp[i] = this->internal[i];
        }
        w = new_w;
        h = new_h;
        std::swap(this->internal, temp);
        delete[] temp;
    }

    //Indexing
    T &At(size_type x, size_type y) { return FastAt((y * (Width()) + x)); }
    T At(size_type x, size_type y) const { return FastAt((y * (Width()) + x)); }

    T &FastAt(msize_type index)
    {
        if (index >= this->Area())
        {
            throw std::out_of_range("FastAt& out of range");
        }
        return internal[index];
    }
    T FastAt(msize_type index) const
    {
        if (index >= this->Area())
        {
            throw std::out_of_range("FastAt out of range");
        }
        return internal[index];
    }

    ~hMat() { delete[] internal; }
};
