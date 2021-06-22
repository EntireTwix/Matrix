#pragma once
#include "depedencies/v_sep.hpp"
#include "util_ops.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M>
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

    template <RUNTIME_MATRIX_TYPENAME M>
    constexpr M Resize(const M& mat, size_t Width, size_t Height)
    {    
        if(mat.Width() == Width && mat.Height() == Height)
        {
            return mat;
        }
        else
        {
            M res(Width, Height);
            CopyTrunc(mat, res);
            return res;
        }
    }
    template <CONSTEXPR_MATRIX_TYPENAME M, size_t W, size_t H>
    constexpr auto Resize(const M& mat)
    {    
        if(mat.Width() == W && mat.Height() == H)
        {
            return mat;
        }
        else 
        {
            typename M::base<W, H> res;
            CopyTrunc(mat, res);
            return res;
        }
    }
}