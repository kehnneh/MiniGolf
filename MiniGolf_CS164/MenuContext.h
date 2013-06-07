#pragma once

#include <string>
#include <list>

#include <glm\glm.hpp>

#include <gl\glew.h>
#include <gl\freeglut.h>

/// Text that is displayed at the given position
struct FloatingText
{
  glm::vec2 pos;
  std::string str;
};

/// Defines what gets displayed on-screen for a particular context of menu
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

  /// Performs data allocation
  unsigned char Initialize();

  /// Performs data deallocation
  unsigned char DeInitialize();

  /// Adds text that can be cycled through and selected
  unsigned char AddSelectableText(std::string, glm::vec2);

  /// Adds text that is displayed
  unsigned char AddStaticText(std::string, glm::vec2);

  /// Changes displayed scoring text on screen
  void SetStaticText(unsigned int level, std::string str);

  /// Sets the color of the selected option
  unsigned char SetSelectedColor(glm::vec3 selectedColor);

  /// Sets the color of non-selected text
  unsigned char SetColor(glm::vec3 color);

  /// Returns the option selected
  unsigned int Selection();

  /// Selects the next option
  void SelectNext();

  /// Selects the previous option
  void SelectPrevious();

  /// Renders the menu
  void Render();
};

