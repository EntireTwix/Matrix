#pragma once
#include <ostream>
#include "dependencies/cmat.hpp"

#ifdef HAS_CONCEPTS
template <typename T>
concept Printable = requires(const T a, std::ostream os) {{ os << a } ->std::same_as<std::ostream &>;};
#endif

namespace mat
{
    template <MATRIX_TYPENAME M>
#ifdef HAS_CONCEPTS
    requires Printable<typename M::value_type>
#endif
    std::ostream &Print(std::ostream &os, const M &mat)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "operation_mut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        for (size_t i = 0; i < mat.get_height(); ++i)
        {
            for (size_t j = 0; j < mat.get_width(); ++j)
            {
                os << mat.at(j, i) << ' ';
            }
            os << '\n';
        }
        return os;
    }
};
