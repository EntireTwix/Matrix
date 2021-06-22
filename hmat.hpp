#pragma once
#include <stdexcept>
#include <stddef.h>

namespace mat
{
    template <typename T>
    class hMat
    {
    private:
        T *internal = nullptr;
        size_t w = 0, h = 0;

    public:
        using type = T;

        hMat() noexcept = default;
        explicit hMat(size_t w, size_t h) noexcept : w(w), h(h)
        {
            this->internal = new T[w * h]{}; //allocate and default initialize
        }
        hMat(const hMat &m) noexcept : w(m.w), h(m.h)
        {
            this->internal = new T[w * h]{}; //allocate and default initialize
            //may replace with memcpy
            for (size_t i = 0; i < this->Area(); ++i)
            {
                this->internal[i] = m.internal[i];
            }
        }
        hMat &operator=(const hMat &m) noexcept
        {
            if((w != m.w || h != m.h) && (Area() != m.Area()))
            {
                if (internal)
                {
                    delete[] internal;
                }
                w = m.w;
                h = m.h;
                this->internal = new T[w * h]{}; //allocate and default initialize
            }
            else //same area wrong dims
            {
                w = m.w;
                h = m.h;
            }
            //may replace with memcpy
            for (size_t i = 0; i < this->Area(); ++i)
            {
                this->internal[i] = m.internal[i];
            }
            return *this;
        }
        hMat(hMat &&m) noexcept : w(m.w), h(m.h)
        {
            this->internal = m.internal; //moving

            //clean up
            m.internal = nullptr;
            m.w = m.h = 0;
        }
        hMat &operator=(hMat &&m) noexcept
        {
            if (internal)
            {
                delete[] internal;
            }
            w = m.w;
            h = m.h;
            this->internal = m.internal; //moving

            //clean up
            m.internal = nullptr;
            m.w = m.h = 0;
            return *this;
        }

        //Iterators
        T *begin() noexcept
        {
            return &internal[0];
        }
        T *end() noexcept { return &internal[this->Area()]; }
        const T *begin() const noexcept { return &internal[0]; }
        const T *end() const noexcept { return &internal[this->Area()]; }
        T *data() noexcept { return internal; }

        //Size
        size_t Area() const noexcept { return Width() * Height(); }
        size_t Width() const noexcept { return w; }
        size_t Height() const noexcept { return h; }

        //Indexing
        T &At(size_t x, size_t y) { return FastAt((y * (Width()) + x)); }
        T At(size_t x, size_t y) const { return FastAt((y * (Width()) + x)); }

        T &FastAt(size_t index)
        {
            if (index >= this->Area())
            {
                throw std::out_of_range("FastAt& out of range");
            }
            return internal[index];
        }
        T FastAt(size_t index) const
        {
            if (index >= this->Area())
            {
                throw std::out_of_range("FastAt out of range");
            }
            return internal[index];
        }

        void Flatten() { w *= h; h = 1; }

        ~hMat() { delete[] internal; }
    };
}
