#pragma once
#include <type_traits>
#include <stddef.h>
#include "copy_fast.hpp"

#ifdef __cpp_concepts
#if __cplusplus >= __cpp_concepts
#define HAS_CONCEPTS true
#endif
#endif

#ifdef HAS_CONCEPTS
#define EXEC_IF_20(expr) expr
#define EXEC_IF_20_ELSE(expr, expr2) expr
#define EXEC_IF_NOT_20(expr)
#define EXEC_IF_NOT_20_ELSE(expr, expr2) expr2
#else
#define EXEC_IF_20(expr)
#define EXEC_IF_20_ELSE(expr, expr2) expr2
#define EXEC_IF_NOT_20(expr) expr
#define EXEC_IF_NOT_20_ELSE(expr, expr2) expr
#endif

#define MATRIX_TYPENAME EXEC_IF_20_ELSE(mat::Matrix, typename)
#define RUNTIME_MATRIX_TYPENAME EXEC_IF_20_ELSE(mat::RuntimeMatrix, typename)
#define CONSTEXPR_MATRIX_TYPENAME EXEC_IF_20_ELSE(mat::ConstexprMatrix, typename)

#ifdef HAS_CONCEPTS

namespace mat
{
#include <concepts>

    template <typename T>
    concept Matrix = requires(T a, const T b)
    {
        typename T::value_type;

        {a.begin()} -> std::same_as<typename T::value_type*>;
        {a.end()} -> std::same_as<typename T::value_type*>;
        {b.begin()} -> std::same_as<const typename T::value_type*>;
        {b.end()} -> std::same_as<const typename T::value_type*>;

        {a.get_area()} -> std::same_as<size_t>;
        {a.get_width()} -> std::same_as<size_t>;
        {a.get_height()} -> std::same_as<size_t>;

        {a.at(0, 0)} -> std::convertible_to<typename T::value_type &>;
        {a.at(0, 0)} -> std::convertible_to<copy_fast_t<typename T::value_type>>;
        {a.fast_at(0)} -> std::convertible_to<typename T::value_type &>;
        {a.fast_at(0)} -> std::convertible_to<copy_fast_t<typename T::value_type>>;
    };

    template <typename M>
    concept ConstexprMatrix = Matrix<M> && requires(M a)
    {
        // so that regardless of type's other template arguments, a function can easily declare variables of said type in different dimensions
        typename M::base<0, 0>;

        {M::area} -> std::convertible_to<size_t>;
        {M::width} -> std::convertible_to<size_t>;
        {M::height} -> std::convertible_to<size_t>;
    };

    template <typename M>
    concept RuntimeMatrix = Matrix<M> && requires(M a)
    {
        {a.capacity()} -> std::same_as<size_t>;
        {a.resize(0, 0)} -> std::same_as<void>;
        {a.reserve(0)} -> std::same_as<void>;
    };
}

#define CONSTEXPR_MATRIX(T) mat::ConstexprMatrix<T>
#define RUNTIME_MATRIX(T) mat::RuntimeMatrix<T>

#else

#define HAS_(member, member_type)                                         \
    template <typename T, typename = member_type>                         \
    struct has_##member : std::false_type                                 \
    {                                                                     \
    };                                                                    \
    template <typename T>                                                 \
    struct has_##member<T, decltype((void)T::member, 0)> : std::true_type \
    {                                                                     \
    };
    
HAS_(area, int);
HAS_(width, int);
HAS_(height, int);

#define HAS_FUNC_(func_name)                                                                                                                  \
    template <typename, typename T>                                                                                                           \
    struct has_##func_name                                                                                                                    \
    {                                                                                                                                         \
        static_assert(std::integral_constant<T, false>::value, "Second template parameter needs to be of function type.");                    \
    };                                                                                                                                        \
    template <typename C, typename Ret, typename... Args>                                                                                     \
    struct has_##func_name<C, Ret(Args...)>                                                                                                   \
    {                                                                                                                                         \
    private:                                                                                                                                  \
        template <typename T>                                                                                                                 \
        static constexpr auto check(T *) -> typename std::is_same<decltype(std::declval<T>().func_name(std::declval<Args>()...)), Ret>::type; \
        template <typename>                                                                                                                   \
        static constexpr std::false_type check(...);                                                                                          \
        typedef decltype(check<C>(0)) type;                                                                                                   \
                                                                                                                                              \
    public:                                                                                                                                   \
        static constexpr bool value = type::value;                                                                                            \
    };

HAS_FUNC_(capacity);
HAS_FUNC_(resize);
HAS_FUNC_(reserve);

#define HAS_STATIC_FUNC(static_method_name)                                                                                             \
    template <typename, typename T>                                                                                                     \
    struct has_##static_method_name                                                                                                     \
    {                                                                                                                                   \
        static_assert(std::integral_constant<T, false>::value, "Second template parameter needs to be of function type.");              \
    };                                                                                                                                  \
    template <typename C, typename Ret, typename... Args>                                                                               \
    struct has_##static_method_name<C, Ret(Args...)>                                                                                    \
    {                                                                                                                                   \
        template <typename T>                                                                                                           \
        static constexpr auto check(T *) -> typename std::is_same<decltype(T::static_method_name(std::declval<Args>()...)), Ret>::type; \
        template <typename>                                                                                                             \
        static constexpr std::false_type check(...);                                                                                    \
        static constexpr bool value = decltype(check<C>(nullptr))::value;                                                               \
    };

template <typename T>
constexpr bool is_constexpr_matrix_v = has_area<T>::value && has_width<T>::value && has_height<T>::value;

template <typename T>
constexpr bool is_runtime_matrix_v = has_capacity<T, size_t()>::value && has_resize<T, void(size_t, size_t)>::value && has_reserve<T, void(size_t, size_t)>::value;

#define CONSTEXPR_MATRIX(T) is_constexpr_matrix_v<T>
#define RUNTIME_MATRIX(T) is_runtime_matrix_v<T>

#endif
