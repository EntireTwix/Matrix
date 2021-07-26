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
#include <cstring>
#include <stdexcept>
#include <stddef.h>

namespace mat
{
    template <typename T>
    class hMat
    {
    private:
        T *_internal = nullptr;
        size_t _w = 0, _h = 0;

    public:
        using type = T;

        hMat() noexcept = default;
        explicit hMat(size_t w, size_t h) noexcept : _w(w), _h(h)
        {
            this->_internal = new T[w * h]{}; //allocate and default initialize
        }
        hMat(const hMat &m) noexcept : _w(m._w), _h(m._h)
        {
            this->_internal = new T[_w * _h]{}; //allocate and default initialize
            memcpy(this->_internal, m._internal, this->Area() * sizeof(T));
        }
        hMat &operator=(const hMat &m) noexcept
        {
            size_t area = Area();
            this->_w = m._w;
            this->_h = m._h;
            if (area != m.Area())
            {
                reallocarray(this->_internal, (_w * _h), sizeof(T)); //allocate
            }
            memcpy(this->_internal, m._internal, this->Area() * sizeof(T));
            return *this;
        }
        hMat(hMat &&m) noexcept : _w(m._w), _h(m._h)
        {
            this->_internal = m._internal; //moving

            //clean up
            m._internal = nullptr;
            m._w = m._h = 0;
        }
        hMat &operator=(hMat &&m) noexcept
        {
            if (_internal)
            {
                delete[] _internal;
            }
            this->_w = m._w;
            this->_h = m._h;
            this->_internal = m._internal; //moving

            //clean up
            m._internal = nullptr;
            m._w = m._h = 0;
            return *this;
        }

        //Iterators
        T *begin() noexcept { return &this->_internal[0]; }
        T *end() noexcept { return &this->_internal[this->Area()]; }
        const T *begin() const noexcept { return &this->_internal[0]; }
        const T *end() const noexcept { return &this->_internal[this->Area()]; }
        T *data() noexcept { return this->_internal; }

        //Size
        size_t Area() const noexcept { return _w * _h; }
        size_t Width() const noexcept { return _w; }
        size_t Height() const noexcept { return _h; }

        //Indexing
        T &At(size_t x, size_t y) { return FastAt((y * (Width()) + x)); }
        T At(size_t x, size_t y) const { return FastAt((y * (Width()) + x)); }

        T &FastAt(size_t index)
        {
            if (index >= this->Area())
            {
                throw std::out_of_range("FastAt& out of range");
            }
            return this->_internal[index];
        }
        T FastAt(size_t index) const
        {
            if (index >= this->Area())
            {
                throw std::out_of_range("FastAt out of range");
            }
            return this->_internal[index];
        }

        void Flatten()
        {
            _w *= _h;
            _h = 1;
        }

        ~hMat()
        {
            if (this->_internal)
            {
                delete[] this->_internal;
            }
        }
    };
}
