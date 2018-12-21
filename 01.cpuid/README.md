# cpuid

cpuid是一个intel指令，用于获取cpu的信息，适用于x86和x64平台。该指令使用方法：

* 使用EAX传入一个id
* 查询的信息放在EAX、EBX、ECX、EDX这四个寄存器里面。

## 1. cpuid指令
cpuid是一个汇编指令，使用EAX和ECX传参，EAX传入0表示基本的function，传入0x80000000表示扩展功能，结果返回在EAX、EBX、ECX、EDX中：
```cpp
int regs[4];

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
```

## 2. __cpuid和__cpuidex函数
可以使用汇编去查询信息，也可以使用编译器提供的函数。在MSVC中就可以使用这两个函数。这两个函数的函数原型：

```cpp
void __cpuid(
   int cpuInfo[4],
   int function_id
);

void __cpuidex(
   int cpuInfo[4],
   int function_id,
   int subfunction_id
);
```

这两个函数都对应cpuid指令，__cpuidex是__cpuid的增强版。
__cpuid传入一个数组，分别保存输出结果EAX、EBX、ECX、EDX的值，function_id作为入参，赋给EAX。查询的内容由function_id指定。
__cpuidex调用时，ECX传入0x80000000（subfunction_id），表示查询扩展功能。因此__cpuid调用时，ECX寄存器需要清零。

## 3. cpuid查询支持功能个数和产商名称
当function_id为0时，EAX中返回了CPU所支持的function_id个数，EBX、ECX、EDX中保存了CPU产商的名称，最多12个字符（4*3）。
```cpp
    int regs[4];

    __cpuid(regs, 0);

    int funid_size = regs[0]; // function_id个数

    char vendor[13] = {0};
    *(int*)vendor = regs[1];
    *(int*)(vendor+4) = regs[3];
    *(int*)(vendor+8) = regs[2]; // 注意顺序

    cout << vendor << endl; // GenuineIntel
```

__cpuid(regs, 0),function_id为0， EAX返回参数支持的function_id个数，可以用它来遍历所有功能：
```
// 使用遍历方法
    __cpuid(regs, 0);
    funid_size = regs[0];
    cout << "function_id max:" << funid_size << endl;  // 当前电脑22
    for (int i = 0; i <= funid_size; i++) {
        __cpuidex(regs, i, 0);
    }
```

我的理解，下面两种写法是等效的：
```
__cpuidex(regs, i, 0);
__cpuid(regs, i);
```

## 4. CPU支持的指令集查询
* __cpuid(regs, 1)的ECX、EDX中保存了对指令集的支持情况，包括MMX（EDX bit 23）、SSE（EDX bit 25）、SSE2（EDX bit 26）、SSE3（ECX bit 0）、AVX（ECX bit 28）等。
* __cpuid(regs, 7)的EBX和ECX也保存了一些指令集支持情况。


## 5. 扩展功能查询
* 一些CPU支持一些扩展function_id，id是从0x80000000开始的，和基本的一样，传0x80000000，在EAX中获取支持的id个数：
```cpp
    __cpuid(regs, 0x80000000);
    int extids = regs[0];
    cout << hex << extids << endl;  // 0x80000008
```

同理，可以使用cpuidex遍历，也可以单独调用。

* 0x80000001返回的ECX、EDX保存了一些功能标志。

* 0x80000002~0x80000004返回的EBX、ECX、EDX保存了CPU型号的信息，需要调用3次！
```cpp
int brand[16] = { 0 };
int* pBrand = brand;
for (unsigned int i = 0x80000002; i <= 0x80000004; i++) {
    __cpuid(regs, i);
    *(pBrand++) = regs[0];
    *(pBrand++) = regs[1];
    *(pBrand++) = regs[2];
    *(pBrand++) = regs[3];
}
cout << (char*)brand << endl; // Intel(R) Core(TM) i7-6500U CPU @ 2.50GHz
```

