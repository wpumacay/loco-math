#include <iostream>
#include <loco/math/all.hpp>

using Vector3f = loco::math::Vector3<float>;

LM_NEVER_INLINE auto check_operator_add() -> float {
    Vector3f vec_a;
    Vector3f vec_b;
    std::cin >> vec_a;
    std::cin >> vec_b;
#ifndef LOCOMATH_COMPILER_MSVC
    __asm__(
        "check_operator_add_start:;"
        "nop;");
#endif
    // Use operator+ (check the dissassembly)
    auto vec_sum = vec_a + vec_b;
#ifndef LOCOMATH_COMPILER_MSVC
    __asm__(
        "check_operator_add_end:;"
        "nop;");
#endif
    return vec_sum[0] + vec_sum[1] + vec_sum[2];
}

LM_NEVER_INLINE auto check_operator_sub() -> float {
    Vector3f vec_a;
    Vector3f vec_b;
    std::cin >> vec_a;
    std::cin >> vec_b;
#ifndef LOCOMATH_COMPILER_MSVC
    __asm__(
        "check_operator_sub_start:;"
        "nop;");
#endif
    // Use operator- (check the dissassembly)
    auto vec_sub = vec_a - vec_b;
#ifndef LOCOMATH_COMPILER_MSVC
    __asm__(
        "check_operator_sub_end:;"
        "nop;");
#endif
    return vec_sub[0] + vec_sub[1] + vec_sub[2];
}

LM_NEVER_INLINE auto check_operator_hadamard() -> float {
    Vector3f vec_a;
    Vector3f vec_b;
    std::cin >> vec_a;
    std::cin >> vec_b;
#ifndef LOCOMATH_COMPILER_MSVC
    __asm__(
        "check_operator_hadamard_start:;"
        "nop;");
#endif
    // Use operator- (check the dissassembly)
    auto vec_hm = vec_a * vec_b;
#ifndef LOCOMATH_COMPILER_MSVC
    __asm__(
        "check_operator_hadamard_end:;"
        "nop;");
#endif
    return vec_hm[0] + vec_hm[1] + vec_hm[2];
}

auto main() -> int {
    check_operator_add();
    check_operator_sub();
    check_operator_hadamard();
    return 0;
}
