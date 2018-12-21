# cpuid

cpuid��һ��intelָ����ڻ�ȡcpu����Ϣ��������x86��x64ƽ̨����ָ��ʹ�÷�����

* ʹ��EAX����һ��id
* ��ѯ����Ϣ����EAX��EBX��ECX��EDX���ĸ��Ĵ������档

## 1. cpuidָ��
cpuid��һ�����ָ�ʹ��EAX��ECX���Σ�EAX����0��ʾ������function������0x80000000��ʾ��չ���ܣ����������EAX��EBX��ECX��EDX�У�
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

## 2. __cpuid��__cpuidex����
����ʹ�û��ȥ��ѯ��Ϣ��Ҳ����ʹ�ñ������ṩ�ĺ�������MSVC�оͿ���ʹ�������������������������ĺ���ԭ�ͣ�

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

��������������Ӧcpuidָ�__cpuidex��__cpuid����ǿ�档
__cpuid����һ�����飬�ֱ𱣴�������EAX��EBX��ECX��EDX��ֵ��function_id��Ϊ��Σ�����EAX����ѯ��������function_idָ����
__cpuidex����ʱ��ECX����0x80000000��subfunction_id������ʾ��ѯ��չ���ܡ����__cpuid����ʱ��ECX�Ĵ�����Ҫ���㡣

## 3. cpuid��ѯ֧�ֹ��ܸ����Ͳ�������
��function_idΪ0ʱ��EAX�з�����CPU��֧�ֵ�function_id������EBX��ECX��EDX�б�����CPU���̵����ƣ����12���ַ���4*3����
```cpp
    int regs[4];

    __cpuid(regs, 0);

    int funid_size = regs[0]; // function_id����

    char vendor[13] = {0};
    *(int*)vendor = regs[1];
    *(int*)(vendor+4) = regs[3];
    *(int*)(vendor+8) = regs[2]; // ע��˳��

    cout << vendor << endl; // GenuineIntel
```

__cpuid(regs, 0),function_idΪ0�� EAX���ز���֧�ֵ�function_id�����������������������й��ܣ�
```
// ʹ�ñ�������
    __cpuid(regs, 0);
    funid_size = regs[0];
    cout << "function_id max:" << funid_size << endl;  // ��ǰ����22
    for (int i = 0; i <= funid_size; i++) {
        __cpuidex(regs, i, 0);
    }
```

�ҵ���⣬��������д���ǵ�Ч�ģ�
```
__cpuidex(regs, i, 0);
__cpuid(regs, i);
```

## 4. CPU֧�ֵ�ָ���ѯ
* __cpuid(regs, 1)��ECX��EDX�б����˶�ָ���֧�����������MMX��EDX bit 23����SSE��EDX bit 25����SSE2��EDX bit 26����SSE3��ECX bit 0����AVX��ECX bit 28���ȡ�
* __cpuid(regs, 7)��EBX��ECXҲ������һЩָ�֧�������


## 5. ��չ���ܲ�ѯ
* һЩCPU֧��һЩ��չfunction_id��id�Ǵ�0x80000000��ʼ�ģ��ͻ�����һ������0x80000000����EAX�л�ȡ֧�ֵ�id������
```cpp
    __cpuid(regs, 0x80000000);
    int extids = regs[0];
    cout << hex << extids << endl;  // 0x80000008
```

ͬ������ʹ��cpuidex������Ҳ���Ե������á�

* 0x80000001���ص�ECX��EDX������һЩ���ܱ�־��

* 0x80000002~0x80000004���ص�EBX��ECX��EDX������CPU�ͺŵ���Ϣ����Ҫ����3�Σ�
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

