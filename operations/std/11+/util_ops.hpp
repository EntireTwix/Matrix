#pragma once
#include "cmat.hpp" 
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
        
        if constexpr(std::same_as<M, M2>)
        {
            dest = src;
        }
        else
        {
            if (src.Area() != dest.Area())
            {
                throw std::invalid_argument("must be same Area if of different typename types");
            }
            for(size_t i = 0; i < src.Area(); ++i)
            {
                dest.FastAt(i) = src.FastAt(i);
            }
        }
    }
};
