#define CONTAINING_RECORD(address, type, field)         \
    ((type *)((char *)(address) -                               \
    (ptrdiff_t)(&((type *)0x10)->field) + (ptrdiff_t)0x10))

#define CONTAININT_RECORD(address, type, field) \
    ((type*)((PCHAR)(address) - (PCHAR)(&((type*)0)->field)))


struct KSimpNode 
{
    KSimpNode();

    KNode   SortedListNode[thtTotal];   // 不同类型的仇恨自己维护一个从大到小排序的List
};

