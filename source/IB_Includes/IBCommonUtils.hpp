#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdint>

namespace IBMol
{
  float RandomFloatRange(float min, float max)
  {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
  }

  inline uint16_t extractBits(uint16_t num, char pos, char k)
  {
    return static_cast<uint16_t>(num << pos) >> (16-k);
  }

  inline void ChangeBits(uint16_t& num, char pos, char k, uint16_t newValue)
  {
      /*get all bits after pos + k &          changing the bits at the position
      set all previous ones to 0*/
      num = (  static_cast<uint16_t>(num << (pos+k))  >>  (pos+k)  )   |    (( ( (num >> (16-pos)) << k ) | newValue ) << (16-pos-k));
  }

  inline bool DoesFileExist (const std::string& name)
  {
    struct stat buffer;   
    return (stat (name.c_str(), &buffer) == 0);
  }

  Vector3 GetRandomPerpVecNormalized(Vector3 input)
  {
    Vector3 i = Vector3Normalize(input);

    if(i.x == 0.0 && i.y == 1.0 && i.z == 0.0)
    {
      return Vector3{1.0, 0.0, 0.0};
    }

    return Vector3CrossProduct(input, Vector3{0.0, 1.0, 0.0});
  } 
}