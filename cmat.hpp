#pragma once
#include <stddef.h>
#include <concepts>

//CopyFast metaprogramming type
template <typename T>
struct copy_fast : std::conditional<std::is_trivially_copyable_v<T>, T, const T &>{};
template <typename T>
using copy_fast_t = typename copy_fast<T>::type;

template <typename T, typename type = typename T::type>
concept Matrix = requires(T a, const T b) {
    typename T::type;
    
    { a.begin() } -> std::same_as<type*>;
    { a.end() } -> std::same_as<type*>;
    { b.begin() } -> std::same_as<const type*>;
    { b.end() } -> std::same_as<const type*>;
    { a.data() } -> std::same_as<type*>;

    { a.Area() } -> std::same_as<size_t>;
    { a.Width() } -> std::same_as<size_t>;
    { a.Height() } -> std::same_as<size_t>;

    { a.At(0,0) } -> std::convertible_to<type&>;
    { a.At(0,0) } -> std::convertible_to<type>;
    { a.FastAt(0) } -> std::convertible_to<type&>;
    { a.FastAt(0) } -> std::convertible_to<type>;
    
    { a.SizeCopy() } -> std::same_as<T>;
};