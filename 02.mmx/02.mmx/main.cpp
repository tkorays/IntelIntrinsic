#include <intrin.h>
#include <iostream>
using namespace std;

int main() {

    // 将eax的值赋给mm0的低32位，高32位清零
    __asm {
        mov eax, 1234
        movd mm0, eax
    }

    char data1[8] = { 1,2,3,4,5,6,7,129 };
    char data2[8] = { 8,7,6,5,254,3,2,129 };
    char result[8] = { 0 };
    __asm {
        movq mm1, [data1]
        movq mm2, [data2]
        paddb mm1, mm2
        movq [result], mm1
    }
    for (int i = 0; i < 8; i++) {
        cout << (int)result[i] << endl;
    }
    
    cout << "-----" << endl;

    // 饱和运算，最大255
    __asm {
        movq mm1, [data1]
        movq mm2, [data2]
        paddusb mm1, mm2
        movq [result], mm1
    }

    for (int i = 0; i < 8; i++) {
        cout << (int)result[i] << endl;
    }

    cout << "-----" << endl;

    // 饱和运算，
    __asm {
        movq mm1, [data1]
        movq mm2, [data2]
        paddsb mm1, mm2
        movq[result], mm1
    }

    for (int i = 0; i < 8; i++) {
        cout << (int)result[i] << endl;
    }

    // 向量乘积
    short arr1[4] = { 1, 2, 3, 4};
    short arr2[4] = { 5, 6, 7, 8 };
    short ret[4];
    __asm {
        movq mm1, [arr1]
        movq mm2, [arr2]
        pmaddwd mm1, mm2
        movq[ret], mm1
    }
    cout << ">>>" << endl;
    for (int i = 0; i < 4; i++) {
        cout << ret[i] << endl;
    }
    return 0;
}