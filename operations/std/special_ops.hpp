#pragma once
#include <iostream>

#ifdef __cpp_concepts 
#include "depedencies/cmat.hpp"

template <typename T>
concept Printable = requires(T a)
{
    {std::cout << a} -> std::same_as<std::ostream &>;
};
#endif

namespace mat
{
    template <MATRIX_TYPENAME M>
    #ifdef __cpp_concepts 
    requires Printable<typename M::type>
    #endif
    std::ostream &operator<<(std::ostream &os, const M &mat)
    {
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