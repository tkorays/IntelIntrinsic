# MMX, Multi Media eXtension，多媒体扩展指令集
MMX扩展指令集中新增了57条命令和一种64字节的数据类型，新增了8个64位寄存器MM0~MM7.

它使用的是浮点寄存器，不能和浮点运算同时进行，执行浮点运算前必须执行EMMS。

【注意】
* 指令中D表示双字（double word，一个字2byte，总共4字节），Q表示（Quad word，四个字节）。
* 第一个P表示pack，即打包数据。


## 1. 数据传送指令
双字传送MOVD、四字传送MOVQ。


## 2. 清空MMX寄存器
EMMS（Empty MMX State）。

## 3. 位移运算
* PSLLW（Shift Left Logical Word）
* PSLLD（Shift Left Logical Double Word）
* PSRLW（Shift Right Logical Word）
* PSRLD（Shift Right Logical Double Word）
* PSRAW（Shift Right Arithmetic Word）
* PSRAD（Shift Right Arithmetic Double Word）
* PSLLQ（Shift Left Logical Quad Word）
* PSRLQ（Shift Right Logical Quad Word）

## 4. 逻辑运算符
PAND、PANDN（And NOT）、POR、PXOR

## 5. 算术运算符
【注意】
1. 不带S的表示环绕模式，溢出后清零。
2. 带S表示在有符号饱和模式，溢出后变成最大值或最小值
3. 带U表示在无符号饱和模式

加:
* PADDB, add byte
* PADDW, add word
* PADDD, add double word

* PADDSB, add signed byte
* PADDSW, add signed word

* PADDUSB, add unsigned byte
* PADDUSW, add unsigned word

对应的函数：
_mm_add_pi8 _mm_add_pi16 _mm_add_pi32 _mm_add_pi64等

减：
* PSUBB, sub byte
* PSUBW, sub word
* PSUBD, sub double word

* PSUBSB, sub signed byte
* PSUBSW, sub unsigned word

* PSUBUSB, sub unsigned byte
* PSUBUSW, sub unsigned word

乘：
* PMULL, Multiply Low
* PMULLH, Multiply High
* PMADD, Multiply and add,可以实现向量点乘，好牛逼
* PMADDWD

对应函数：_mm_mullo_pi16 _mm_mulhi_pi16 _mm_madd_pi16


## 6. 比较指令
* PCMPEQB, compare for equal byte
* PCMPEQW, compare for equal word
* PCMPEQD, compare for equal double word

* PCMPGTPB, compare for greater than byte
* PCMPGTPW, compare for greater than word
* PCMPGTPD, compare for greater than double word

## 7. pack
* PACKSSWB, pack signed -> signed, word -> byte
* PACKSSDW, pack signed -> signed,  double word -> word
* PACKUSWB, pack unsigned -> signed, word -> byte

## 8. unpack
* PUNPACKHBW, unpack high byte -> word
* PUNPACKHWD, unpack high word -> double word
* PUNPACKHDQ, unpack high double word -> quad word

* PUNPACKLBW,
* PUNPACKLWD,
* PUNPACKLDQ,