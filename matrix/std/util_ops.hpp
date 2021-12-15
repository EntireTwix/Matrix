#pragma once
#include <optional>
#include "dependencies/is_vector.hpp"
#include "dependencies/copy_fast.hpp"
#include "dependencies/cmat.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    constexpr void CopySameArea(const M &src, M2 &dest)
    {
        if constexpr (CONSTEXPR_MATRIX(M) && CONSTEXPR_MATRIX(M2))
        {
            static_assert(src.Area() == dest.Area(), "CopySameArea: must be same Area");
        }
        else
        {
            assert(src.Area() == dest.Area());
        }

        if constexpr (std::is_same_v<M, M2>)
        {
            dest = src; //calling operator=
        }
        else
        {
            for (size_t i = 0; i < src.Area(); ++i)
            {
                dest.FastAt(i) = src.FastAt(i);
            }
        }
    }

    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    constexpr void Copy(const M &src, M2 &dest)
    {
        if (src.Area() == dest.Area())
        {
            //CopySameArea definition, without static_assert
            if constexpr (std::is_same_v<M, M2>)
            {
                dest = src; //calling operator=
            }
            else
            {
                for (size_t i = 0; i < src.Area(); ++i)
                {
                    dest.FastAt(i) = src.FastAt(i);
                }
            }
        }
        else
        {
            for (size_t i = 0; i < dest.Height(); ++i)
            {
                for (size_t j = 0; j < dest.Width(); ++j)
                {
                    if (j < src.Width() && i < src.Height())
                    {
                        dest.At(j, i) = src.At(j, i);
                    }
                }
            }
        }
    }

    //STL generic macro gen?
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    constexpr bool Equal(const M &a, const M &b)
    {
        if constexpr (CONSTEXPR_MATRIX(M) && std::is_same_v<M, M2>)
        {
            if constexpr (a.Area() != b.Area())
            {
                return false;
            }
            else
            {
                return std::equal(a.begin(), a.end(), b.begin());
            }
        }
        else
        {
            if (a.Area() != b.Area())
            {
                return false;
            }
            else
            {
                return std::equal(a.begin(), a.end(), b.begin());
            }
        }
    }

    template <MATRIX_TYPENAME M>
    auto* SafeFastAt(size_t index, M& mat)
    {
        if(index < mat.Area())
        {
            return &mat.FastAt(index);
        }
        else
        {
            return (typename M::type*)nullptr;
        }
    }

    template <MATRIX_TYPENAME M>
    auto* SafeAt(size_t x, size_t y, M& mat) 
    { 
        if(x < mat.Width() && y < mat.Height())
        {
            return &mat.At(x, y);
        }
        else
        {
            return (typename M::type*)nullptr;
        }    
    }
};
