#pragma once
#include "raymath.h"
#include "raylib.h"
#include <vector>

struct Atom
{
    short AtomicMassAndNumber;
    /*
    read conventions.md for full understanding on how each bit is used
    */

    Vector3 Position;
    Vector3 Rotation;   //wrt world space
    //NOTE: I WILL NOT IMPLEMENT OVER HERE ROTATION WITH RESPECT TO MOLECULE
    //THERE WILL BE A SEPERATE FUNCTION THAT IF I WANT TO ROTATE A MOLECULE IT WIL GO THROUGH EACH
    //ATOM AND ROTATE IT INDIVISUALLY
   
    std::vector<Vector3> orbitals;
    std::vector<char> OrbitalFillingAndHybridization;
    

    Atom(short atomic_mass_and_number, Vector3 pos)
    : AtomicMassAndNumber{atomic_mass_and_number}, Position{pos}
    {
    }
};
