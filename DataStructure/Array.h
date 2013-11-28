#ifdef NDEBUG
// From http://cnicholson.net/2009/02/stupid-c-tricks-adventures-in-assert/
#	define rcAssert(x) do { (void)sizeof(x); } while((void)(__LINE__==-1),false)  
#else
#	include <assert.h> 
#	define rcAssert assert
#endif


/// A simple dynamic array of integers.
class rcIntArray
{
    int* m_data;
    int m_size, m_cap;
    inline rcIntArray(const rcIntArray&);
    inline rcIntArray& operator=(const rcIntArray&);
public:

    /// Constructs an instance with an initial array size of zero.
    inline rcIntArray() : m_data(0), m_size(0), m_cap(0) {}

    /// Constructs an instance initialized to the specified size.
    ///  @param[in]		n	The initial size of the integer array.
    inline rcIntArray(int n) : m_data(0), m_size(0), m_cap(0) { resize(n); }
    inline ~rcIntArray() { rcFree(m_data); }

    /// Specifies the new size of the integer array.
    ///  @param[in]		n	The new size of the integer array.
    void resize(int n);

    /// Push the specified integer onto the end of the array and increases the size by one.
    ///  @param[in]		item	The new value.
    inline void push(int item) { resize(m_size+1); m_data[m_size-1] = item; }

    /// Returns the value at the end of the array and reduces the size by one.
    ///  @return The value at the end of the array.
    inline int pop() { if (m_size > 0) m_size--; return m_data[m_size]; }

    /// The value at the specified array index.
    /// @warning Does not provide overflow protection.
    ///  @param[in]		i	The index of the value.
    inline const int& operator[](int i) const { return m_data[i]; }

    /// The value at the specified array index.
    /// @warning Does not provide overflow protection.
    ///  @param[in]		i	The index of the value.
    inline int& operator[](int i) { return m_data[i]; }

    /// The current size of the integer array.
    inline int size() const { return m_size; }
};

/// A simple helper class used to delete an array when it goes out of scope.
/// @note This class is rarely if ever used by the end user.
template<class T> class rcScopedDelete
{
    T* ptr;
    inline T* operator=(T* p);
public:

    /// Constructs an instance with a null pointer.
    inline rcScopedDelete() : ptr(0) {}

    /// Constructs an instance with the specified pointer.
    ///  @param[in]		p	An pointer to an allocated array.
    inline rcScopedDelete(T* p) : ptr(p) {}
    inline ~rcScopedDelete() { rcFree(ptr); }

    /// The root array pointer.
    ///  @return The root array pointer.
    inline operator T*() { return ptr; }
};
