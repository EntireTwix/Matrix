#pragma once
#include <vector>
#include <string.h> // for memcpy
#include "imat.hpp"

template <typename T, Integral sz_t = size_t>
class hMat : public IMat<T, sz_t>
{
private:
    T *internal;
    sz_t w = 0, h = 0;

public:
    hMat() = default;
    explicit hMat(sz_t w, sz_t h) : w(w), h(h)
    {
        this->internal = new T[w * h]{}; //allocate and default initialize
    }
    hMat(const hMat &m) : w(m.w), h(m.h)
    {
        this->internal = new T[w * h]{}; //allocate and default initialize
        memcpy(&this->internal, &m.internal, m.Area());
    }
    hMat(hMat &&m) : w(m.w), h(m.h)
    {
        this->internal = std::move(m.internal); //moving
        m.w = m.h = 0;                          //clean up
    }

    //Iterators
    virtual T *begin() override { return &internal[0]; }
    virtual T *end() override { return &internal[this->Area() - 1]; }
    virtual const T *begin() const override { return &internal[0]; }
    virtual const T *end() const override { return &internal[this->Area() - 1]; }
    virtual T *data() { return internal; }

    //Size
    virtual sz_t Width() const { return w; }
    virtual sz_t Height() const { return h; }

    //Indexing
    virtual T &FastAt(typename IMat<T, sz_t>::msize_type index) override { return internal[index]; }
    virtual T FastAt(typename IMat<T, sz_t>::msize_type index) const override { return internal[index]; }

    ~hMat() { delete[] internal; }
};
