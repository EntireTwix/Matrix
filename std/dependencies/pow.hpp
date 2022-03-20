#pragma once
#include "copy_fast.hpp"

template <typename T>
constexpr T pow2(copy_fast_t<T> val) { return val * val; }
