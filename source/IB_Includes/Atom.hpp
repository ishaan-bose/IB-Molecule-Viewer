#pragma once
#include "raymath.h"
#include "raylib.h"
#include <vector>
#include "halfVec3.hpp"


//This is a C++ abstract class, if you dont know about it, a quick net search will
//explain what it is
class Atom
{
public:
    short AtomicNeutronsAndNumber;
    //read conventions.md for full understanding on how each bit is used
    Vector3 Position;
    Vector3 Rotation;   //wrt world space
    //NOTE: I WILL NOT IMPLEMENT OVER HERE ROTATION WITH RESPECT TO MOLECULE
    //THERE WILL BE A SEPERATE FUNCTION THAT IF I WANT TO ROTATE A MOLECULE IT WIL GO THROUGH EACH
    //ATOM AND ROTATE IT INDIVISUALLY
   
    virtual void Hybridize() = 0;
    virtual void UnHybridize() = 0;

    Atom(short atomic_neutrons_and_number, Vector3 pos, Vector3 rot)
    : AtomicNeutronsAndNumber{atomic_neutrons_and_number}, Position{pos}, Rotation{rot}
    {}

    virtual ~Atom()
    {}
};





//SmolAtom will have 4 orbitals only, the s and p orbitals
//SmolAtom is from Hydrogen to Magnesium
//O at the end of the orbitals stands for "Orbital"
class SmolAtom : public Atom
{
    hVec3 sO, pxO, pyO, pzO;
    short FillingAndHybridization;

public:
    SmolAtom();
    ~SmolAtom();
};



//MediumAtom will have 9 orbitals
//MediumAtom ranges from Aluminium to Strontium
//Mid stands for Medium
//O at the end of the orbitals stands for "Orbital"
class MidAtom : public Atom
{
    hVec3 sO, pxO, pyO, pzO;
    hVec3 dxyO, dyzO, dxzO, dx2y2O, dz2O;

public:
    MidAtom();
    ~MidAtom();
};
