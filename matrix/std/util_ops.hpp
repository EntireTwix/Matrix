#pragma once
#include "dependencies/copy_fast.hpp"
#include "dependencies/cmat.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    constexpr void CopySameArea(const M &src, M2 &dest)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "CopySameArea: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
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
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Copy: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
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

    template <RUNTIME_MATRIX_TYPENAME M>
    constexpr void FlattenMut(M &mat)
    {
        EXEC_IF_NOT_20(static_assert(RUNTIME_MATRIX(M), "FlattenMut: M must be RUNTIME_MATRIX");)
        mat.Flatten();
    }

    template <RUNTIME_MATRIX_TYPENAME M>
    constexpr void ResizeMut(M &mat, size_t w, size_t h)
    {
        EXEC_IF_NOT_20(static_assert(RUNTIME_MATRIX(M), "ResizeMut: M must be RUNTIME_MATRIX");)
        mat.Resize(w, h);
    }
};
