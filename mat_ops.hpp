#pragma once
#include <ostream>
#include "cmat.hpp"

namespace mat
{
    //Print
    template <Matrix M>
    std::ostream &operator<<(std::ostream &os, const M &mat)
    {
        for (size_t i = 0; i < mat.Height(); ++i)
        {
            for (size_t j = 0; j < mat.Width(); ++j)
            {
                os << mat.At(j, i) << ' ';
            }
            os << '\n';
        }
        return os;
    }

    //Add
    template <Matrix M, Matrix M2>
    constexpr M Add(const M& a, const M2& b)
    {
        M res(a.SizeCopy());
        for(size_t i = 0; i < a.Area(); ++i)
        {
            res.FastAt(i) = a.FastAt(i) + b.FastAt(i);
        }
        return res;
    }
    template <Matrix M, Matrix M2>
    constexpr void AddMut(M& a, const M2& b)
    {
        for(size_t i = 0; i < a.Area(); ++i)
        {
            a.FastAt(i) += b.FastAt(i);
        }
    }
    template <Matrix M>
    constexpr M ScalarAdd(const M& mat, copy_fast_t<typename M::type> v)
    {
        M res(mat.SizeCopy());
        for(size_t i = 0; i < mat.Area(); ++i)
        {
            res.FastAt(i) = mat.FastAt(i) + v;
        }
        return res;
    }
    template <Matrix M>
    constexpr void ScalarAddM(M& mat, copy_fast_t<typename M::type> v)
    {
        for(size_t i = 0; i < mat.Area(); ++i)
        {
            mat.FastAt(i) += v;
        }
    }



};