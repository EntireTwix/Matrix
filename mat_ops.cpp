#pragma once
#include <stdexcept>

//CopyFast metaprogramming type
template <typename T>
struct copy_fast : std::conditional<std::is_trivially_copyable_v<T>, T, const T &>
{
};
template <typename T>
using copy_fast_t = typename copy_fast<T>::type;

namespace mat
{
    //Arithmetic Operators
    template <typename T>
    constexpr T Add(const T &a, const T &b)
    {
        if (a.Area() != b.Area())
        {
            throw std::invalid_argument("Add: A's Area must match B's Area");
        }
        auto res(a.SizeCopy());
        for (size_t i = 0; i < a.Area(); ++i)
        {
            res.FastAt(i) = a.FastAt(i) + b.FastAt(i);
        }
        return res;
    }
    template <typename T>
    constexpr T Sub(const T &a, const T &b)
    {
        if (a.Area() != b.Area())
        {
            throw std::invalid_argument("Sub: A's Area must match B's Area");
        }
        auto res(a.SizeCopy());
        for (size_t i = 0; i < a.Area(); ++i)
        {
            res.FastAt(i) = a.FastAt(i) - b.FastAt(i);
        }
        return res;
    }
    template <typename T>
    constexpr T Mult(const T &a, const T &b)
    {
        if (a.Area() != b.Area())
        {
            throw std::invalid_argument("Mult: A's Area must match B's Area");
        }
        auto res(a.SizeCopy());
        for (size_t i = 0; i < a.Area(); ++i)
        {
            res.FastAt(i) = a.FastAt(i) * b.FastAt(i);
        }
        return res;
    }
    template <typename T>
    constexpr T Div(const T &a, const T &b)
    {
        if (a.Area() != b.Area())
        {
            throw std::invalid_argument("Div: A's Area must match B's Area");
        }
        auto res(a.SizeCopy());
        for (size_t i = 0; i < a.Area(); ++i)
        {
            res.FastAt(i) = a.FastAt(i) / b.FastAt(i);
        }
        return res;
    }

    //Scalar Arithmetic
    template <typename T>
    constexpr T Add(const T &mat, copy_fast<typename T::type> value)
    {
        auto res(mat.SizeCopy());
        for (auto &e : mat)
        {
            e += value;
        }
        return res;
    }
    template <typename T>
    constexpr T Sub(const T &mat, copy_fast<typename T::type> value)
    {
        auto res(mat.SizeCopy());
        for (auto &e : mat)
        {
            e -= value;
        }
        return res;
    }
    template <typename T>
    constexpr T Mult(const T &mat, copy_fast<typename T::type> value)
    {
        auto res(mat.SizeCopy());
        for (auto &e : mat)
        {
            e *= value;
        }
        return res;
    }
    template <typename T>
    constexpr T Div(const T &mat, copy_fast<typename T::type> value)
    {
        auto res(mat.SizeCopy());
        for (auto &e : mat)
        {
            e /= value;
        }
        return res;
    }
};
