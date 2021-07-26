#pragma once
#include <type_traits>
#include <stddef.h>

#ifdef __cpp_concepts
    #if __cplusplus >= __cpp_concepts
    #define HAS_CONCEPTS true
    #endif
#endif

#ifdef HAS_CONCEPTS 
#define EXEC_IF_20(expr) expr
#else
#define EXEC_IF_20(expr) 
#endif

#ifdef HAS_CONCEPTS 
#define EXEC_IF_20_ELSE(expr, expr2) expr
#else
#define EXEC_IF_20_ELSE(expr, expr2) expr2
#endif

#define MATRIX_TYPENAME EXEC_IF_20_ELSE(Matrix, typename)
#define RUNTIME_MATRIX_TYPENAME EXEC_IF_20_ELSE(RuntimeMatrix, typename)
#define CONSTEXPR_MATRIX_TYPENAME EXEC_IF_20_ELSE(ConstexprMatrix, typename)

#ifdef HAS_CONCEPTS
namespace mat
{
    #include <concepts>

    template <typename T>
    concept Matrix = requires(T a, const T b) {
        typename T::type;
    
        { a.begin() } -> std::same_as<typename T::type*>;
        { a.end() } -> std::same_as<typename T::type*>;
        { b.begin() } -> std::same_as<const typename T::type*>;
        { b.end() } -> std::same_as<const typename T::type*>;
        { a.data() } -> std::same_as<typename T::type*>;

        { a.Area() } -> std::same_as<size_t>;
        { a.Width() } -> std::same_as<size_t>;
        { a.Height() } -> std::same_as<size_t>;

        { a.At(0,0) } -> std::convertible_to<typename T::type&>;
        { a.At(0,0) } -> std::convertible_to<typename T::type>;
        { a.FastAt(0) } -> std::convertible_to<typename T::type&>;
        { a.FastAt(0) } -> std::convertible_to<typename T::type>;
    };

    template <typename M>
    concept ConstexprMatrix = Matrix<M> && requires(M a) {
        typename M::base<0, 0>;

        { M::area } -> std::convertible_to<size_t>;
        { M::width } -> std::convertible_to<size_t>;
        { M::height } -> std::convertible_to<size_t>;
    };

    template <typename M>
    concept RuntimeMatrix = Matrix<M> && requires(M a) {
        { a.Flatten() } -> std::same_as<void>;
    };
}

    #define CONSTEXPR_MATRIX(T) mat::ConstexprMatrix<T>
    #define RUNTIME_MATRIX(T) mat::RuntimeMatrix<T>
#else
    template <typename T, typename = void>
    struct has_area : std::false_type{};
    template <typename T>
    struct has_area<T, decltype((void)T::area, void())> : std::true_type {};
    template <typename T, typename = void>
    struct has_width : std::false_type{};
    template <typename T>
    struct has_width<T, decltype((void)T::width, void())> : std::true_type {};
    template <typename T, typename = void>
    struct has_height : std::false_type{};
    template <typename T>
    struct has_height<T, decltype((void)T::height, void())> : std::true_type {};

    template <typename T>
    struct is_constexpr_matrix : std::integral_constant<bool, has_area<T>::value && has_width<T>::value && has_height<T>::value> {};
    template <typename T>
    constexpr bool is_constexpr_matrix_v = is_constexpr_matrix<T>::value;

    #define CONSTEXPR_MATRIX(T) is_constexpr_matrix_v<T>
    #define RUNTIME_MATRIX(T) !CONSTEXPR_MATRIX(T)
#endif
