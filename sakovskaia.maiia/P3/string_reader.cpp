#include "string_reader.hpp"
#include <iostream>
#include <iomanip>

char * sakovskaia::readString(std::istream & input)
{
  size_t size = 10;
  char * buffer = new char[size];
  char * new_buffer = nullptr;
  char c = 0;
  size_t i = 0;
  size_t n = 1;
  input >> std::noskipws;
  while ((input >> c) && (c != '\n'))
  {
    if (!input)
    {
      delete [] buffer;
      throw std::logic_error("Error in input");
    }
    buffer[i++] = c;
    if (i == (size - 1))
    {
      size_t new_size = size + 10;
      try
      {
        new_buffer = new char[new_size];
        for (size_t j = 0; j < i; j++)
        {
          new_buffer[j] = buffer[j];
        }
        delete [] buffer;
        buffer = new_buffer;
        size = new_size;
      }
      catch (const std::bad_alloc &e)
      {
        delete [] buffer;
        buffer = nullptr;
      }
    }
    buffer[i] = '\n';
    if ((buffer[0] == '\n') || (buffer[0] == '\0'))
    {
      delete [] buffer;
      throw std::logic_error("String is empty");
    }
  }
  input >> std::skipws;
  return buffer;
}