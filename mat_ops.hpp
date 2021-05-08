#pragma once
#include <stdexcept>
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
        if(b.Area() < a.Area()) 
        {
            throw std::invalid_argument("arg is too big");
        }
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
        if(b.Area() < a.Area()) 
        {
            throw std::invalid_argument("arg is too big");
        }
        for(size_t i = 0; i < a.Area(); ++i)
        {
            a.FastAt(i) += b.FastAt(i);
        }
    }
    template <Matrix M, typename T = typename M::type>
    constexpr M ScalarAdd(const M& mat, copy_fast_cv_t<T> v) noexcept
    {
        M res(mat.SizeCopy());
        for(size_t i = 0; i < mat.Area(); ++i)
        {
            res.FastAt(i) = mat.FastAt(i) + v;
        }
        return res;
    }
    template <Matrix M, typename T = typename M::type>
    constexpr void ScalarAddMut(M& mat, copy_fast_cv_t<T> v)  noexcept
    {
        for(T& e : mat)
        {
            e += v;
        }
    }

    //Sub
    template <Matrix M, Matrix M2>
    constexpr M Sub(const M& a, const M2& b)
    {
        if(b.Area() < a.Area()) 
        {
            throw std::invalid_argument("arg is too big");
        }
        M res(a.SizeCopy());
        for(size_t i = 0; i < a.Area(); ++i)
        {
            res.FastAt(i) = a.FastAt(i) - b.FastAt(i);
        }
        return res;
    }
    template <Matrix M, Matrix M2>
    constexpr void SubMut(M& a, const M2& b)
    {
        if(b.Area() < a.Area()) 
        {
            throw std::invalid_argument("arg is too big");
        }
        for(size_t i = 0; i < a.Area(); ++i)
        {
            a.FastAt(i) -= b.FastAt(i);
        }
    }
    template <Matrix M, typename T = typename M::type>
    constexpr M ScalarSub(const M& mat, copy_fast_cv_t<T> v) noexcept
    {
        M res(mat.SizeCopy());
        for(size_t i = 0; i < mat.Area(); ++i)
        {
            res.FastAt(i) = mat.FastAt(i) - v;
        }
        return res;
    }
    template <Matrix M, typename T = typename M::type>
    constexpr void ScalarSubMut(M& mat, copy_fast_cv_t<T> v) noexcept
    {
        for(T& e : mat)
        {
            e -= v;
        }
    }

    //Mul
    template <Matrix M, Matrix M2>
    constexpr M Mul(const M& a, const M2& b)
    {
        if(b.Area() < a.Area()) 
        {
            throw std::invalid_argument("arg is too big");
        }
        M res(a.SizeCopy());
        for(size_t i = 0; i < a.Area(); ++i)
        {
            res.FastAt(i) = a.FastAt(i) * b.FastAt(i);
        }
        return res;
    }
    template <Matrix M, Matrix M2>
    constexpr void MulMut(M& a, const M2& b)
    {
        if(b.Area() < a.Area()) 
        {
            throw std::invalid_argument("arg is too big");
        }
        for(size_t i = 0; i < a.Area(); ++i)
        {
            a.FastAt(i) *= b.FastAt(i);
        }
    }
    template <Matrix M, typename T = typename M::type>
    constexpr M ScalarMul(const M& mat, copy_fast_cv_t<T> v) noexcept
    {
        M res(mat.SizeCopy());
        for(size_t i = 0; i < mat.Area(); ++i)
        {
            res.FastAt(i) = mat.FastAt(i) * v;
        }
        return res;
    }
    template <Matrix M, typename T = typename M::type>
    constexpr void ScalarMulMut(M& mat, copy_fast_cv_t<T> v) noexcept
    {
        for(T& e : mat)
        {
            e *= v;
        }
    }

    //Div
    template <Matrix M, Matrix M2>
    constexpr M Div(const M& a, const M2& b)
    {
        if(b.Area() < a.Area()) 
        {
            throw std::invalid_argument("arg is too big");
        }
        M res(a.SizeCopy());
        for(size_t i = 0; i < a.Area(); ++i)
        {
            res.FastAt(i) = a.FastAt(i) / b.FastAt(i);
        }
        return res;
    }
    template <Matrix M, Matrix M2>
    constexpr void DivMut(M& a, const M2& b)
    {
        if(b.Area() < a.Area()) 
        {
            throw std::invalid_argument("arg is too big");
        }
        for(size_t i = 0; i < a.Area(); ++i)
        {
            a.FastAt(i) /= b.FastAt(i);
        }
    }
    template <Matrix M, typename T>
    constexpr M ScalarDiv(const M& mat, copy_fast_cv_t<T> v) noexcept
    {
        M res(mat.SizeCopy());
        for(size_t i = 0; i < mat.Area(); ++i)
        {
            res.FastAt(i) = mat.FastAt(i) / v;
        }
        return res;
    }
    template <Matrix M, typename T>
    constexpr void ScalarDivMut(M& mat, copy_fast_cv_t<T> v) noexcept
    {
        for(T& e : mat)
        {
            e /= v;
        }
    }

};
