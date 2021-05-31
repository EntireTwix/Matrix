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
            Copy(mat, res);
            return res;
        }
        else if(RuntimeMatrix<M>)
        {
            M res(mat); 
            res.Flatten(); 
            return res; 
        }
    }
}