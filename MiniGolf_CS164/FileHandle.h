#pragma once

#include <fstream>
#include <string>

class FileHandle
{
  std::fstream _f;
  char *_buf;

public:
  FileHandle()
  {}

  ~FileHandle()
  {}

  unsigned char Open(std::string);

  void Close();

  // Reads lines for levels
  unsigned char ReadLine(char delim, char *out_func, char *out_params);

  bool eof() const;

  static const unsigned int MaxLineLen();
};

