#pragma once

template <typename T>
constexpr T pow2(copy_fast_t<T> val) { return val * val; }
