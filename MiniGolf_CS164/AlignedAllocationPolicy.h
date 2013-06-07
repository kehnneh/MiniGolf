#pragma once
/// Policy for allocating byte-aligned classes

/**
 * Defines a child class as having aligned memory on an Alignment-byte boundary.
 */
template<size_t Alignment>
class AlignedAllocationPolicy
{
public:
  /**
   * Uses _aligned_malloc() to allocate memory instead of malloc()
   */
  static void* operator new(size_t size)
  {
    return _aligned_malloc(size, Alignment);
  }

  /**
   * Uses _aligned_free() to free memory instead of free()
   */
  static void operator delete(void* memory)
  {
    _aligned_free(memory);
  }
};

