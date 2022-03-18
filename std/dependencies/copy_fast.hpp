#pragma once
#include <type_traits>


//CopyFast metaprogramming type
template <typename T>
struct copy_fast : std::conditional<std::is_trivially_copyable_v<T>, T, const T &>{};
template <typename T>
using copy_fast_t = typename copy_fast<T>::type;
