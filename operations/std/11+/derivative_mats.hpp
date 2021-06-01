#pragma once
#include <cstddef>
#include "util_ops.hpp"

namespace mat
{
    template <typename M>
    constexpr auto FlattenedCopy(const M& mat) //unfortunately has to copy 
    {
        if constexpr(is_constexpr_matrix_v<M>)
        {
            typename M::base<M::area, 1> res; //not implementation indepedent
            Copy(mat, res);
            return res;
        }
        else //assumed to be runtime mat
        {
            M res(mat); 
            res.Flatten(); 
            return res; 
        }
    }

    template <typename M>
    constexpr M Resize(const M& mat, size_t Width, size_t Height)
    {     
        M res(Width, Height);
        Copy(mat, res);
        return res;
    }
    template <typename M, size_t W, size_t H>
    constexpr auto Resize(const M& mat)
    {     
        typename M::base<W, H> res;
        Copy(mat, res);
        return res;
    }
}