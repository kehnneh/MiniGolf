#include "GameMenu.h"

#include "CommonUtils.h"

#include <gl\glew.h>
#include <gl\freeglut.h>

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

void GameMenu::RenderText(FloatingText *ft)
{
  if (ft->selected > 0)
  {
    glColor3f(selectedColor.x, selectedColor.y, selectedColor.z);
  }
  else
  {
    glColor3f(color.x, color.y, color.z);
  }
  
  glRasterPos2f(ft->pos.x, ft->pos.y);
  const char *str = ft->str.c_str();
  int len = (int) strlen(str);
  for (int i = 0; i < len; i++)
  {
    glutBitmapCharacter(ft->font, str[i]);
  }
}

void GameMenu::Render()
{
  std::vector<FloatingText*>::iterator it = _text->begin(), end = _text->end();
  for (; it != end; it++)
  {
    RenderText(*it);
  }
}