#pragma once
#include "rlgl.h"
#include "raymath.h"
#include "raylib.h"
#include <vector>
#include "halfVec3.hpp"
#include "IBCommonUtils.hpp"


static Matrix PxMat = MatrixRotateXYZ(Vector3{0.0, 0.0, PI/2.0});
static Matrix PyMat = MatrixRotateXYZ(Vector3{0.0, 0.0, 0.0});
static Matrix PzMat = MatrixRotateXYZ(Vector3{PI/2.0, 0.0, 0.0});

#define SP 1
#define SP2 2

namespace IBMol
{



//This is a C++ abstract class, if you dont know about it, a quick net search will
//explain what it is
class Atom
{
    //everything will be public, i am only using the class keyword to make it more readable, or else
    //it is the equivalent to a struct
public:
    short AtomicNeutronsAndNumber;
    //read conventions.md for full understanding on how each bit is used
    Vector3 Position;
    Vector3 Rotation;   //wrt world space
    //NOTE: I WILL NOT IMPLEMENT OVER HERE ROTATION WITH RESPECT TO MOLECULE
    //THERE WILL BE A SEPERATE FUNCTION THAT IF I WANT TO ROTATE A MOLECULE IT WIL GO THROUGH EACH
    //ATOM AND ROTATE IT INDIVISUALLY
   
    virtual void Hybridize(char HybridizationType) = 0;
    virtual void UnHybridize() = 0;
    virtual uint16_t GetFillingAndHybridization() const = 0;

    virtual Vector3 GetSOrbital() = 0;

    virtual void SetSOrbital(const Vector3& dir, uint16_t Filling) = 0;

    virtual Vector3 GetPxOrbital() = 0;

    virtual void SetPxOrbital(const Vector3& dir, uint16_t Filling) = 0;

    virtual Vector3 GetPyOrbital() = 0;

    virtual void SetPyOrbital(const Vector3& dir, uint16_t Filling) = 0;

    virtual Vector3 GetPzOrbital() = 0;

    virtual void SetPzOrbital(const Vector3& dir, uint16_t Filling) = 0;




    Vector3 GetAtomPosition()
    {
        return Position;
    }

    void SetAtomPosition(const Vector3& inPosition)
    {
        Position = inPosition;
    }

    Vector3 GetAtomRotation()
    {
        return Vector3Normalize(Rotation);
    }

    void SetAtomRotation(const Vector3& inRotation)
    {
        Rotation = inRotation;
    }

    Atom(short atomic_neutrons_and_number, Vector3 pos, Vector3 rot)
    : AtomicNeutronsAndNumber{atomic_neutrons_and_number}, Position{pos}, Rotation{rot}
    {}

    Atom(){}

    virtual ~Atom(){}
};


//SmolAtom will have 4 orbitals only, the s and p orbitals
//SmolAtom is from Hydrogen to Magnesium
//O at the end of the orbitals stands for "Orbital"
class SmolAtom : public Atom
{
    //everything will be public, i am only using the class keyword to make it more readable, or else
    //it is the equivalent to a struct
public:
    hVec3 sO, pxO, pyO, pzO;
    uint16_t FillingAndHybridization;

    Vector3 GetSOrbital() override
    {
        return (Vector3)sO;
    }

    void SetSOrbital(const Vector3& dir, uint16_t Filling) override
    {
        sO = dir;
        ChangeBits(FillingAndHybridization, 0, 2, Filling);

    }

    Vector3 GetPxOrbital() override
    {
        return (Vector3)pxO;
    }

    void SetPxOrbital(const Vector3& dir, uint16_t Filling) override
    {
        pxO = dir;
        ChangeBits(FillingAndHybridization, 2, 2, Filling);

    }

    Vector3 GetPyOrbital() override
    {
        return (Vector3)pyO;
    }

    void SetPyOrbital(const Vector3& dir, uint16_t Filling) override
    {
        pyO = dir;
        ChangeBits(FillingAndHybridization, 4, 2, Filling);

    }

    Vector3 GetPzOrbital() override
    {
        return (Vector3)pzO;
    }

    void SetPzOrbital(const Vector3& dir, uint16_t Filling) override
    {
        pzO = dir;
        ChangeBits(FillingAndHybridization, 6, 2, Filling);
        
    }


    uint16_t GetFillingAndHybridization() const override
    {
        return FillingAndHybridization;
    }


    //only 12 types of hybridization, hence make sure that HybridizationType is 4 bits of data
    void Hybridize(char HybridizationType) override
    {
        ChangeBits(FillingAndHybridization, 8, 4, HybridizationType);
    }

    void UnHybridize() override
    {
        ChangeBits(FillingAndHybridization, 8, 4, 12);
    }


    SmolAtom()
    {
        FillingAndHybridization = 0;


    }

    ~SmolAtom()
    {

    }
};



//MediumAtom will have 9 orbitals
//MediumAtom ranges from Aluminium to Strontium
//Mid stands for Medium
//O at the end of the orbitals stands for "Orbital"
class MidAtom : public Atom
{
    //everything will be public, i am only using the class keyword to make it more readable, or else
    //it is the equivalent to a struct
public:
    hVec3 sO, pxO, pyO, pzO;
    hVec3 dxyO, dyzO, dxzO, dx2y2O, dz2O;
    short FillingAndHybridization;


    MidAtom();
    ~MidAtom();
};
















}   //namespace end



