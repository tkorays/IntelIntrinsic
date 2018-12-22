# MMX, Multi Media eXtension����ý����չָ�
MMX��չָ���������57�������һ��64�ֽڵ��������ͣ�������8��64λ�Ĵ���MM0~MM7.

��ʹ�õ��Ǹ���Ĵ��������ܺ͸�������ͬʱ���У�ִ�и�������ǰ����ִ��EMMS��

��ע�⡿
* ָ����D��ʾ˫�֣�double word��һ����2byte���ܹ�4�ֽڣ���Q��ʾ��Quad word���ĸ��ֽڣ���
* ��һ��P��ʾpack����������ݡ�


## 1. ���ݴ���ָ��
˫�ִ���MOVD�����ִ���MOVQ��


## 2. ���MMX�Ĵ���
EMMS��Empty MMX State����

## 3. λ������
* PSLLW��Shift Left Logical Word��
* PSLLD��Shift Left Logical Double Word��
* PSRLW��Shift Right Logical Word��
* PSRLD��Shift Right Logical Double Word��
* PSRAW��Shift Right Arithmetic Word��
* PSRAD��Shift Right Arithmetic Double Word��
* PSLLQ��Shift Left Logical Quad Word��
* PSRLQ��Shift Right Logical Quad Word��

## 4. �߼������
PAND��PANDN��And NOT����POR��PXOR

## 5. ���������
��ע�⡿
1. ����S�ı�ʾ����ģʽ����������㡣
2. ��S��ʾ���з��ű���ģʽ������������ֵ����Сֵ
3. ��U��ʾ���޷��ű���ģʽ

��:
* PADDB, add byte
* PADDW, add word
* PADDD, add double word

* PADDSB, add signed byte
* PADDSW, add signed word

* PADDUSB, add unsigned byte
* PADDUSW, add unsigned word

��Ӧ�ĺ�����
_mm_add_pi8 _mm_add_pi16 _mm_add_pi32 _mm_add_pi64��

����
* PSUBB, sub byte
* PSUBW, sub word
* PSUBD, sub double word

* PSUBSB, sub signed byte
* PSUBSW, sub unsigned word

* PSUBUSB, sub unsigned byte
* PSUBUSW, sub unsigned word

�ˣ�
* PMULL, Multiply Low
* PMULLH, Multiply High
* PMADD, Multiply and add,����ʵ��������ˣ���ţ��
* PMADDWD

��Ӧ������_mm_mullo_pi16 _mm_mulhi_pi16 _mm_madd_pi16


## 6. �Ƚ�ָ��
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