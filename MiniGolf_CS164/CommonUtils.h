#include <vector>

//typedef unsigned char Status;

#define STATUS_OK 0x1

template <typename T>
void Delete(T **thing)
{
  if (*thing)
  {
    delete (*thing);
    (*thing) = 0;
  }
}

template <typename T>
void DeleteAligned(T **alignedThing)
{
  if (*alignedThing)
  {
    _aligned_free(*alignedThing);
    (*alignedThing) = 0;
  }
}

template <typename T>
T *NewAligned(size_t alignment)
{
  return (T*) _aligned_malloc(sizeof(T), alignment);
}

template <typename T>
void DeleteVectorPtrs(std::vector<T*> **vec)
{
  if (*vec)
  {
    for (std::vector<T*>::iterator it = (*vec)->begin(); it != (*vec)->end(); ++it)
    {
      Delete(&(*it));
      //delete (*it);
      //(*it) = 0;
    }
    delete (*vec);
    (*vec) = 0;
  }
}
