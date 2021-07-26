#include <iostream>
#include <hmat.hpp>
#include <smat.hpp>
#include <matrix/std/util_ops.hpp>
#include <matrix/std/arithmetic_ops.hpp>
#include <matrix/std/special_ops.hpp>

#include <ctime>
#include <ratio>
#include <chrono>

#define time_func_a(f, a, x)                                                                  \
    {                                                                                         \
        using namespace std::chrono;                                                          \
        uint32_t timer = 0;                                                                   \
        for (int i = 0; i < x; ++i)                                                           \
        {                                                                                     \
            auto t1 = high_resolution_clock::now().time_since_epoch();                        \
            f;                                                                                \
            auto t2 = high_resolution_clock::now().time_since_epoch();                        \
            a;                                                                                \
            timer += std::chrono::duration_cast<std::chrono::nanoseconds>((t2 - t1)).count(); \
        }                                                                                     \
        std::cout << timer / x << '\n';                                                       \
    }

#define Op_a(v, name, x, a)   \
    {                         \
        std::cout << name;    \
        time_func_a(v, a, x); \
    }

int main()
{
    using namespace mat;
    hMat<int> a(10, 10);
    hMat<int> b(10, 10);
    Fill(a, 3);
    Fill(b, 8);

    Print(std::cout, a);
    Op_a(AddMatMut(a, b), "+= generic     ", 10000, Fill(a, 3); Fill(b, 8););
    Op_a(for (size_t i = 0; i < 100; ++i) a.FastAt(i) += b.FastAt(i), "+= handwritten ", 10000, Fill(a, 3); Fill(b, 8););

    return 0;
}
