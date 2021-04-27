#pragma once
#include <stddef.h>

template <typename T, size_t W, size_t H>
class sMat
{
private:
    T internal[H * W];

public:
    using type = T;

    //Iterators
    T *begin() { return &internal[0]; }
    T *end() { return &internal[this->Area() - 1]; }
    const T *begin() const { return &internal[0]; }
    const T *end() const { return &internal[this->Area() - 1]; }
    T *data() { return &internal[0]; }

    //Size
    size_t Area() const { return Width() * Height(); }
    size_t Width() const { return W; }
    size_t Height() const { return H; }

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
};
