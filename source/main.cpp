/*#include "imgui.h"
#include "rlImGui.h"
#include "imgui_impl_raylib.h"*/


#include "raylib.h"
#include "raymath.h"
#include "raymath_operators.hpp"
#include "rcamera.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#include "IBCommonUtils.hpp"


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
    InitWindow(1200, 1200, "IB Molecule Viewer");
    SetTargetFPS(500);  // Set the desired frames-per-second

    

    /*
    ░██████╗░█████╗░███████╗███╗░░██╗███████╗  ░░░░░░░  ░█████╗░████████╗██╗░░██╗███████╗██████╗░
    ██╔════╝██╔══██╗██╔════╝████╗░██║██╔════╝  ░░██╗░░  ██╔══██╗╚══██╔══╝██║░░██║██╔════╝██╔══██╗
    ╚█████╗░██║░░╚═╝█████╗░░██╔██╗██║█████╗░░  ██████╗  ██║░░██║░░░██║░░░███████║█████╗░░██████╔╝
    ░╚═══██╗██║░░██╗██╔══╝░░██║╚████║██╔══╝░░  ╚═██╔═╝  ██║░░██║░░░██║░░░██╔══██║██╔══╝░░██╔══██╗
    ██████╔╝╚█████╔╝███████╗██║░╚███║███████╗  ░░╚═╝░░  ╚█████╔╝░░░██║░░░██║░░██║███████╗██║░░██║
    ╚═════╝░░╚════╝░╚══════╝╚═╝░░╚══╝╚══════╝  ░░░░░░░  ░╚════╝░░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝

    ░██████╗███████╗████████╗██╗░░░██╗██████╗░
    ██╔════╝██╔════╝╚══██╔══╝██║░░░██║██╔══██╗
    ╚█████╗░█████╗░░░░░██║░░░██║░░░██║██████╔╝
    ░╚═══██╗██╔══╝░░░░░██║░░░██║░░░██║██╔═══╝░
    ██████╔╝███████╗░░░██║░░░╚██████╔╝██║░░░░░
    ╚═════╝░╚══════╝░░░╚═╝░░░░╚═════╝░╚═╝░░░░░
    */


    SetExitKey(KEY_NULL);
    Color color = GRAY; //note: remove when necessary or when you feel like it
    float frameDeltaTime = 1; //placeholder value 1, or else it might complain about dividing by 0
    bool CursorEnabled = false;
    Vector2 mouseDelta;
    Vector2 mousePosBeforeDisable;
    DisableCursor();
    SetTargetFPS(75);
   

    bool InMenu = false; //in menu refers to  being in menu, if it is true it means the user is in menu
    //such as graphics, audio, other settings, NOTE: IMGUI WILL HANDLE MOUSE INPUTS TOO, BE CAREFUL, SO DONT USE
    //ImGui::GetIO().WantCaptureMouse WHILE ALSO EXPECTING THE GAME TO CAPTURE MOUSE CORRECTLY, hence the InMenu bool
    //is so important
    /*   
    ▀█▀ █▀█ █▀▄ █▀█ ▀   █▀▀ █░█ ▄▀█ █▄░█ █▀▀ █▀▀   █ █▄░█ █▀▄▀█ █▀▀ █▄░█ █░█   ▀█▀ █▀█   ▀█▀ █▀█ █░█ █▀▀
    ░█░ █▄█ █▄▀ █▄█ ▄   █▄▄ █▀█ █▀█ █░▀█ █▄█ ██▄   █ █░▀█ █░▀░█ ██▄ █░▀█ █▄█   ░█░ █▄█   ░█░ █▀▄ █▄█ ██▄

    ▄▀█ █▀▀ ▀█▀ █▀▀ █▀█   ▀█▀ █▀▀ █▀ ▀█▀ █ █▄░█ █▀▀ ░   █▀▀ █▀█ █▀█   ▀█▀ █░█ █▀▀   █▀▀ █ █▄░█ █ █▀ █░█ █▀▀ █▀▄
    █▀█ █▀░ ░█░ ██▄ █▀▄   ░█░ ██▄ ▄█ ░█░ █ █░▀█ █▄█ █   █▀░ █▄█ █▀▄   ░█░ █▀█ ██▄   █▀░ █ █░▀█ █ ▄█ █▀█ ██▄ █▄▀

    █▀█ █▀█ █▀█ █▀▄ █░█ █▀▀ ▀█▀   █▄█ █▀█ █░█   █▀ █░█ █▀█ █░█ █░░ █▀▄   █▄▄ █▄█   █▀▄ █▀▀ █▀▀ ▄▀█ █░█ █░░ ▀█▀   █▄▄ █▀▀
    █▀▀ █▀▄ █▄█ █▄▀ █▄█ █▄▄ ░█░   ░█░ █▄█ █▄█   ▄█ █▀█ █▄█ █▄█ █▄▄ █▄▀   █▄█ ░█░   █▄▀ ██▄ █▀░ █▀█ █▄█ █▄▄ ░█░   █▄█ ██▄

    █ █▄░█   ▀█▀ █░█ █▀▀   █▀▄▀█ █▀▀ █▄░█ █░█
    █ █░▀█   ░█░ █▀█ ██▄   █░▀░█ ██▄ █░▀█ █▄█
    */

    


    Shader shader;
    std::vector<Mesh> meshes;

    Atom CarbonTestAtom(1542, Vector3{0.0, 3.0, 2.6});

    try
    {
        if(!DoesFileExist("./resources/models/p orbital.obj"))
        {
            throw std::runtime_error("resources/models/p orbital.obj");
        }
        if(!DoesFileExist("./resources/models/d orbital normal.obj"))
        {
            throw std::runtime_error("resources/models/d orbital normal.obj");
        }



        if(!DoesFileExist("./resources/shaders/CellShading.fs"))
        {
            throw std::runtime_error("resources/shaders/CellShading.fs");
        }

        meshes.push_back(LoadModel("./resources/models/p orbital.obj").meshes[0]);
        meshes.push_back(LoadModel("./resources/models/d orbital normal.obj").meshes[0]);


        shader = LoadShader("./resources/shaders/CellShading.vs", "./resources/shaders/CellShading.fs");
        
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "\n\n\n" << e.what() << " not found, Aborting execution \n\n\n";
        EnableCursor();
        ShowCursor();

        UnloadMesh(meshes.at(0));
        UnloadMesh(meshes.at(1));

        CloseWindow();  // Close the window and OpenGL context

        return -1;
    }

    
    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    //setup shader viewPos, idk bruh it was there in the raylib/examples/shaders/shaders_basic_lighting.c
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    //i got this also from the same file above
    int ambientLoc = GetShaderLocation(shader, "ambient");
    float* ambientColour = new float[4]{ 0.4f, 0.4f, 0.4f, 1.0f };
    SetShaderValue(shader, ambientLoc, ambientColour, SHADER_UNIFORM_VEC4);
    delete[] ambientColour;

    Material orbitalMat = LoadMaterialDefault();
    orbitalMat.shader = shader;

    //Creating the main light source                                                                        got this colour from some colour picking website
    Light mainLight = CreateLight(LIGHT_DIRECTIONAL, (Vector3){ 1000, 1000, 1000 }, (Vector3){0, 0, 0}, (Color){246, 234, 172, 255}, shader);






    /*
    ███╗░░░███╗░█████╗░██╗███╗░░██╗  ██╗░░░░░░█████╗░░█████╗░██████╗░
    ████╗░████║██╔══██╗██║████╗░██║  ██║░░░░░██╔══██╗██╔══██╗██╔══██╗
    ██╔████╔██║███████║██║██╔██╗██║  ██║░░░░░██║░░██║██║░░██║██████╔╝
    ██║╚██╔╝██║██╔══██║██║██║╚████║  ██║░░░░░██║░░██║██║░░██║██╔═══╝░
    ██║░╚═╝░██║██║░░██║██║██║░╚███║  ███████╗╚█████╔╝╚█████╔╝██║░░░░░
    ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝  ╚══════╝░╚════╝░░╚════╝░╚═╝░░░░░
    */
    

    while (!WindowShouldClose())
    {
        frameDeltaTime = GetFrameTime();

        float cameraPos[4] = { camera.position.x, camera.position.y, camera.position.z };

        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        

        /*
        ██╗███╗░░██╗██████╗░██╗░░░██╗████████╗  ░█████╗░██╗░░██╗███████╗░█████╗░██╗░░██╗
        ██║████╗░██║██╔══██╗██║░░░██║╚══██╔══╝  ██╔══██╗██║░░██║██╔════╝██╔══██╗██║░██╔╝
        ██║██╔██╗██║██████╔╝██║░░░██║░░░██║░░░  ██║░░╚═╝███████║█████╗░░██║░░╚═╝█████═╝░
        ██║██║╚████║██╔═══╝░██║░░░██║░░░██║░░░  ██║░░██╗██╔══██║██╔══╝░░██║░░██╗██╔═██╗░
        ██║██║░╚███║██║░░░░░╚██████╔╝░░░██║░░░  ╚█████╔╝██║░░██║███████╗╚█████╔╝██║░╚██╗
        ╚═╝╚═╝░░╚══╝╚═╝░░░░░░╚═════╝░░░░╚═╝░░░  ░╚════╝░╚═╝░░╚═╝╚══════╝░╚════╝░╚═╝░░╚═╝
        */

        //bool CursorDisabled = true; //uncomment this later

        mouseDelta = GetMouseDelta();

        /*
        ▀▀█▀▀ █▀▀█ █▀▀▄ █▀▀█ ▄
        ░░█░░ █░░█ █░░█ █░░█ ░
        ░░▀░░ ▀▀▀▀ ▀▀▀░ ▀▀▀▀ ▀
        */
        //create an array to store all the current keys being pressed at the moment, and later
        //make handler code that will do everything that needs to be done such as animations, loading, etc while
        //also taking care of the input

        
            
        if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_ESCAPE))
        {
           goto PROGRAM_END;
        }   //setup a way to forcefully exit program no matter what

        if(!InMenu) //in app controls such as moving camera, moving objects, etc
        {
            /*
            ▀▀█▀▀ █▀▀█ █▀▀▄ █▀▀█ ▄
            ░░█░░ █░░█ █░░█ █░░█ ░
            ░░▀░░ ▀▀▀▀ ▀▀▀░ ▀▀▀▀ ▀
            */
            //write some code to find if the mouse is in the scene view region or in the menu region, and the menu and screen view
            //can be dynamically changed, also the mouse being outside of the window counts as menu, for simplicity sake 
            

            if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            {
                if(CursorEnabled)
                {
                    CursorEnabled = false;
                    mousePosBeforeDisable = GetMousePosition();
                    DisableCursor();
                }


                if(IsKeyDown(KEY_W))
                {
                    CameraMoveForward(&camera, 0.2f, false);
                }
                else if(IsKeyDown(KEY_S))
                {
                    CameraMoveForward(&camera, -0.2f, false);
                }

                if(IsKeyDown(KEY_D))
                {
                    CameraMoveRight(&camera, 0.2f, false);
                }
                else if(IsKeyDown(KEY_A))
                {
                    CameraMoveRight(&camera, -0.2f, false);
                }

                if(IsKeyDown(KEY_E))
                {
                    CameraMoveUp(&camera, 0.2f);
                }
                else if(IsKeyDown(KEY_Q))
                {
                    CameraMoveUp(&camera, -0.2f);
                }
                

                //there is '-' because for some reason it is inverting it idk why
                CameraYaw(&camera, -mouseDelta.x*0.005f, false);
                CameraPitch(&camera, -mouseDelta.y*0.005f, true, false, false); //DONT SET ROTATE UP PARAMETER TO TRUE
                //wasted like 1 hour of my time figuring it out
            }
            else
            {
                if(!CursorEnabled)
                {
                    CursorEnabled = true;
                    EnableCursor();
                    SetMousePosition(mousePosBeforeDisable.x, mousePosBeforeDisable.y);
                }
            }
        }
        else if(InMenu)
        {
            /*
            ▀▀█▀▀ █▀▀█ █▀▀▄ █▀▀█ ▄
            ░░█░░ █░░█ █░░█ █░░█ ░
            ░░▀░░ ▀▀▀▀ ▀▀▀░ ▀▀▀▀ ▀
            */
            //write some code to find if the mouse is in the scene view region or in the menu region, and the menu and screen view
            //can be dynamically changed, also the mouse being outside of the window counts as menu, for simplicity sake 
        }

        









        /*
        ██████╗░██████╗░░█████╗░░██╗░░░░░░░██╗██╗███╗░░██╗░██████╗░
        ██╔══██╗██╔══██╗██╔══██╗░██║░░██╗░░██║██║████╗░██║██╔════╝░
        ██║░░██║██████╔╝███████║░╚██╗████╗██╔╝██║██╔██╗██║██║░░██╗░
        ██║░░██║██╔══██╗██╔══██║░░████╔═████║░██║██║╚████║██║░░╚██╗
        ██████╔╝██║░░██║██║░░██║░░╚██╔╝░╚██╔╝░██║██║░╚███║╚██████╔╝
        ╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝░╚═════╝░
        */

        Matrix transform = MatrixTranslate(CarbonTestAtom.Position.x, CarbonTestAtom.Position.y, CarbonTestAtom.Position.z);


        BeginDrawing();

        {

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

                DrawMesh(meshes.at(0), orbitalMat, transform);
                DrawGrid(100, 1.0f);

            EndMode3D();



            /*
            ░██████╗░██╗░░░██╗██╗  ██████╗░███████╗███╗░░██╗██████╗░███████╗██████╗░██╗███╗░░██╗░██████╗░
            ██╔════╝░██║░░░██║██║  ██╔══██╗██╔════╝████╗░██║██╔══██╗██╔════╝██╔══██╗██║████╗░██║██╔════╝░
            ██║░░██╗░██║░░░██║██║  ██████╔╝█████╗░░██╔██╗██║██║░░██║█████╗░░██████╔╝██║██╔██╗██║██║░░██╗░
            ██║░░╚██╗██║░░░██║██║  ██╔══██╗██╔══╝░░██║╚████║██║░░██║██╔══╝░░██╔══██╗██║██║╚████║██║░░╚██╗
            ╚██████╔╝╚██████╔╝██║  ██║░░██║███████╗██║░╚███║██████╔╝███████╗██║░░██║██║██║░╚███║╚██████╔╝
            ░╚═════╝░░╚═════╝░╚═╝  ╚═╝░░╚═╝╚══════╝╚═╝░░╚══╝╚═════╝░╚══════╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░╚═════╝░
            */

            DrawText((std::to_string(GetFPS())).c_str(), 10, 10, 20, DARKPURPLE);
        }

        EndDrawing();
    }

    goto PROGRAM_END;   //i have a feeling that if you close the window by clicking the x
    //it skips the PROGRAM_END Label, so this is just to be sure

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

    UnloadMesh(meshes.at(0));
    UnloadMesh(meshes.at(1));

    CloseWindow();  // Close the window and OpenGL context

    std::cout << "CleanUp Successful\n";

    return 0;
}