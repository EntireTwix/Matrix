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
#include <stddef.h>
#include <cassert>
#include "dependencies/copy_fast.hpp"

namespace mat
{
    template <typename T, size_t W, size_t H>
    class sMat
    {
    private:
        T _internal[H * W]{};

    public:
        using value_type = T;

        template <size_t W2, size_t H2>
        using base = sMat<T, W2, H2>;

        // compile time dimensions
        static constexpr size_t width = W;
        static constexpr size_t height = H;
        static constexpr size_t area = W * H; 

        // Constructors
        constexpr sMat() noexcept = default;
        template <typename... Args>
        constexpr explicit sMat(Args... list) : _internal{list...} {}

        //Iterators
        constexpr T *begin() noexcept { return &this->_internal[0]; }
        constexpr T *end() noexcept { return &this->_internal[area - 1] + 1; }
        constexpr const T *begin() const noexcept { return &this->_internal[0]; }
        constexpr const T *end() const noexcept { return &this->_internal[area - 1] + 1; }

        //Size
        constexpr size_t get_area() const noexcept { return area; }
        constexpr size_t get_width() const noexcept { return width; }
        constexpr size_t get_height() const noexcept { return height; }

        //Indexing
        constexpr T &at(size_t x, size_t y) noexcept 
        { 
            assert(x < W && y < H);
            return this->_internal[(y * W) + x]; 
        }
        constexpr copy_fast_t<T> at(size_t x, size_t y) const noexcept 
        { 
            assert(x < W && y < H);
            return this->_internal[(y * W) + x]; 
        }

        constexpr T &fast_at(size_t index) noexcept
        {
            assert(index < area);
            return this->_internal[index];
        }
        constexpr copy_fast_t<T> fast_at(size_t index) const noexcept
        {
            assert(index < area);
            return this->_internal[index];
        }
    };
}
