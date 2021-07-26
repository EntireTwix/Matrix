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
#include <stddef.h>

namespace mat
{
    template <typename T, size_t W, size_t H>
    class sMat
    {
    private:
        T _internal[H * W]{};

    public:
        using type = T;

        template <size_t W2, size_t H2>
        using base = sMat<T, W2, H2>;

        static constexpr size_t width = W;
        static constexpr size_t height = H;

        sMat() noexcept = default;

        //Iterators
        constexpr T *begin() noexcept { return &this->_internal[0]; }
        constexpr T *end() noexcept { return &this->_internal[this->Area()]; }
        constexpr const T *begin() const noexcept { return &this->_internal[0]; }
        constexpr const T *end() const noexcept { return &this->_internal[this->Area()]; }
        constexpr T *data() { return &this->_internal[0]; }

        //Size
        constexpr size_t Area() const noexcept { return W * H; }
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
            return this->_internal[index];
        }
        constexpr T FastAt(size_t index) const
        {
            if (index >= this->Area())
            {
                throw std::out_of_range("FastAt out of range");
            }
            return this->_internal[index];
        }
    };
}
