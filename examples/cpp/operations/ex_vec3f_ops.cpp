#include <iostream>
#include <tinymath/tinymath.hpp>

using Vector3f = tiny::math::Vector3<float>;

TM_NEVER_INLINE auto check_operator_add() -> float {
    Vector3f vec_a;
    Vector3f vec_b;
    std::cin >> vec_a;
    std::cin >> vec_b;
    __asm__(
        "check_operator_add_start:;"
        "nop;");
    // Use operator+ (check the dissassembly)
    auto vec_sum = vec_a + vec_b;
    __asm__(
        "check_operator_add_end:;"
        "nop;");
    return vec_sum[0] + vec_sum[1] + vec_sum[2];
}

TM_NEVER_INLINE auto check_operator_sub() -> float {
    Vector3f vec_a;
    Vector3f vec_b;
    std::cin >> vec_a;
    std::cin >> vec_b;
    __asm__(
        "check_operator_sub_start:;"
        "nop;");
    // Use operator- (check the dissassembly)
    auto vec_sub = vec_a - vec_b;
    __asm__(
        "check_operator_sub_end:;"
        "nop;");
    return vec_sub[0] + vec_sub[1] + vec_sub[2];
}

TM_NEVER_INLINE auto check_operator_hadamard() -> float {
    Vector3f vec_a;
    Vector3f vec_b;
    std::cin >> vec_a;
    std::cin >> vec_b;
    __asm__(
        "check_operator_hadamard_start:;"
        "nop;");
    // Use operator- (check the dissassembly)
    auto vec_hm = vec_a * vec_b;
    __asm__(
        "check_operator_hadamard_end:;"
        "nop;");
    return vec_hm[0] + vec_hm[1] + vec_hm[2];
}

auto main() -> int {
    auto foo_add = check_operator_add();
    auto foo_sub = check_operator_sub();
    auto foo_hmd = check_operator_hadamard();
    return 0;
}