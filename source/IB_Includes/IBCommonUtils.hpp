#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <stdexcept>
#include <string>
#include "Atom.hpp"




inline bool DoesFileExist (const std::string& name)
{
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0);
}