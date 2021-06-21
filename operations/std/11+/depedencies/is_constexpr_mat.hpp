#pragma once

template <auto E>
struct has_constexpr_element : std::integral_constant<decltype(E), E> {};

template <typename M>
using is_constexpr_matrix = has_constexpr_element<M::area>;
template <typename T>
using is_constexpr_matrix_v = is_constexpr_matrix<T>::value;