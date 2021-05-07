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
    template <Matrix M, Matrix M2, Matrix M3 = M>
    constexpr M3 Add(const M& a, const M2& b)
    {
        M3 res(a.SizeCopy());
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
    template <Matrix M, Matrix M2, typename T>
    constexpr M2 ScalarAdd(const M& mat, copy_fast_cv_t<T> v)
    {
        M2 res(mat.SizeCopy());
        for(size_t i = 0; i < mat.Area(); ++i)
        {
            res.FastAt(i) = mat.FastAt(i) + v;
        }
        return res;
    }
    template <Matrix M, typename T>
    constexpr void ScalarAddM(M& mat, copy_fast_cv_t<T> v)
    {
        for(T& e : mat)
        {
            e += v;
        }
    }

    //Sub
    template <Matrix M, Matrix M2, Matrix M3 = M>
    constexpr M3 Sub(const M& a, const M2& b)
    {
        M3 res(a.SizeCopy());
        for(size_t i = 0; i < a.Area(); ++i)
        {
            res.FastAt(i) = a.FastAt(i) - b.FastAt(i);
        }
        return res;
    }
    template <Matrix M, Matrix M2>
    constexpr void SubMut(M& a, const M2& b)
    {
        for(size_t i = 0; i < a.Area(); ++i)
        {
            a.FastAt(i) -= b.FastAt(i);
        }
    }
    template <Matrix M, Matrix M2, typename T>
    constexpr M2 ScalarSub(const M& mat, copy_fast_cv_t<T> v)
    {
        M2 res(mat.SizeCopy());
        for(size_t i = 0; i < mat.Area(); ++i)
        {
            res.FastAt(i) = mat.FastAt(i) - v;
        }
        return res;
    }
    template <Matrix M, typename T>
    constexpr void ScalarSubM(M& mat, copy_fast_cv_t<T> v)
    {
        for(T& e : mat)
        {
            e -= v;
        }
    }

    //Mul
    template <Matrix M, Matrix M2, Matrix M3 = M>
    constexpr M3 Mul(const M& a, const M2& b)
    {
        M3 res(a.SizeCopy());
        for(size_t i = 0; i < a.Area(); ++i)
        {
            res.FastAt(i) = a.FastAt(i) * b.FastAt(i);
        }
        return res;
    }
    template <Matrix M, Matrix M2>
    constexpr void MulMut(M& a, const M2& b)
    {
        for(size_t i = 0; i < a.Area(); ++i)
        {
            a.FastAt(i) *= b.FastAt(i);
        }
    }
    template <Matrix M, Matrix M2, typename T>
    constexpr M2 ScalarMul(const M& mat, copy_fast_cv_t<T> v)
    {
        M2 res(mat.SizeCopy());
        for(size_t i = 0; i < mat.Area(); ++i)
        {
            res.FastAt(i) = mat.FastAt(i) * v;
        }
        return res;
    }
    template <Matrix M, typename T>
    constexpr void ScalarMulM(M& mat, copy_fast_cv_t<T> v)
    {
        for(T& e : mat)
        {
            e *= v;
        }
    }

    //Div
    template <Matrix M, Matrix M2, Matrix M3 = M>
    constexpr M3 Div(const M& a, const M2& b)
    {
        M3 res(a.SizeCopy());
        for(size_t i = 0; i < a.Area(); ++i)
        {
            res.FastAt(i) = a.FastAt(i) / b.FastAt(i);
        }
        return res;
    }
    template <Matrix M, Matrix M2>
    constexpr void DivMut(M& a, const M2& b)
    {
        for(size_t i = 0; i < a.Area(); ++i)
        {
            a.FastAt(i) /= b.FastAt(i);
        }
    }
    template <Matrix M, Matrix M2, typename T>
    constexpr M2 ScalarDiv(const M& mat, copy_fast_cv_t<T> v)
    {
        M2 res(mat.SizeCopy());
        for(size_t i = 0; i < mat.Area(); ++i)
        {
            res.FastAt(i) = mat.FastAt(i) / v;
        }
        return res;
    }
    template <Matrix M, typename T>
    constexpr void ScalarDivM(M& mat, copy_fast_cv_t<T> v)
    {
        for(T& e : mat)
        {
            e /= v;
        }
    }

};
