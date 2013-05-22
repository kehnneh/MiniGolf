#include <vector>

#define SAFE_DELETE(X) if (X) { delete X; X = 0; }

template<typename T>
void DeleteVector(std::vector<T*> **vec)
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
