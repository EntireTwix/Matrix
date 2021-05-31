#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <algorithm>
#include "hmat.hpp"
#include "smat.hpp"
#include "operations/std/20/util_ops.hpp"
#include "operations/std/20/arithmetic_ops.hpp"
#include "operations/std/20/special_ops.hpp"

#include <ctime>
#include <ratio>
#include <chrono>
#define time_func(f)                                                                        \
    {                                                                                       \
        using namespace std::chrono;                                                        \
        uint32_t res = 0;                                                                   \
        for (int i = 0; i < 1000000; ++i)                                                   \
        {                                                                                   \
            auto t1 = high_resolution_clock::now().time_since_epoch();                      \
            f;                                                                              \
            auto t2 = high_resolution_clock::now().time_since_epoch();                      \
            res += std::chrono::duration_cast<std::chrono::nanoseconds>((t2 - t1)).count(); \
        }                                                                                   \
        std::cout << res / 1000000 << '\n';                                                 \
    }

#define Op(v, name)        \
    {                      \
        std::cout << name; \
        time_func(v);      \
    }

int main()
{
    using namespace mat;

    sMat<int, 100, 100> a;
    sMat<int, 100, 100> b;

    //gets CPU working because otherwise the last operation will be faster by a non-insignificant amount
    auto c = a + b;
    std::cout << c << '\n';

    {
        for (int &i : a)
        {
            i = 4;
        }

        for (int &i : b)
        {
            i = 3;
        }
        time_func(a += b);
    }

    {
        for (int &i : a)
        {
            i = 4;
        }

        for (int &i : b)
        {
            i = 3;
        }
        time_func(for (size_t i = 0; i < 10000; ++i) {
            a.FastAt(i) += b.FastAt(i);
        });
    }

    return 0;
}

// on a i7 6700k the result is always
// 16xx
// vs
// 16xx
// where xx is some digit that barely allows hand written or generic to win, so it can be concluded they are of equivelant speed
