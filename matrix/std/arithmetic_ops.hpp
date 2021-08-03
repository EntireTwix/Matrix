#pragma once
#include "generic_ops.hpp"

#ifdef HAS_CONCEPTS 
template <typename T, typename T2> 
concept Addable = requires(T a, T2 b) { {a+b}->std::convertible_to<T>; };
template <typename T, typename T2> 
concept AddableAs = requires(T a, T2 b) { {a+=b}->std::convertible_to<T>; };
template <typename T, typename T2>
concept Subtractable = requires(T a, T2 b) { {a-b}->std::convertible_to<T>; };
template <typename T, typename T2> 
concept SubtractableAs = requires(T a, T2 b) { {a-=b}->std::convertible_to<T>; };
template <typename T, typename T2>
concept Multipliable = requires(T a, T2 b) { {a*b}->std::convertible_to<T>; };
template <typename T, typename T2>
concept MultipliableAs = requires(T a, T2 b) { {a*=b}->std::convertible_to<T>; };
template <typename T, typename T2>
concept Divideable = requires(T a, T2 b) { {a/b}->std::convertible_to<T>; };
template <typename T, typename T2>
concept DivideableAs = requires(T a, T2 b) { {a/=b}->std::convertible_to<T>; };
template <typename T, typename T2>
concept Powable = requires(T a, T2 b)
{
    { a = 1 };
    { 0 < b } -> std::same_as<bool>;
    { a *= a };
    { a = a};
};
#endif


namespace mat
{
    //Add
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Addable<typename M::type, typename M2::type>
    #endif
    constexpr M AddMat(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M2::type> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "AddMat: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return a+b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires AddableAs<typename M::type, typename M2::type>
    #endif
    constexpr void AddMatMut(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M2::type> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "AddMatMut: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); a+=b; }); }
    template <MATRIX_TYPENAME M, typename T>
    #ifdef HAS_CONCEPTS 
    requires Addable<typename M::type, T>
    #endif
    constexpr M Add(const M& mat, T&& v) { return ScalarOperation(mat, std::move(v), [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Add: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return a+b; }); }
    template <MATRIX_TYPENAME M, typename T>
    #ifdef HAS_CONCEPTS 
    requires AddableAs<typename M::type, T>
    #endif
    constexpr void AddMut(M& mat, T&& v)  { ScalarOperationMut(mat, std::move(v), [](typename M::type& a, copy_fast_cv_t<T> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "AddMut: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); a+=b; }); }

    //Sub
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Subtractable<typename M::type, typename M2::type>
    #endif
    constexpr M SubMat(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M2::type> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "SubMat: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return a-b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires SubtractableAs<typename M::type, typename M2::type>
    #endif
    constexpr void SubMatMut(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M2::type> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "SubMatMut: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); a-=b; }); }
    template <MATRIX_TYPENAME M, typename T>
    #ifdef HAS_CONCEPTS 
    requires Subtractable<typename M::type, T>
    #endif
    constexpr M Sub(const M& mat, T&& v) { return ScalarOperation(mat, std::move(v), [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Sub: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return a-b; }); }
    template <MATRIX_TYPENAME M, typename T>
    #ifdef HAS_CONCEPTS 
    requires SubtractableAs<typename M::type, T>
    #endif
    constexpr void SubMut(M& mat, T&& v)  { ScalarOperationMut(mat, std::move(v), [](typename M::type& a, copy_fast_cv_t<T> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "SubMut: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); a-=b; }); }

    //Mul
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Multipliable<typename M::type, typename M2::type>
    #endif
    constexpr M MulMat(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M2::type> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "MulMat: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return a*b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires MultipliableAs<typename M::type, typename M2::type>
    #endif
    constexpr void MulMatMut(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M2::type> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "MulMatMut: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); a*=b; }); }
    template <MATRIX_TYPENAME M, typename T>
    #ifdef HAS_CONCEPTS 
    requires Multipliable<typename M::type, T>
    #endif
    constexpr M Mul(const M& mat, T&& v) { return ScalarOperation(mat, std::move(v), [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Mul: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return a*b; }); }
    template <MATRIX_TYPENAME M, typename T>
    #ifdef HAS_CONCEPTS 
    requires MultipliableAs<typename M::type, T>
    #endif
    constexpr void MulMut(M& mat, T&& v)  { ScalarOperationMut(mat, std::move(v), [](typename M::type& a, copy_fast_cv_t<T> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "MulMut: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); a*=b; }); }

    //Div
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Divideable<typename M::type, typename M2::type>
    #endif
    constexpr M DivMat(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M2::type> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "DivMat: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return a/b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires DivideableAs<typename M::type, typename M2::type>
    #endif
    constexpr void DivMatMut(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M2::type> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "DivMatMut: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); a/=b; }); }
    template <MATRIX_TYPENAME M, typename T>
    #ifdef HAS_CONCEPTS 
    requires Divideable<typename M::type, T>
    #endif
    constexpr M Div(const M& mat, T&& v) { return ScalarOperation(mat, std::move(v), [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Div: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return a/b; }); }
    template <MATRIX_TYPENAME M, typename T>
    #ifdef HAS_CONCEPTS 
    requires DivideableAs<typename M::type, T>
    #endif
    constexpr void DivMut(M& mat, T&& v)  { ScalarOperationMut(mat, std::move(v), [](typename M::type& a, copy_fast_cv_t<T> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "DivMut: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); a/=b; }); }
    
    //Pow
    template <typename T, typename T2>
    constexpr T Pow(T base, T2 power) 
    {
        T res = 1;
        for(size_t i = 0; i < power; ++i) 
        {
            res *= base;
        }
        return res;
    }
    template <typename T, typename T2>
    constexpr void PowMut(T& base, T2 power) 
    {
        T res = 1;
        for(size_t i = 0; i < power; ++i) 
        {
            res *= base;
        }
        base = res;
    }

    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Powable<typename M::type, typename M2::type>
    #endif
    constexpr M PowMat(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M2::type> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "DivMat: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return Pow(a, b); }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Powable<typename M::type, typename M2::type>
    #endif
    constexpr void PowMatMut(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M2::type> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "DivMatMut: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); PowMut(a, b); }); }
    template <MATRIX_TYPENAME M, typename T>
    #ifdef HAS_CONCEPTS 
    requires Powable<typename M::type, T>
    #endif
    constexpr M Pow(const M& mat, T&& v) { return ScalarOperation(mat, std::move(v), [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Div: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return Pow(a, b); }); }
    template <MATRIX_TYPENAME M, typename T>
    #ifdef HAS_CONCEPTS 
    requires Powable<typename M::type, T>
    #endif
    constexpr void PowMut(M& mat, T&& v)  { ScalarOperationMut(mat, std::move(v), [](typename M::type& a, copy_fast_cv_t<T> b){ EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "DivMut: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX")); PowMut(a, b); }); }
};
