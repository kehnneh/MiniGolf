#include <vector>

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
void DeleteVectorPtrs(std::vector<T*> **vec)
{
  if (*vec)
  {
    for (std::vector<T*>::iterator it = (*vec)->begin(); it != (*vec)->end(); ++it)
    {
      delete (*it);
      (*it) = 0;
    }
    delete (*vec);
    (*vec) = 0;
  }
}
