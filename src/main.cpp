//Game Engine Development - Assignment 1
//Group Members: Brandon Norris & Devin Coles

#include <include/raylib.h>
#include <imgui/imgui.h>
#include <imgui/rlImGui.h>
#include <imgui/imgui_stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

#include <vector>


//Shape Parent Class
class Shape {

    public:
        std::string Name;
        int X = 0;
        int Y = 0;
        int SX = 0;
        int SY = 0;
        int Red = 0;
        int Green = 0;
        int Blue = 0;

        int Length = 0;
        int Width = 0;

        int Radius = 0;

};

//Circle Child Class
class Circle: public Shape {

    int Radius = 0;

    Circle(std::string Name, int X, int Y, int SX, int SY, int Red, int Green, int Blue, int Radius) {
        this->Name = "";
        this->X = X;
        this->Y = Y;
        this->SX = SX;
        this->SY = SY;
        this->Red = Red;
        this->Green = Green;
        this->Blue = Blue;
        this->Radius = Radius;
        
    }
};

//Rect Child Class
class Rect : public Shape {

    int Length = 0;
    int Width = 0;

    Rect(std::string Name, int X, int Y, int SX, int SY, int Red, int Green, int Blue, int Length, int Width) {
        this->Name = "";
        this->X = X;
        this->Y = Y;
        this->SX = SX;
        this->SY = SY;
        this->Red = Red;
        this->Green = Green;
        this->Blue = Blue;
        this->Length = Length;
        this->Width = Width;

    }
};


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    //original dimensions: 1280 x 800
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "Assignment 1 Starter Code");
    
    //initialize the raylib ImGui backend
    rlImGuiSetup(true);
    //increase ImGui item size to 2x
    ImGui::GetStyle().ScaleAllSizes(2);

    // Set raylib to target 60 frames-per-second (this does not mean it will actually RUN at 60 fps)
    SetTargetFPS(60);               

    // General variables
    //--------------------------------------------------------------------------------------

    //shape properties to draw on the screen (circle for this example)
    //units of size and speed are in pixels
    float obj1Radius=50;
    float obj1SpeedX=1.0f;
    float obj1SpeedY=0.5f;
    bool drawObj1=true;
    float obj1X=50.0f;
    float obj1Y=50.0f;
    float color[3] = {0.0f,0.0,1.0f}; //color is from 0-1

    //booleans to keep track of direction
    bool obj1Right = true;
    bool obj1Down = true;

    //std::vector<Shape> shapes;
    bool posY = true;
    bool posX = true;

    //Let's draw some text to the screen too
    bool drawText=true;
    std::string strText= "Some Text";
    std::string newText= strText;

    //load a font (Raylib gives warning if font can't be found, then uses default as fallback)
    Font font = LoadFont("assets/Orbitron.ttf");

    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------


        //move Object1 and detecting if it has hit the side of the screen
        if (obj1Right) 
        {
            obj1X += obj1SpeedX;
            if (obj1X + obj1Radius == screenWidth)
                obj1Right = false;
        }
        else 
        {
            obj1X -= obj1SpeedX;
            if (obj1X - obj1Radius == 0)
                obj1Right = true;
        }

        if (obj1Down) 
        {
            obj1Y += obj1SpeedY;
            if (obj1Y + obj1Radius == screenHeight)
                obj1Down = false;
        }
        else
        {
            obj1Y -= obj1SpeedY;
            if (obj1Y - obj1Radius == 0)
                obj1Down = true;
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            //********** Raylib Drawing Content **********

            //draw the cricle (center x, center y, radius, color(r,g,b,a))
            if(drawObj1){
                DrawCircle((int)obj1X, (int)obj1Y, obj1Radius, ColorFromNormalized({ color[0],color[1],color[2],1.0f }));
            }
            
            //draw the text
            if(drawText){
                //get the size (x and y) of the text object
                //(font,c string, font size, font spaceing)
                Vector2 textSize= MeasureTextEx(font, strText.c_str(), 18, 1);

                //draw the text (using the text size to help draw it in the corner
                //(font,c string, vector2, font size, font spaceing, color)
                DrawTextEx(font, strText.c_str(), { 0.0f, screenHeight - textSize.y }, 18, 1, WHITE);
            }

            //********** ImGUI Content *********
            
            //Draw imgui stuff last so it is over the top of everything else
            rlImGuiBegin();

                //sets the next window to be at this position
                //also uses the imgui.ini that gets created at first run
                ImGui::SetNextWindowSize(ImVec2(350, 250));
                //creates a new window
                ImGui::Begin("My Window",NULL,ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse);
                    ImGui::Text("The Window Text!");
                    //A listbox to select which object is being modified
                    const char* items[] = { "Object1","Object2","Text"};
                    static int item_current = 0;
                    ImGui::Combo("Object\nSelect", &item_current, items, IM_ARRAYSIZE(items),1);

                    if (item_current == 0) //when Object1 is selected in the Object Select ComboBox
                    {
                        //checkboxes, they directly modify the value (which is why we send a reference)
                        ImGui::Checkbox("Draw Cricle", &drawObj1);

                        //slider, again directly modifies the value and limites between 0 and 300 for this example
                        ImGui::SliderFloat("Radius", &obj1Radius, 0.0f, 300.0f);

                        //color picker button, directly modifies the color (3 element float array)
                        ImGui::ColorEdit3("Object1 Color", color);

                        //Another button
                        if (ImGui::Button("Reset Object1")) {
                            obj1X = 50.0;
                            obj1Y = 50.0;
                            obj1Radius = 50;
                        }
                    }

                    if (item_current == 1) //when Object2 is selected in the Object Select ComboBox
                    {
                        //needs implementation when second object is created
                    }

                    if (item_current == 2) //when Text is selected in the Object Select ComboBox
                    {
                        //checkboxes, they directly modify the value (which is why we send a reference)
                        ImGui::Checkbox("Draw Text", &drawText);

                        //text input field, directly modifies the string
                        ImGui::InputText("Text", &newText);

                        //buttons, returns true if clicked on this frame
                        if (ImGui::Button("Set Text")) {
                            strText = newText;
                        }
                    }

                    //The next item will be on the same line as the previous one
                    //ImGui::SameLine();

                    
                //ends this window
                ImGui::End();

                //show ImGui Demo Content if you want to see it
                //bool open = true;
                //ImGui::ShowDemoWindow(&open);

            // end ImGui Content
            rlImGuiEnd();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Clean Up
    //--------------------------------------------------------------------------------------
    rlImGuiShutdown();    // Shuts down the raylib ImGui backend
    UnloadFont(font);     // Remove font from memory
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}