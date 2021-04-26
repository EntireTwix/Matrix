#pragma once
#include <stddef.h>
#include <stdint.h>
#include <concepts>
#include <type_traits>

template <typename T>
requires std::is_unsigned_v<T> struct uadd_long : std::type_identity<T>{};
template <>
struct uadd_long<uint8_t> : std::type_identity<uint16_t>{};
template <>
struct uadd_long<uint16_t> : std::type_identity<uint32_t>{};
template <>
struct uadd_long<uint32_t> : std::type_identity<uint64_t>{};
template <>
struct uadd_long<uint64_t> : std::type_identity<uint64_t>{};

template <typename T>
using uadd_long_t = typename uadd_long<T>::type;

template <typename T>
concept Integral = std::is_integral_v<T> &&std::is_unsigned_v<T>;

template <typename T, Integral sz_t = size_t>
class IMat
{
public:
    using type = T;
    using size_type = sz_t;
    using msize_type = uadd_long_t<sz_t>; //max size type

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
