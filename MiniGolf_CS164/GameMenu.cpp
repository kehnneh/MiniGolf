#include "GameMenu.h"

#include "CommonUtils.h"

glm::vec3 selectedColor(1.f, 0.f, 0.f);
glm::vec3 color(1.f, 1.f, 1.f);

unsigned char GameMenu::Initialize()
{
  _text = new std::vector<FloatingText*>;

  return STATUS_OK;
}

unsigned char GameMenu::DeInitialize()
{
  DeleteVectorPtrs(&_text);

  return STATUS_OK;
}