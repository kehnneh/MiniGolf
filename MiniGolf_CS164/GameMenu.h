#pragma once

#include <string>
#include <vector>

#include <glm\glm.hpp>

struct FloatingText
{
  glm::vec2 pos;
  int selected;
  void *font;
  std::string str;
};

class GameMenu
{
private:
  std::vector<FloatingText*> *_text;

  void RenderText(FloatingText *ft);

public:
  GameMenu() :
    _text(0)
  {}

  ~GameMenu()
  {}

  unsigned char Initialize();

  unsigned char DeInitialize();

  void Render();
};

