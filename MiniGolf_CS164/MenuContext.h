#pragma once

#include <string>
#include <list>

#include <glm\glm.hpp>

#include <gl\glew.h>
#include <gl\freeglut.h>

struct FloatingText
{
  glm::vec2 pos;
  std::string str;
};

class MenuContext
{
private:
  typedef void* font;

  std::list<FloatingText*> *_selectableText, *_staticText;
  glm::vec3 *_selectedColor, *_color;
  font _glutFont;
  unsigned int _selection;

  void RenderSelectableText(FloatingText * const ft, bool selected);
  void RenderStaticText(FloatingText * const ft);

public:
  MenuContext() :
    _selectableText(0), _staticText(0),
    _glutFont(GLUT_BITMAP_TIMES_ROMAN_10),
    _selection(0),
    _selectedColor(0), _color(0)
  {}

  ~MenuContext()
  {}

  unsigned char Initialize();

  unsigned char DeInitialize();

  unsigned char AddSelectableText(std::string, glm::vec2);

  unsigned char AddStaticText(std::string, glm::vec2);

  void SetStaticText(unsigned int level, std::string str);

  unsigned char SetSelectedColor(glm::vec3 selectedColor);

  unsigned char SetColor(glm::vec3 color);

  unsigned int Selection();

  void SelectNext();

  void SelectPrevious();

  void Render();
};

