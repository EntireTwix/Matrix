#pragma once
#include <stdexcept>
#include "cmat.hpp"

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
        constexpr T *end() noexcept { return &internal[this->Area()]; }
        constexpr const T *begin() const noexcept { return &internal[0]; }
        constexpr const T *end() const noexcept { return &internal[this->Area()]; }
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

        sMat SizeCopy() const noexcept { return sMat<T, W, H>(); }
    };
}
