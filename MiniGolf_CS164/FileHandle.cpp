#include "FileHandle.h"
#include "CommonUtils.h"

#include <map>

using namespace std;

static const unsigned int
  MAX_LINE_SIZE = 1024;

const unsigned int FileHandle::MaxLineLen()
{
  return MAX_LINE_SIZE;
}

unsigned char FileHandle::Open(string filename)
{
  _f.open(filename.c_str());

  if (_f.fail())
  {
    return 0x2; // File failed to open
  }

  _buf = new char[MAX_LINE_SIZE];

  return STATUS_OK;
}

void FileHandle::Close()
{
  if (_f.is_open())
  {
    _f.close();
  }
}

bool FileHandle::eof() const
{
  return _f.eof();
}

unsigned char FileHandle::ReadLine(char delim, char *out_func, char *out_params)
{
  if (!_f.is_open() || _f.fail())
  {
    return 0x2; // No valid file is open
  }
  
  _f.getline(_buf, MAX_LINE_SIZE, delim);

#pragma warning( suppress : 4996 )
  sscanf(_buf, "%s %[^\t\n\r]", out_func, out_params);

  return STATUS_OK;
}