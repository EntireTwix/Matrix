#pragma once
#include "depedencies/cmat.hpp"
#include "depedencies/copy_fast.hpp"

namespace mat
{
    template <Matrix M, typename T = typename M::type>
    constexpr void Fill(M &mat, T&& v)
    {
        for (typename M::type &e : mat)
        {
            e = v;
        }
    }

    template <Matrix M, typename F>
    constexpr void ForEach(M &mat, F &&func)
    {
        for (typename M::type &e : mat)
        {
            func(e);
        }
    }

    template <Matrix M, Matrix M2>
    constexpr void CopyTrunc(const M &src, M2 &dest)
    {
        for (size_t i = 0; i < dest.Height(); ++i)
        {
            for (size_t j = 0; j < dest.Width(); ++j)
            {
                if (j < src.Width() && i < src.Height())
                {
                    dest.At(j, i) = src.At(j, i);
                }
            }
        }
    }

    template <Matrix M, Matrix M2>
    constexpr void CopySameArea(const M &src, M2 &dest)
    {
        if (src.Area() != dest.Area())
        {
            throw std::invalid_argument("must be same Area if of different Matrix types");
        }
        //may replace with memcpy
        for (size_t i = 0; i < src.Area(); ++i)
        {
            dest.FastAt(i) = src.FastAt(i);
        }
    }
};