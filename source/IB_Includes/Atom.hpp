#pragma once
#include "raymath.h"

struct Atom
{
    short Atomic_Mass_And_Atomic_Num;
    //9 bytes for atomic mass, 7 bytes for atomic number
    //atomic number only goes till 128, I am hoping there are no elements beyond
    //128 discovered and hoping no mass goes beyond 512

    //TODO: AFTER ORBITAL STRUCT MADE, MAKE LIST OF ATOMIC ORBITALS
};
