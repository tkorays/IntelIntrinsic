#include <intrin.h>
#include <iostream>
using namespace std;

int main() {

    char vendor[13] = { 0 };

    int regs[4];

#define CHOOSE_ASM
#ifdef CHOOSE_ASM
    __asm {
        lea esi, [regs]
        mov eax, 0
        xor ecx, ecx 
        cpuid 
        mov dword ptr[esi], eax
        mov dword ptr[esi+4], ebx
        mov dword ptr[esi+8], ecx
        mov dword ptr[esi+12], edx
    }
#else 
    __cpuid(regs, 0);
#endif

    int funid_size = regs[0]; // function_id����

    *(int*)vendor = regs[1];
    *(int*)(vendor+4) = regs[3];
    *(int*)(vendor+8) = regs[2]; // ע��˳��

    cout << vendor << endl; // GenuineIntel

    // ʹ�ñ�������
    __cpuid(regs, 0);
    funid_size = regs[0];
    cout << "function_id max:" << funid_size << endl;  // ��ǰ����22
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