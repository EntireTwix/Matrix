// MIT License

// Copyright (c) 2021 William Katz

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
