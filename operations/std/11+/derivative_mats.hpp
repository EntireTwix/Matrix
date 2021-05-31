#pragma once
#include "util_ops.hpp"
#include "is_constexpr_matrix.hpp"

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
}