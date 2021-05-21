#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <algorithm>
#include "hmat.hpp"
#include "smat.hpp"
#include "operations/misc_ops.hpp"
#include "operations/arithmetic_ops.hpp"

#include <ctime>
#include <ratio>
#include <chrono>
#define time_func(f)                                                                        \
    {                                                                                       \
        using namespace std::chrono;                                                        \
        uint32_t res = 0;                                                                   \
        for (int i = 0; i < 100000; ++i)                                                    \
        {                                                                                   \
            auto t1 = high_resolution_clock::now().time_since_epoch();                      \
            f;                                                                              \
            auto t2 = high_resolution_clock::now().time_since_epoch();                      \
            res += std::chrono::duration_cast<std::chrono::nanoseconds>((t2 - t1)).count(); \
        }                                                                                   \
        std::cout << res / 100000 << '\n';                                                  \
    }

#define Op(v, name)        \
    {                      \
        std::cout << name; \
        time_func(v);      \
    }

int main()
{
    using namespace mat;

    sMat<int, 100, 100> s;
    for (int &i : s)
    {
        i = 4;
    }

    hMat<int> h(100, 100);
    for (int &i : h)
    {
        i = 3;
    }

    Op(h + h, "heap + heap\n");
    Op(h + s, "heap + stack\n");
    Op(s + s, "stack + stack\n");
    Op(s + h, "stack + heap\n");
    Op(s + h, "stack + heap\n");
    std::cout << '\n';

    Op(h - h, "heap - heap\n");
    Op(h - s, "heap - stack\n");
    Op(s - s, "stack - stack\n");
    Op(s - h, "stack - heap\n");
    Op(s - h, "stack - heap\n");
    std::cout << '\n';

    Op(h * h, "heap * heap\n");
    Op(h * s, "heap * stack\n");
    Op(s * s, "stack * stack\n");
    Op(s * h, "stack * heap\n");
    Op(s * h, "stack * heap\n");
    std::cout << '\n';

    Op(h / h, "heap / heap\n");
    Op(h / s, "heap / stack\n");
    Op(s / s, "stack / stack\n");
    Op(s / h, "stack / heap\n");
    Op(s / h, "stack / heap\n");
    std::cout << '\n';
}
