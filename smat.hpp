#pragma once

template <typename T, auto W, auto H>
class sMat
{
private:
    T internal[H * W];

public:
    using type = T;
    using size_type = decltype(W);
    using msize_type = uadd_long_t<decltype(W)>; //max size type

    //Iterators
    T *begin() { return &internal[0]; }
    T *end() { return &internal[this->Area() - 1]; }
    const T *begin() const { return &internal[0]; }
    const T *end() const { return &internal[this->Area() - 1]; }
    T *data() { return &internal[0]; }

    //Size
    msize_type Area() const { return Width() * Height(); }
    size_type Width() const { return W; }
    size_type Height() const { return H; }

    //Indexing
    T &At(size_type x, size_type y) { return FastAt((y * (Width()) + x)); }
    T At(size_type x, size_type y) const { return FastAt((y * (Width()) + x)); }

    T &FastAt(msize_type index)
    {
        if (index >= this->Area())
        {
            throw std::out_of_range("FastAt& out of range");
        }
        return internal[index];
    }
    T FastAt(msize_type index) const
    {
        if (index >= this->Area())
        {
            throw std::out_of_range("FastAt out of range");
        }
        return internal[index];
    }
};
