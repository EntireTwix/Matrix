#pragma once
#include <stddef.h>
#include <concepts>

namespace mat
{
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
    
        { a.SizeCopy() } -> std::same_as<T>;
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
