# cpuid

cpuid是一个intel指令，用于获取cpu的信息，适用于x86和x64平台。该指令使用方法：

* 使用EAX传入一个id
* 查询的信息放在EAX、EBX、ECX、EDX这四个寄存器里面。

## 1. __cpuid和__cpuidex函数
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

* __cpuid传入一个数组，分别保存输出结果EAX、EBX、ECX、EDX的值，function_id作为入参，赋给EAX。查询的内容由function_id指定。

__cpuid和__cpuidex对应的汇编：
```
    int regs[4];

    __cpuid(regs, 1);
00C516B8  lea         esi,[regs]  
00C516BB  mov         eax,1  
00C516C0  xor         ecx,ecx  
00C516C2  cpuid  
00C516C4  mov         dword ptr [esi],eax  
00C516C6  mov         dword ptr [esi+4],ebx  
00C516C9  mov         dword ptr [esi+8],ecx  
00C516CC  mov         dword ptr [esi+0Ch],edx 

    __cpuidex(regs, 1, 0);
009716CF  lea         esi,[regs]  
009716D2  mov         eax,1  
009716D7  xor         ecx,ecx  
009716D9  cpuid  
009716DB  mov         dword ptr [esi],eax  
009716DD  mov         dword ptr [esi+4],ebx  
009716E0  mov         dword ptr [esi+8],ecx  
009716E3  mov         dword ptr [esi+0Ch],edx 
```

* 当function_id为0时，EAX中返回了CPU所支持的function_id个数，EBX、ECX、EDX中保存了CPU产商的名称，最多12个字符（4*3）。
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

* __cpuid(regs, 0),function_id为0， EAX返回参数支持的function_id个数，可以用它来遍历所有功能：
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

* __cpuid(regs, 1)的ECX、EDX中保存了对指令集的支持情况，包括MMX、SSE、AVX等。
* __cpuid(regs, 7)的EBX和ECX也保存了一些指令集支持情况。


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

