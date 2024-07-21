#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <stdexcept>
#include <string>


unsigned int extractBits(unsigned int num, unsigned int pos, unsigned int k)
{
    return ((num >> pos) & ((1 << k) - 1));
}


inline bool DoesFileExist (const std::string& name)
{
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0);
}