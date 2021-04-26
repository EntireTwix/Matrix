#pragma once
#include <stddef.h>
#include <concepts>
#include <type_traits>

template <typename T>
concept Integral = std::is_integral_v<T> &&std::is_unsigned_v<T>;

template <typename T, Integral sz_t = size_t>
class IMat
{
public:
    using type = T;
    using size_type = sz_t;
    using msize_type = decltype(std::numeric_limits<sz_t>::max() * std::numeric_limits<sz_t>::max()); //max size type

    //Iterators
    virtual T *begin() = 0;
    virtual T *end() = 0;
    virtual const T *begin() const = 0;
    virtual const T *end() const = 0;
    virtual T *data() = 0;

    //Size
    msize_type Area() const { return Width() * Height(); }
    virtual size_type Width() const = 0;
    virtual size_type Height() const = 0;

    //Indexing
    T &At(size_type x, size_type y) { return FastAt((y * (Width()) + x)); }
    T At(size_type x, size_type y) const { return FastAt((y * (Width()) + x)); }

    virtual T &FastAt(msize_type) = 0;
    virtual T FastAt(msize_type) const = 0;
};

template <typename M>
concept Mat = std::is_base_of_v<IMat<typename M::type, typename M::size_type>, M>;
