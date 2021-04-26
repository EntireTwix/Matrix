#pragma once
#include "imat.hpp"

template <typename T, Integral sz_t, sz_t W, sz_t H>
class sMat : public IMat<T, sz_t>
{
private:
    T internal[H * W];

public:
    //Iterators
    virtual T *begin() override { return &internal[0]; }
    virtual T *end() override { return &internal[this->Area() - 1]; }
    virtual const T *begin() const override { return &internal[0]; }
    virtual const T *end() const override { return &internal[this->Area() - 1]; }
    virtual T *data() { return &internal[0]; }

    //Size
    virtual sz_t Width() const { return W; }
    virtual sz_t Height() const { return H; }

    //Indexing
    virtual T &FastAt(typename IMat<T, sz_t>::msize_type index) override { return internal[index]; }
    virtual T FastAt(typename IMat<T, sz_t>::msize_type index) const override { return internal[index]; }
};
