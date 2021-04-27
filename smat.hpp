#pragma once
#include <stddef.h>
template <auto ret>
constexpr auto ConfirmConstexpr() { return ret; }

template <typename T, size_t W, size_t H>
class sMat
{
private:
    T internal[H * W]{};

public:
    sMat() = default;
    using type = T;

    //Iterators
    constexpr T *begin() { return &internal[0]; }
    constexpr T *end() { return &internal[this->Area() - 1]; }
    constexpr const T *begin() const { return &internal[0]; }
    constexpr const T *end() const { return &internal[this->Area() - 1]; }
    constexpr T *data() { return &internal[0]; }

    //Size
    constexpr size_t Area() const { return Width() * Height(); }
    constexpr size_t Width() const { return W; }
    constexpr size_t Height() const { return H; }

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
};
