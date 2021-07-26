#pragma once
#include "depedencies/cmat.hpp"
#include "depedencies/copy_fast.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    constexpr void Fill(M &mat, T&& v)
    {
        for (typename M::type &e : mat)
        {
            e = v;
        }
    }

    template <MATRIX_TYPENAME M, typename F>
    constexpr void ForEach(M &mat, F &&func)
    {
        for (typename M::type &e : mat)
        {
            func(e);
        }
    }

    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
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

    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    constexpr void CopySameArea(const M &src, M2 &dest)
    {
        if (src.Area() != dest.Area())
        {
            throw std::invalid_argument("CopySameArea: must be same Area if of different Matrix types");
        }
        if constexpr(std::is_same_v<M, M2>)
        {
            dest = src; //calling operator=
        }
        else
        {
            for (size_t i = 0; i < src.Area(); ++i)
            {
                dest.FastAt(i) = src.FastAt(i);
            }
        }
    }
};