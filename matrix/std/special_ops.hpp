#pragma once
#include "dependencies/cmat.hpp"

#ifdef HAS_CONCEPTS
#include <iostream>
template <typename T>
concept Printable = requires(T a)
{
    { std::cout << a } ->std::same_as<std::ostream &>;
};
#else
#include <ostream>
#endif

namespace mat
{
    template <MATRIX_TYPENAME M>
#ifdef HAS_CONCEPTS
    requires Printable<typename M::type>
#endif
    std::ostream &Print(std::ostream &os, const M &mat)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "OperationMut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
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
};
