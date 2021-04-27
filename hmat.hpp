#pragma once
#include <stddef.h>

template <typename T>
class hMat
{
private:
    T *internal = nullptr;
    size_t w = 0, h = 0;

public:
    using type = T;

    hMat() = default;
    explicit hMat(size_t w, size_t h) : w(w), h(h)
    {
        this->internal = new T[w * h]{}; //allocate and default initialize
    }
    hMat(const hMat &m) : w(m.w), h(m.h)
    {
        this->internal = new T[w * h]{}; //allocate and default initialize
        for (size_t i = 0; i < this->Area(); ++i)
        {
            this->internal[i] = m.internal[i];
        }
    }
    hMat(hMat &&m) : w(m.w), h(m.h)
    {
        this->internal = std::move(m.internal); //moving
        m.w = m.h = 0;                          //clean up
    }

    //Iterators
    T *begin() { return &internal[0]; }
    T *end() { return &internal[this->Area() - 1]; }
    const T *begin() const { return &internal[0]; }
    const T *end() const { return &internal[this->Area() - 1]; }
    T *data() { return internal; }

    //Size
    size_t Area() const { return Width() * Height(); }
    size_t Width() const { return w; }
    size_t Height() const { return h; }
    void Resize(size_t new_w, size_t new_h)
    {
        size_t new_area = new_w * new_h;
        T *temp = new T[new_area]{};
        for (size_t i = 0; i < this->Area() && i < new_area; ++i)
        {
            temp[i] = this->internal[i];
        }
        w = new_w;
        h = new_h;
        std::swap(this->internal, temp);
        delete[] temp;
    }

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

    ~hMat() { delete[] internal; }
};
