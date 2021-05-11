#pragma once
#include <iostream>
#include "cmat.hpp"

template <typename T>
concept Printable = requires(T a) { {std::cout<<a}->std::same_as<std::ostream&>; };

namespace mat
{
    //Print
    template <Matrix M>
    requires Printable<typename M::type>
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

    //Fill
    template <Matrix M, typename T>
    constexpr void Fill(M& m, T&& v)
    {
        for(auto& e : m)
        {
            e = v;
        }
    }

    template <Matrix M, typename F>
    constexpr void ForEach(M& mat, F&& func)
    {
        for(typename M::type& e : mat)
        {
            func(e);
        }
    }
};
