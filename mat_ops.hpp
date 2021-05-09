#pragma once
#include <stdexcept>
#include <ostream>
#include "cmat.hpp"

template <typename T>
concept Printable = requires(T a)
{
    {std::cout<<a}->std::same_as<std::ostream&>;
};
template <typename T, typename T2>
concept Addable = requires(T a, T2 b)
{
    {a+b}->std::convertible_to<T>;
};
template <typename T, typename T2>
concept Subtractable = requires(T a, T2 b)
{
    {a-b}->std::convertible_to<T>;
};
template <typename T, typename T2>
concept Multipliable = requires(T a, T2 b)
{
    {a*b}->std::convertible_to<T>;
};
template <typename T, typename T2>
concept Divideable = requires(T a, T2 b)
{
    {a/b}->std::convertible_to<T>;
};

namespace mat
{
    //Print
    template <Matrix M>
    requires Printable<typename M::type>
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

    //Generic Operations
    template <Matrix M, Matrix M2, typename F>
    constexpr M Operation(const M& a, const M2& b, F&& func)
    {
        if(b.Area() < a.Area()) 
        {
            throw std::invalid_argument("arg is too big");
        }
        M res(a.SizeCopy());
        for(size_t i = 0; i < a.Area(); ++i)
        {
            res.FastAt(i) = func(a.FastAt(i), b.FastAt(i));
        }
        return res;
    }
    template <Matrix M, Matrix M2, typename F>
    constexpr void OperationMut(M& a, const M2& b, F&& func)
    {
        if(b.Area() < a.Area()) 
        {
            throw std::invalid_argument("arg is too big");
        }
        for(size_t i = 0; i < a.Area(); ++i)
        {
            a.FastAt(i) =func(a.FastAt(i), b.FastAt(i));
        }
    }
    template <Matrix M, typename F, typename T = typename M::type>
    constexpr M ScalarOperation(const M& mat, copy_fast_cv_t<T> v, F&& func) noexcept
    {
        M res(mat.SizeCopy());
        for(size_t i = 0; i < mat.Area(); ++i)
        {
            res.FastAt(i) = func(mat.FastAt(i), v);
        }
        return res;
    }
    template <Matrix M, typename F, typename T = typename M::type>
    constexpr void ScalarOperationMut(M& mat, copy_fast_cv_t<T> v, F&& func)  noexcept
    {
        for(T& e : mat)
        {
            e = func(e, v);
        }
    }

    //Add
    template <Matrix M, Matrix M2>
    requires Addable<typename M::type, typename M2::type>
    constexpr M Add(const M& a, const M2& b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a+b; }); }
    template <Matrix M, Matrix M2>
    requires Addable<typename M::type, typename M2::type>
    constexpr void AddMut(M& a, const M2& b) { return OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ return a+b; }); }
    template <Matrix M, typename T = typename M::type>
    requires Addable<typename M::type, T>
    constexpr M ScalarAdd(const M& mat, copy_fast_cv_t<T> v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a+b; }); }
    template <Matrix M, typename T = typename M::type>
    requires Addable<typename M::type, T>
    constexpr void ScalarAddMut(M& mat, copy_fast_cv_t<T> v)  noexcept { return ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ return a+b; }); }

    //Sub
    template <Matrix M, Matrix M2>
    requires Subtractable<typename M::type, typename M2::type>
    constexpr M Sub(const M& a, const M2& b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a-b; }); }
    template <Matrix M, Matrix M2>
    requires Subtractable<typename M::type, typename M2::type>
    constexpr void SubMut(M& a, const M2& b) { return OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ return a-b; }); }
    template <Matrix M, typename T = typename M::type>
    requires Subtractable<typename M::type, T>
    constexpr M ScalarSub(const M& mat, copy_fast_cv_t<T> v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a-b; }); }
    template <Matrix M, typename T = typename M::type>
    requires Subtractable<typename M::type, T>
    constexpr void ScalarSubMut(M& mat, copy_fast_cv_t<T> v)  noexcept { return ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ return a-b; }); }

    //Mul
    template <Matrix M, Matrix M2>
    requires Multipliable<typename M::type, typename M2::type>
    constexpr M Mul(const M& a, const M2& b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a*b; }); }
    template <Matrix M, Matrix M2>
    requires Multipliable<typename M::type, typename M2::type>
    constexpr void MulMut(M& a, const M2& b) { return OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ return a*b; }); }
    template <Matrix M, typename T = typename M::type>
    requires Multipliable<typename M::type, T>
    constexpr M ScalarMul(const M& mat, copy_fast_cv_t<T> v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a*b; }); }
    template <Matrix M, typename T = typename M::type>
    requires Multipliable<typename M::type, T>
    constexpr void ScalarMulMut(M& mat, copy_fast_cv_t<T> v)  noexcept { return ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ return a*b; }); }

    //Div
    template <Matrix M, Matrix M2>
    requires Divideable<typename M::type, typename M2::type>
    constexpr M Div(const M& a, const M2& b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a/b; }); }
    template <Matrix M, Matrix M2>
    requires Divideable<typename M::type, typename M2::type>
    constexpr void DivMut(M& a, const M2& b) { return OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ return a/b; }); }
    template <Matrix M, typename T = typename M::type>
    requires Divideable<typename M::type, T>
    constexpr M ScalarDiv(const M& mat, copy_fast_cv_t<T> v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a/b; }); }
    template <Matrix M, typename T = typename M::type>
    requires Divideable<typename M::type, T>
    constexpr void ScalarDivMut(M& mat, copy_fast_cv_t<T> v)  noexcept { return ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ return a/b; }); }
};
