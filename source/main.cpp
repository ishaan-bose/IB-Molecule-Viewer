/*#include "imgui.h"
#include "rlImGui.h"
#include "imgui_impl_raylib.h"*/


#include "raylib.h"
#include "raymath.h"
#include "raymath_operators.hpp"
#include "rcamera.h"

#include <iostream>
#include <vector>
#include <fstream>

int main()
{
    std::cout << "everything is initialized correctly :)" << std::endl;

    /*
    ░██╗░░░░░░░██╗██╗███╗░░██╗██████╗░░█████╗░░██╗░░░░░░░██╗
    ░██║░░██╗░░██║██║████╗░██║██╔══██╗██╔══██╗░██║░░██╗░░██║
    ░╚██╗████╗██╔╝██║██╔██╗██║██║░░██║██║░░██║░╚██╗████╗██╔╝
    ░░████╔═████║░██║██║╚████║██║░░██║██║░░██║░░████╔═████║░
    ░░╚██╔╝░╚██╔╝░██║██║░╚███║██████╔╝╚█████╔╝░░╚██╔╝░╚██╔╝░
    ░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░░╚════╝░░░░╚═╝░░░╚═╝░░
    */
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 800, "IB Molecule Viewer");
    SetTargetFPS(60);  // Set the desired frames-per-second

    


    /*
    ░██████╗░█████╗░███████╗███╗░░██╗███████╗
    ██╔════╝██╔══██╗██╔════╝████╗░██║██╔════╝
    ╚█████╗░██║░░╚═╝█████╗░░██╔██╗██║█████╗░░
    ░╚═══██╗██║░░██╗██╔══╝░░██║╚████║██╔══╝░░
    ██████╔╝╚█████╔╝███████╗██║░╚███║███████╗
    ╚═════╝░░╚════╝░╚══════╝╚═╝░░╚══╝╚══════╝
    */

    Model pOrbital = LoadModel("./resources/models/p orbital.obj");


    /*
    ░█████╗░░█████╗░███╗░░░███╗███████╗██████╗░░█████╗░
    ██╔══██╗██╔══██╗████╗░████║██╔════╝██╔══██╗██╔══██╗
    ██║░░╚═╝███████║██╔████╔██║█████╗░░██████╔╝███████║
    ██║░░██╗██╔══██║██║╚██╔╝██║██╔══╝░░██╔══██╗██╔══██║
    ╚█████╔╝██║░░██║██║░╚═╝░██║███████╗██║░░██║██║░░██║
    ░╚════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝
    */

    //DEFINITELY DIDNT STEAL THIS FROM THE RAYLIB EXAMPLES

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type




    /*
    ███╗░░░███╗░█████╗░██╗███╗░░██╗  ██╗░░░░░░█████╗░░█████╗░██████╗░
    ████╗░████║██╔══██╗██║████╗░██║  ██║░░░░░██╔══██╗██╔══██╗██╔══██╗
    ██╔████╔██║███████║██║██╔██╗██║  ██║░░░░░██║░░██║██║░░██║██████╔╝
    ██║╚██╔╝██║██╔══██║██║██║╚████║  ██║░░░░░██║░░██║██║░░██║██╔═══╝░
    ██║░╚═╝░██║██║░░██║██║██║░╚███║  ███████╗╚█████╔╝╚█████╔╝██║░░░░░
    ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝  ╚══════╝░╚════╝░░╚════╝░╚═╝░░░░░
    */
    SetExitKey(KEY_NULL);
    Color color = GRAY; //note: remove when necessary or when you feel like it
    float frameDeltaTime = 1; //placeholder value 1, or else it might complain about dividing by 0
    bool InMenu = false; //in menu refers to  being in menu, if it is true it means the user is in menu
    //such as graphics, audio, other settings, NOTE: IMGUI WILL HANDLE MOUSE INPUTS TOO, BE CAREFUL, SO DONT USE
    //ImGui::GetIO().WantCaptureMouse WHILE ALSO EXPECTING THE GAME TO CAPTURE MOUSE CORRECTLY, hence the InMenu bool
    //is so important
    /*
    █▄░█ █▀█ ▀█▀ █▀▀ ▀   █▀▀ █░█ ▄▀█ █▄░█ █▀▀ █▀▀   █ █▄░█ █▀▄▀█ █▀▀ █▄░█ █░█   ▀█▀ █▀█   ▀█▀ █▀█ █░█ █▀▀
    █░▀█ █▄█ ░█░ ██▄ ▄   █▄▄ █▀█ █▀█ █░▀█ █▄█ ██▄   █ █░▀█ █░▀░█ ██▄ █░▀█ █▄█   ░█░ █▄█   ░█░ █▀▄ █▄█ ██▄

    ▄▀█ █▀▀ ▀█▀ █▀▀ █▀█   ▀█▀ █▀▀ █▀ ▀█▀ █ █▄░█ █▀▀ ░   █▀▀ █▀█ █▀█   ▀█▀ █░█ █▀▀   █▀▀ █ █▄░█ █ █▀ █░█ █▀▀ █▀▄
    █▀█ █▀░ ░█░ ██▄ █▀▄   ░█░ ██▄ ▄█ ░█░ █ █░▀█ █▄█ █   █▀░ █▄█ █▀▄   ░█░ █▀█ ██▄   █▀░ █ █░▀█ █ ▄█ █▀█ ██▄ █▄▀

    █▀█ █▀█ █▀█ █▀▄ █░█ █▀▀ ▀█▀   █▄█ █▀█ █░█   █▀ █░█ █▀█ █░█ █░░ █▀▄   █▄▄ █▄█   █▀▄ █▀▀ █▀▀ ▄▀█ █░█ █░░ ▀█▀   █▄▄ █▀▀
    █▀▀ █▀▄ █▄█ █▄▀ █▄█ █▄▄ ░█░   ░█░ █▄█ █▄█   ▄█ █▀█ █▄█ █▄█ █▄▄ █▄▀   █▄█ ░█░   █▄▀ ██▄ █▀░ █▀█ █▄█ █▄▄ ░█░   █▄█ ██▄

    █ █▄░█   ▀█▀ █░█ █▀▀   █▀▄▀█ █▀▀ █▄░█ █░█
    █ █░▀█   ░█░ █▀█ ██▄   █░▀░█ ██▄ █░▀█ █▄█
    */

    Vector2 mousePos;
    DisableCursor();


    while (!WindowShouldClose())
    {
        frameDeltaTime = GetFrameTime();

        

        /*
        ██╗███╗░░██╗██████╗░██╗░░░██╗████████╗  ░█████╗░██╗░░██╗███████╗░█████╗░██╗░░██╗
        ██║████╗░██║██╔══██╗██║░░░██║╚══██╔══╝  ██╔══██╗██║░░██║██╔════╝██╔══██╗██║░██╔╝
        ██║██╔██╗██║██████╔╝██║░░░██║░░░██║░░░  ██║░░╚═╝███████║█████╗░░██║░░╚═╝█████═╝░
        ██║██║╚████║██╔═══╝░██║░░░██║░░░██║░░░  ██║░░██╗██╔══██║██╔══╝░░██║░░██╗██╔═██╗░
        ██║██║░╚███║██║░░░░░╚██████╔╝░░░██║░░░  ╚█████╔╝██║░░██║███████╗╚█████╔╝██║░╚██╗
        ╚═╝╚═╝░░╚══╝╚═╝░░░░░░╚═════╝░░░░╚═╝░░░  ░╚════╝░╚═╝░░╚═╝╚══════╝░╚════╝░╚═╝░░╚═╝
        */

        //bool CursorDisabled = true; //uncomment this later


        mousePos = GetMouseDelta();

        /*
        ▀▀█▀▀ █▀▀█ █▀▀▄ █▀▀█ ▄
        ░░█░░ █░░█ █░░█ █░░█ ░
        ░░▀░░ ▀▀▀▀ ▀▀▀░ ▀▀▀▀ ▀
        */
        //create an array to store all the current keys being pressed at the moment, and later
        //make handler code that will do everything that needs to be done such as animations, loading, etc while
        //also taking care of the input


        /*
        ▀▀█▀▀ █▀▀█ █▀▀▄ █▀▀█ ▄
        ░░█░░ █░░█ █░░█ █░░█ ░
        ░░▀░░ ▀▀▀▀ ▀▀▀░ ▀▀▀▀ ▀
        */
       //write some code to find if the mouse is in the scene view region or in the menu region, and the menu and screen view
       //can be dynamically changed, also the mouse being outside of the window counts as menu, for simplicity sake 
        
            
        if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_ESCAPE))
        {
           goto PROGRAM_END;
        }   //setup a way to forcefully exit program no matter what

        if(!InMenu) //in app controls such as moving camera, moving objects, etc
        {

            if(IsKeyPressed(KEY_HOME)) //just a simple code to switch to menu, later implement the todo that is above
            {
                EnableCursor();
                InMenu = true;
            }

            if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            {
                if(IsKeyDown(KEY_W))
                {
                    CameraMoveForward(&camera, 0.2f, false);
                }

                if(IsKeyDown(KEY_S))
                {
                    CameraMoveForward(&camera, -0.2f, false);
                }

                if(IsKeyDown(KEY_D))
                {
                    CameraMoveRight(&camera, 0.2f, false);
                }

                if(IsKeyDown(KEY_A))
                {
                    CameraMoveRight(&camera, -0.2f, false);
                }

                if(IsKeyDown(KEY_E))
                {
                    CameraMoveUp(&camera, 0.2f);
                }

                if(IsKeyDown(KEY_Q))
                {
                    CameraMoveUp(&camera, -0.2f);
                }

                //there is '-' because for some reason it is inverting it idk why
                CameraYaw(&camera, -mousePos.x*0.005f, false);
                CameraPitch(&camera, -mousePos.y*0.005f, true, false, false); //DONT SET ROTATE UP PARAMETER TO TRUE
                //wasted like 1 hour of my time figuring it out
            }
        }
        else if(InMenu)
        {

            if(IsKeyPressed(KEY_HOME)) //just a simple code to switch to scene, later implement the todo that is above
            {
                DisableCursor();
                InMenu = false;
            }
        }

        









        /*
        ██████╗░██████╗░░█████╗░░██╗░░░░░░░██╗██╗███╗░░██╗░██████╗░
        ██╔══██╗██╔══██╗██╔══██╗░██║░░██╗░░██║██║████╗░██║██╔════╝░
        ██║░░██║██████╔╝███████║░╚██╗████╗██╔╝██║██╔██╗██║██║░░██╗░
        ██║░░██║██╔══██╗██╔══██║░░████╔═████║░██║██║╚████║██║░░╚██╗
        ██████╔╝██║░░██║██║░░██║░░╚██╔╝░╚██╔╝░██║██║░╚███║╚██████╔╝
        ╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝░╚═════╝░
        */
        BeginDrawing();

        {

            /*
            ░██████╗░██╗░░░██╗██╗  ██████╗░███████╗███╗░░██╗██████╗░███████╗██████╗░██╗███╗░░██╗░██████╗░
            ██╔════╝░██║░░░██║██║  ██╔══██╗██╔════╝████╗░██║██╔══██╗██╔════╝██╔══██╗██║████╗░██║██╔════╝░
            ██║░░██╗░██║░░░██║██║  ██████╔╝█████╗░░██╔██╗██║██║░░██║█████╗░░██████╔╝██║██╔██╗██║██║░░██╗░
            ██║░░╚██╗██║░░░██║██║  ██╔══██╗██╔══╝░░██║╚████║██║░░██║██╔══╝░░██╔══██╗██║██║╚████║██║░░╚██╗
            ╚██████╔╝╚██████╔╝██║  ██║░░██║███████╗██║░╚███║██████╔╝███████╗██║░░██║██║██║░╚███║╚██████╔╝
            ░╚═════╝░░╚═════╝░╚═╝  ╚═╝░░╚═╝╚══════╝╚═╝░░╚══╝╚═════╝░╚══════╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░╚═════╝░
            */




            /*
            ███╗░░░███╗░█████╗░██╗███╗░░██╗  ██████╗░███████╗███╗░░██╗██████╗░███████╗██████╗░██╗███╗░░██╗░██████╗░
            ████╗░████║██╔══██╗██║████╗░██║  ██╔══██╗██╔════╝████╗░██║██╔══██╗██╔════╝██╔══██╗██║████╗░██║██╔════╝░
            ██╔████╔██║███████║██║██╔██╗██║  ██████╔╝█████╗░░██╔██╗██║██║░░██║█████╗░░██████╔╝██║██╔██╗██║██║░░██╗░
            ██║╚██╔╝██║██╔══██║██║██║╚████║  ██╔══██╗██╔══╝░░██║╚████║██║░░██║██╔══╝░░██╔══██╗██║██║╚████║██║░░╚██╗
            ██║░╚═╝░██║██║░░██║██║██║░╚███║  ██║░░██║███████╗██║░╚███║██████╔╝███████╗██║░░██║██║██║░╚███║╚██████╔╝
            ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝  ╚═╝░░╚═╝╚══════╝╚═╝░░╚══╝╚═════╝░╚══════╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░╚═════╝░
            */

            ClearBackground(color);


            BeginMode3D(camera);


                DrawModel(pOrbital, (Vector3){ 1.0, 0.0, 0.0 }, 3.0f, BLUE);
                DrawGrid(100, 1.0f);


            EndMode3D();
        }

        EndDrawing();
    }



    /*
    ░█████╗░██╗░░░░░███████╗░█████╗░███╗░░██╗██╗░░░██╗██████╗░
    ██╔══██╗██║░░░░░██╔════╝██╔══██╗████╗░██║██║░░░██║██╔══██╗
    ██║░░╚═╝██║░░░░░█████╗░░███████║██╔██╗██║██║░░░██║██████╔╝
    ██║░░██╗██║░░░░░██╔══╝░░██╔══██║██║╚████║██║░░░██║██╔═══╝░
    ╚█████╔╝███████╗███████╗██║░░██║██║░╚███║╚██████╔╝██║░░░░░
    ░╚════╝░╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚══╝░╚═════╝░╚═╝░░░░░
    */

    //later implement a system where if you exit the app, it will use goto to go to this label

    PROGRAM_END:

    EnableCursor();
    ShowCursor();

    UnloadModel(pOrbital);


    CloseWindow();  // Close the window and OpenGL context

    return 0;
}
