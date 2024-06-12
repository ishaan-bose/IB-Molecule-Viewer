#include "imgui.h"
#include "rlImGui.h"
#include "imgui_impl_raylib.h"
#include "raymath.h"
#include "raylib.h"
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

    // Setup Dear ImGui context
    rlImGuiSetup(true);
    ImGui::StyleColorsDark();


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
    camera.position = (Vector3){ 15.0f,-31.0f, 4.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 90.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type




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
    Vector2 mousePosition = {0.0f, 0.0f}; //the change in the mouse position
    Vector2 mouseSpeed = {0.0f, 0.0f};
    float mouseSensitivity = 0.5f;

    HideCursor();

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

        //bool CursorDisabled = true; //uncomment this later+

        mousePosition = GetMousePosition();
        mouseSpeed = Vector2Scale(mousePosition, frameDeltaTime*mouseSensitivity);
        

        CameraYaw(&camera, mouseSpeed.x, false);
        CameraPitch(&camera, mouseSpeed.y, true, false, true);

        /*
        ▀▀█▀▀ █▀▀█ █▀▀▄ █▀▀█ ▄
        ░░█░░ █░░█ █░░█ █░░█ ░
        ░░▀░░ ▀▀▀▀ ▀▀▀░ ▀▀▀▀ ▀
        */
        //create an array to store all the current keys being pressed at the moment, and later
        //make handler code that will do everything that needs to be done such as animations, loading, etc while
        //also taking care of the input
        if(!ImGui::GetIO().WantCaptureMouse)
        {

            if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_ESCAPE))
            {
                goto PROGRAM_END;
            }

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

        }









        /*
        ██████╗░░█████╗░██╗░░░██╗██╗░░░░░██╗██████╗░  ██████╗░██████╗░░█████╗░░██╗░░░░░░░██╗██╗███╗░░██╗░██████╗░
        ██╔══██╗██╔══██╗╚██╗░██╔╝██║░░░░░██║██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░██║░░██╗░░██║██║████╗░██║██╔════╝░
        ██████╔╝███████║░╚████╔╝░██║░░░░░██║██████╦╝  ██║░░██║██████╔╝███████║░╚██╗████╗██╔╝██║██╔██╗██║██║░░██╗░
        ██╔══██╗██╔══██║░░╚██╔╝░░██║░░░░░██║██╔══██╗  ██║░░██║██╔══██╗██╔══██║░░████╔═████║░██║██║╚████║██║░░╚██╗
        ██║░░██║██║░░██║░░░██║░░░███████╗██║██████╦╝  ██████╔╝██║░░██║██║░░██║░░╚██╔╝░╚██╔╝░██║██║░╚███║╚██████╔╝
        ╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚═╝╚═════╝░  ╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝░╚═════╝░
        */
        BeginDrawing();
        rlImGuiBegin();

        {

            /*
            ░██████╗░██╗░░░██╗██╗
            ██╔════╝░██║░░░██║██║
            ██║░░██╗░██║░░░██║██║
            ██║░░╚██╗██║░░░██║██║
            ╚██████╔╝╚██████╔╝██║
            ░╚═════╝░░╚═════╝░╚═╝
            */

            ImGui::Begin("hi there");
            ImGui::Text("Hello there!");


            ImGui::End();



            /*
            ██████╗░███████╗███╗░░██╗██████╗░███████╗██████╗░██╗███╗░░██╗░██████╗░
            ██╔══██╗██╔════╝████╗░██║██╔══██╗██╔════╝██╔══██╗██║████╗░██║██╔════╝░
            ██████╔╝█████╗░░██╔██╗██║██║░░██║█████╗░░██████╔╝██║██╔██╗██║██║░░██╗░
            ██╔══██╗██╔══╝░░██║╚████║██║░░██║██╔══╝░░██╔══██╗██║██║╚████║██║░░╚██╗
            ██║░░██║███████╗██║░╚███║██████╔╝███████╗██║░░██║██║██║░╚███║╚██████╔╝
            ╚═╝░░╚═╝╚══════╝╚═╝░░╚══╝╚═════╝░╚══════╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░╚═════╝░
            */

            ImGui::Render();
            ClearBackground(color);


            BeginMode3D(camera);


                DrawModel(pOrbital, (Vector3){ 1.0, 0.0, 0.0 }, 3.0f, BLUE);
                DrawGrid(15, 1.0f);


            EndMode3D();
        }


        rlImGuiEnd();
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


    rlImGuiShutdown();
    CloseWindow();  // Close the window and OpenGL context

    return 0;
}
