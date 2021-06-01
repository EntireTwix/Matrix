#pragma once
#include "is_constexpr_mat.hpp" 
#include "copy_fast.hpp"

namespace mat
{
    template <typename M, typename T = typename M::type>
    constexpr void Fill(M &mat, copy_fast_cv_t<T> v)
    {
        for (typename M::type &e : mat)
        {
            e = v;
        }
    }

    template <typename M, typename F>
    constexpr void ForEach(M &mat, F &&func)
    {
        for (typename M::type &e : mat)
        {
            func(e);
        }
    }

    template <typename M, typename M2>
    constexpr void Copy(const M& src, M2& dest)
    {
        if constexpr(std::is_same_v<M, M2> && is_constexpr_matrix_v<M>)
        {
            dest = src;
        }
        else
        {
            for(size_t i = 0; i < dest.Height(); ++i)
            {
                for(size_t j = 0; j < dest.Width(); ++j)
                {
                    if(j < src.Width() && i < src.Height()) 
                    {
                        dest.At(j, i) = src.At(j, i);
                    }
                }
            }
        }
    }

    template <typename M, typename M2>
    constexpr void CopySameArea(const M& src, M2& dest)
    {
        if constexpr(std::is_same_v<M, M2> && is_constexpr_matrix_v<M>)
        {
            dest = src;
        }
        else
        {
            if (src.Area() != dest.Area())
            {
                throw std::invalid_argument("must be same Area if of different Matrix types");
            }
            for(size_t i = 0; i < src.Area(); ++i)
            {
                dest.FastAt(i) = src.FastAt(i);
            }
        }
    }
};
