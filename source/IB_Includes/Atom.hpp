#pragma once
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
    virtual void PrintFillingAndHybridization() const = 0;
    virtual uint16_t GetFillingAndHybridization() const = 0;

    virtual Vector3 GetSOrbital() = 0;

    virtual void SetSOrbital(const Vector3& inDir, uint16_t Filling) = 0;

    virtual Vector3 GetPxrbital() = 0;

    virtual void SetPxOrbital(const Vector3& inDir, uint16_t Filling) = 0;

    virtual Vector3 GetPyOrbital() = 0;

    virtual void SetPyOrbital(const Vector3& inDir, uint16_t Filling) = 0;

    virtual Vector3 GetPzOrbital() = 0;

    virtual void SetPzOrbital(const Vector3& inDir, uint16_t Filling) = 0;




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
        return Rotation;
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

    void SetSOrbital(const Vector3& inDir, uint16_t Filling) override
    {
        sO = inDir;
        ChangeBits(FillingAndHybridization, 0, 2, Filling);

    }

    Vector3 GetPxrbital() override
    {
        return (Vector3)pxO;
    }

    void SetPxOrbital(const Vector3& inDir, uint16_t Filling) override
    {
        pxO = inDir;
        ChangeBits(FillingAndHybridization, 2, 2, Filling);

    }

    Vector3 GetPyOrbital() override
    {
        return (Vector3)pyO;
    }

    void SetPyOrbital(const Vector3& inDir, uint16_t Filling) override
    {
        pyO = inDir;
        ChangeBits(FillingAndHybridization, 4, 2, Filling);

    }

    Vector3 GetPzOrbital() override
    {
        return (Vector3)pzO;
    }

    void SetPzOrbital(const Vector3& inDir, uint16_t Filling) override
    {
        pzO = inDir;
        ChangeBits(FillingAndHybridization, 6, 2, Filling);
        
    }



    void PrintFillingAndHybridization() const override
    {

        
        //S ORBITAL
        switch (extractBits(this->FillingAndHybridization, 0, 2))
        {
        case 0:
            //00 = 0 = empty orbital
            std::cout << "S: empty, ";
            break;
        case 1:
            //01 = 1 = half filled orbital
            std::cout << "S: half, ";
            break;
        case 2:
            //10 = 2 = fully filled orbital
            std::cout << "S: full, ";
            break;
        case 3:
            //11 = 3 = disabled orbital, aka the orbital is not in use
            std::cout << "S: disabled, ";
            break;
        default:
            break;
        }



        //Px ORBITAL
        switch (extractBits(this->FillingAndHybridization, 2, 2))
        {
        case 0:
            //00 = 0 = empty orbital
            std::cout << "Px: empty, ";
            break;
        case 1:
            //01 = 1 = half filled orbital
            std::cout << "Px: half, ";
            break;
        case 2:
            //10 = 2 = fully filled orbital
            std::cout << "Px: full, ";
            break;
        case 3:
            //11 = 3 = disabled orbital, aka the orbital is not in use
            std::cout << "Px: disabled, ";
            break;
        default:
            break;
        }



        //Py ORBITAL
        switch (extractBits(this->FillingAndHybridization, 4, 2))
        {
        case 0:
            //00 = 0 = empty orbital
            std::cout << "Py: empty, ";
            break;
        case 1:
            //01 = 1 = half filled orbital
            std::cout << "Py: half, ";
            break;
        case 2:
            //10 = 2 = fully filled orbital
            std::cout << "Py: full, ";
            break;
        case 3:
            //11 = 3 = disabled orbital, aka the orbital is not in use
            std::cout << "Py: disabled, ";
            break;
        default:
            break;
        }



        //Pz ORBITAL
        switch (extractBits(this->FillingAndHybridization, 6, 2))
        {
        case 0:
            //00 = 0 = empty orbital
            std::cout << "Pz: empty, ";
            break;
        case 1:
            //01 = 1 = half filled orbital
            std::cout << "Pz: half, ";
            break;
        case 2:
            //10 = 2 = fully filled orbital
            std::cout << "Pz: full, ";
            break;
        case 3:
            //11 = 3 = disabled orbital, aka the orbital is not in use
            std::cout << "Pz: disabled, ";
            break;
        default:
            break;
        }



        //HYRBIDIZATION
        switch (extractBits(this->FillingAndHybridization, 8, 4))
        {
        case 12:
            //1100 = 12 = UnHybridized
            std::cout << "No / negligible Hybridization\n";
            break;
        case 1:
            //0001 = 1 = sp hybridization
            std::cout << "sp hybridization\n";
            break;
        case 2:
            //0010 = 2 = sp2 hybridization
            std::cout << "sp2 hybridization\n";
            break;
        case 3:
            //0011 = 3 = sp3 hybridization
            std::cout << "sp3 hybridization\n";
            break;
        
        default:
            break;
        }
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

    void PrintFillingAndHybridization() const override
    {

    }

    MidAtom();
    ~MidAtom();
};




}   //namespace end



