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
#include <type_traits>
#include <functional>
#include <stddef.h>

//CopyFast metaprogramming type
template <typename T>
struct copy_fast : std::conditional<std::is_trivially_copyable_v<T>, T, const T &>
{
};
template <typename T>
using copy_fast_t = typename copy_fast<T>::type;

namespace mat
{
    template <typename T, size_t W, size_t H>
    class sMat
    {
    private:
        T internal[H * W]{};

    public:
        using type = T;

        sMat() noexcept = default;

        //Iterators
        constexpr T *begin() noexcept { return &internal[0]; }
        constexpr T *end() noexcept { return &internal[this->Area() - 1]; }
        constexpr const T *begin() const noexcept { return &internal[0]; }
        constexpr const T *end() const noexcept { return &internal[this->Area() - 1]; }
        constexpr T *data() { return &internal[0]; }

        //Size
        constexpr size_t Area() const noexcept { return Width() * Height(); }
        constexpr size_t Width() const noexcept { return W; }
        constexpr size_t Height() const noexcept { return H; }

        //Indexing
        constexpr T &At(size_t x, size_t y) { return FastAt((y * (Width()) + x)); }
        constexpr T At(size_t x, size_t y) const { return FastAt((y * (Width()) + x)); }

        constexpr T &FastAt(size_t index)
        {
            if (index >= this->Area())
            {
                throw std::out_of_range("FastAt& out of range");
            }
            return internal[index];
        }
        constexpr T FastAt(size_t index) const
        {
            if (index >= this->Area())
            {
                throw std::out_of_range("FastAt out of range");
            }
            return internal[index];
        }

        //Other
        constexpr sMat Operation(const sMat &mat, std::function<T(copy_fast_t<T>, copy_fast_t<T>)> &&func)
        {
            sMat res;
            for (size_t i = 0; i < res.Area(); ++i)
            {
                res.internal[i] = func(this->internal[i], mat.internal[i]);
            }
            return res;
        }
        constexpr void Operation_M(const sMat &mat, std::function<void(T &, copy_fast_t<T>)> &&func)
        {
            for (size_t i = 0; i < Area(); ++i)
            {
                func(this->internal[i], mat.internal[i]);
            }
        }
        constexpr sMat ScalarOperation(copy_fast_t<T> value, std::function<T(copy_fast_t<T>, copy_fast_t<T>)> &&func)
        {
            sMat res;
            for (size_t i = 0; i < res.Area(); ++i)
            {
                res = func(this->internal[i], value);
            }
            return res;
        }
        constexpr void ScalarOperation_M(copy_fast_t<T> value, std::function<void(T &, copy_fast_t<T>)> &&func)
        {
            for (T &e : *this)
            {
                func(e, value);
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const sMat &mat) noexcept
        {
            for (size_t i = 0; i < mat.Height(); ++i)
            {
                for (size_t j = 0; j < mat.Width(); ++j)
                {
                    os << mat.At(j, i) << ' ';
                }
                os << '\n';
            }
            return os;
        }
    };
}
