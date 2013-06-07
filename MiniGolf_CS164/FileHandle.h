#pragma once

#include <fstream>
#include <string>

/// Defines a handle to a file for easy usage in the LevelManager
class FileHandle
{
  std::fstream _f;
  char *_buf;

public:
  FileHandle()
  {}

  ~FileHandle()
  {}

  /// Opens a file. Returns a status code based on success or failure
  unsigned char Open(std::string);

  /// Closes the file represented by this FileHandle if it is open
  void Close();

  /// Reads a line from a file that is delimited by delim, and splits the first space-separated string from the rest of the text up until the next delim character
  unsigned char ReadLine(char delim, char *out_func, char *out_params);

  /// Returns true if the end of the file has been reached
  bool eof() const;

  /// Returns the maximum line length for a file
  static const unsigned int MaxLineLen();
};

