#pragma once
#include "util_ops.hpp"

namespace mat
{
    template <Matrix M>
    constexpr auto FlattenedCopy(const M& mat) 
    {
        if constexpr(ConstexprMatrix<M>)
        {
            typename M::base<M::area, 1> res;
            CopySameArea(mat, res);
            return res;
        }
        else if(RuntimeMatrix<M>)
        {
            M res(mat); 
            res.Flatten(); 
            return res; 
        }
        return mat;
    }

    template <RuntimeMatrix M>
    constexpr M Resize(const M& mat, size_t Width, size_t Height)
    {     
        M res(Width, Height);
        Copy(mat, res);
        return res;
    }
    template <ConstexprMatrix M, size_t W, size_t H>
    constexpr auto Resize(const M& mat)
    {     
        typename M::base<W, H> res;
        Copy(mat, res);
        return res;
    }
}