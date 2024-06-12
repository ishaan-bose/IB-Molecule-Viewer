#pragma once

#include "raylib.h"
#include "raymath.h"

struct orbital
{
        vec orbitalLength;
        //read Conventions.md in "Conventions And Usage" folder for further details

        int type;
        //Using int not as an integer but as a data type of 4 bytes, used for all conventions such as
        //MOT, VBT, CFT, etc. Read Conventions.md in "Conventions And Usage" for more details about what
        //each bit and byte means



        //I am a bit stuck if I should implement the energy level of each orbital, because its a pain in the ass
        //to calculate the energy of each orbital using stuff like DFT if i want to be accurate
        //and if I am anyways implementing DFT I can also use it for bond lengths and stuff, but its too much work
        //and I am lazy
};
