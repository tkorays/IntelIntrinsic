#include <intrin.h>
#include <iostream>
using namespace std;

int main() {
    int regs[4];

    __cpuid(regs, 0);

    int funid_size = regs[0]; // function_id个数

    char vendor[13] = {0};
    *(int*)vendor = regs[1];
    *(int*)(vendor+4) = regs[3];
    *(int*)(vendor+8) = regs[2]; // 注意顺序

    cout << vendor << endl; // GenuineIntel

    // 使用遍历方法
    __cpuid(regs, 0);
    funid_size = regs[0];
    cout << "function_id max:" << funid_size << endl;  // 当前电脑22
    for (int i = 0; i <= funid_size; i++) {
        __cpuidex(regs, i, 0);
    }

    __cpuidex(regs, 2, 0);
    cout << regs[0] << "," << regs[1] << "," << regs[2] << "," << regs[3] << endl;

    __cpuid(regs, 2);
    cout << regs[0] << "," << regs[1] << "," << regs[2] << "," << regs[3] << endl;

    __cpuid(regs, 0x80000000);
    int extids = regs[0];
    cout << hex << extids << endl;  // 0x80000008

    int brand[16] = { 0 };
    int* pBrand = brand;
    for (unsigned int i = 0x80000002; i <= 0x80000004; i++) {
        __cpuidex(regs, i, 0x80000000);
        // __cpuid(regs, i);
        *(pBrand++) = regs[0];
        *(pBrand++) = regs[1];
        *(pBrand++) = regs[2];
        *(pBrand++) = regs[3];
    }
    cout << (char*)brand << endl; // Intel(R) Core(TM) i7-6500U CPU @ 2.50GHz


    //__cpuid(regs, 1);

    //__cpuidex(regs, 1, 0);

    return 0;
}