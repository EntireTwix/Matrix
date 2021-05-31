#pragma once

namespace mat
{
    template <typename M>
    void IsVector(const M &mat)
    {
        assert(mat.Width() == 1 || mat.Height() == 1);
    }
};