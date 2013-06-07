#include "MenuContext.h"

#include "CommonUtils.h"

unsigned char MenuContext::Initialize()
{
  _selectableText = new std::list<FloatingText*>;
  _staticText = new std::list<FloatingText*>;

  _selectedColor = new glm::vec3(1.f, 0.f, 0.f);
  _color = new glm::vec3(1.f, 1.f, 1.f);

  return STATUS_OK;
}

unsigned char MenuContext::DeInitialize()
{
  std::list<FloatingText*>::iterator it, end;

  it = _selectableText->begin(), end = _selectableText->end();
  for (; it != end; it++)
  {
    Delete(&(*it));
  }

  it = _staticText->begin(), end = _staticText->end();
  for (; it != end; it++)
  {
    Delete(&(*it));
  }

  Delete(&_selectedColor);
  Delete(&_color);

  return STATUS_OK;
}

unsigned char MenuContext::AddSelectableText(std::string str, glm::vec2 pos)
{
  FloatingText *ft = new FloatingText;
  ft->str = str;
  ft->pos = pos;

  _selectableText->push_back(ft);

  return STATUS_OK;
}

unsigned char MenuContext::AddStaticText(std::string str, glm::vec2 pos)
{
  FloatingText *ft = new FloatingText;
  ft->str = str;
  ft->pos = pos;

  _staticText->push_back(ft);

  return STATUS_OK;
}

void MenuContext::Render()
{
  std::list<FloatingText*>::iterator it = _selectableText->begin(), end = _selectableText->end();
  for (; it != end; it++)
  {
    RenderSelectableText(*it, std::distance(_selectableText->begin(), it) == _selection ? true : false);
  }

  it = _staticText->begin(), end = _staticText->end();
  for (; it != end; it++)
  {
    RenderStaticText(*it);
  }
}

unsigned char MenuContext::SetSelectedColor(glm::vec3 selectedColor)
{
  *_selectedColor = selectedColor;
  return STATUS_OK;
}

unsigned char MenuContext::SetColor(glm::vec3 color)
{
  *_color = color;
  return STATUS_OK;
}

void MenuContext::RenderSelectableText(FloatingText * const ft, bool selected)
{
  if (selected)
  {
    glColor3f(_selectedColor->x, _selectedColor->y, _selectedColor->z);
  }
  else
  {
    glColor3f(_color->x, _color->y, _color->z);
  }
  
  glRasterPos3i(ft->pos.x, ft->pos.y, 0);
  const char *str = ft->str.c_str();
  int len = (int) strlen(str);
  for (int i = 0; i < len; i++)
  {
    glutBitmapCharacter(_glutFont, str[i]);
  }
}

void MenuContext::RenderStaticText(FloatingText * const ft)
{
  glColor3f(_color->x, _color->y, _color->z);
  glRasterPos2f(ft->pos.x, ft->pos.y);
  const char *str = ft->str.c_str();
  int len = (int) strlen(str);
  for (int i = 0; i < len; i++)
  {
    glutBitmapCharacter(_glutFont, str[i]);
  }
}

unsigned int MenuContext::Selection()
{
  return _selection;
}

void MenuContext::SetStaticText(unsigned int level, std::string str)
{
  std::list<FloatingText*>::iterator it = _staticText->begin();
  for (unsigned int i = 0; i < level; i++)
  {
    it++;
  }
  (*it)->str = str;
}

void MenuContext::SelectNext()
{
  if (_selection == _selectableText->size() - 1)
  {
    _selection = 0;
  }
  else
  {
    _selection++;
  }
}

void MenuContext::SelectPrevious()
{
  if (_selection == 0)
  {
    _selection = _selectableText->size() - 1;
  }
  else
  {
    _selection--;
  }
}