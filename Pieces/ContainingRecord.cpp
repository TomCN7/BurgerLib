#define CONTAINING_RECORD(address, type, field)         \
    ((type *)((char *)(address) -                               \
    (ptrdiff_t)(&((type *)0x10)->field) + (ptrdiff_t)0x10))

#define CONTAININT_RECORD(address, type, field) \
    ((type*)((PCHAR)(address) - (PCHAR)(&((type*)0)->field)))


struct KSimpNode 
{
    KSimpNode();

    KNode   SortedListNode[thtTotal];   // ��ͬ���͵ĳ���Լ�ά��һ���Ӵ�С�����List
};

