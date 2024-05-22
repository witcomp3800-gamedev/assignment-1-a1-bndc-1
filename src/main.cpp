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

    float objRadius;
    float objSpeedX;
    float objSpeedY;
    bool drawObj;
    bool drawObjText;
    float objX;
    float objY;
    float objColor[3]; //color is from 0-1
    std::string objName;
    std::string objNewText;

    //object direction booleans
    bool objRight = true;
    bool objDown = true;

    Circle(float objRadius, float objSpeedX, float objSpeedY, bool drawObj, bool drawObjText, float objX, float objY, float objColor[3], std::string objName) {
        this->objRadius = objRadius;
        this->objSpeedX = objSpeedX;
        this->objSpeedY = objSpeedY;
        this->drawObj = drawObj;
        this->drawObjText = drawObjText;
        this->objX = objX;
        this->objY = objY;
        this->objColor[0] = objColor[0];
        this->objColor[1] = objColor[1];
        this->objColor[2] = objColor[2];
        this->objName = objName;
        this->objNewText = objName;
    }

    void move(int screenWidth, int screenHeight) {
        if (objRight)
        {
            objX += objSpeedX;
            if (objX + objRadius >= screenWidth)
                objRight = false;
        }
        else
        {
            objX -= objSpeedX;
            if (objX - objRadius <= 0)
                objRight = true;
        }

        if (objDown)
        {
            objY += objSpeedY;
            if (objY + objRadius >= screenHeight)
                objDown = false;
        }
        else
        {
            objY -= objSpeedY;
            if (objY - objRadius <= 0)
                objDown = true;
        }
    }

};

//Rect Child Class
class Rect : public Shape {


private:
    float objLength;
    float objWidth;
    float objSpeedX;
    float objSpeedY;
    bool drawObj;
    bool drawObjText;
    float objX;
    float objY;
    float objColor[3]; //color is from 0-1
    std::string objName;
    std::string objNewText;

    //object direction booleans
    bool objRight = false;
    bool objDown = true;

public:
    Rect(float objLength, float objWidth, float objSpeedX, float objSpeedY, bool drawObj, bool drawObjText, float objX, float objY, float objColor[3], std::string objName) {
        this->objLength = objLength;
        this->objWidth = objWidth;
        this->objSpeedX = objSpeedX;
        this->objSpeedY = objSpeedY;
        this->drawObj = drawObj;
        this->drawObjText = drawObjText;
        this->objX = objX;
        this->objY = objY;
        this->objColor[0] = objColor[0];
        this->objColor[1] = objColor[1];
        this->objColor[2] = objColor[2];
        this->objName = objName;
        this->objNewText = objName;
    }

    void move(int screenWidth, int screenHeight) {
        if (objRight)
        {
            objX += objSpeedX;
            if (objX + objWidth >= screenWidth)
                objRight = false;
        }
        else
        {
            objX -= objSpeedX;
            if (objX - objWidth <= 0)
                objRight = true;
        }

        if (objDown)
        {
            objY += objSpeedY;
            if (objY + objLength >= screenHeight)
                objDown = false;
        }
        else
        {
            objY -= objSpeedY;
            if (objY - objLength <= 0)
                objDown = true;
        }
    }

};

//object move function
void Move_Shape(Shape obj) {

}


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
    bool drawObj1Text = true;
    float obj1X=50.0f;
    float obj1Y=50.0f;
    float obj1Color[3] = {0.0f,0.0,1.0f}; //color is from 0-1
    std::string obj1Name = "Object1";
    std::string obj1NewText = obj1Name;
    //booleans to keep track of direction
    bool obj1Right = true;
    bool obj1Down = true;


    //shape properties to draw on the screen (circle for this example)
    //units of size and speed are in pixels
    float obj2Length = 30;
    float obj2Width = 60;
    float obj2SpeedX = 1.0f;
    float obj2SpeedY = 0.5f;
    bool drawObj2 = true;
    bool drawObj2Text = true;
    float obj2X = 1000.0f;
    float obj2Y = 50.0f;
    float obj2Color[3] = { 1.0f,0.5f,0.0f }; //color is from 0-1
    std::string obj2Name = "Object2";
    std::string obj2NewText = obj1Name;
    //booleans to keep track of direction
    bool obj2Right = false;
    bool obj2Down = true;


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
            if (obj1X + obj1Radius >= screenWidth)
                obj1Right = false;
        }
        else 
        {
            obj1X -= obj1SpeedX;
            if (obj1X - obj1Radius <= 0)
                obj1Right = true;
        }

        if (obj1Down) 
        {
            obj1Y += obj1SpeedY;
            if (obj1Y + obj1Radius >= screenHeight)
                obj1Down = false;
        }
        else
        {
            obj1Y -= obj1SpeedY;
            if (obj1Y - obj1Radius <= 0)
                obj1Down = true;
        }

        //move Object2 and detecting if it has hit the side of the screen
        if (obj2Right)
        {
            obj2X += obj2SpeedX;
            if (obj2X + obj2Width >= screenWidth)
                obj2Right = false;
        }
        else
        {
            obj2X -= obj2SpeedX;
            if (obj2X - obj2Width <= 0)
                obj2Right = true;
        }

        if (obj2Down)
        {
            obj2Y += obj2SpeedY;
            if (obj2Y + obj2Length >= screenHeight)
                obj2Down = false;
        }
        else
        {
            obj2Y -= obj2SpeedY;
            if (obj2Y - obj2Length <= 0)
                obj2Down = true;
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            //********** Raylib Drawing Content **********

            //draw the cicle (center x, center y, radius, color(r,g,b,a))
            if(drawObj1){
                DrawCircle((int)obj1X, (int)obj1Y, obj1Radius, ColorFromNormalized({ obj1Color[0],obj1Color[1],obj1Color[2],1.0f }));

                if (drawObj1Text) 
                {
                    //get the size (x and y) of the text object
                    //(font,c string, font size, font spaceing)
                    Vector2 textSize = MeasureTextEx(font, strText.c_str(), 18, 1);

                    //draw the text (using the text size to help draw it in the corner
                    //(font,c string, vector2, font size, font spaceing, color)
                    DrawTextEx(font, obj1Name.c_str(), { obj1X - (textSize.x / 3), obj1Y - (textSize.y / 2) }, 18, 1, WHITE);
                }
            }

            //draw the rectangle (center x, center y, width, height, color(r,g,b,a))
            if (drawObj2) {
                DrawRectangle((int)obj2X, (int)obj2Y, obj2Width, obj2Length, ColorFromNormalized({ obj2Color[0],obj2Color[1],obj2Color[2],1.0f }));

                if(drawObj2Text)
                {
                    //get the size (x and y) of the text object
                    //(font,c string, font size, font spaceing)
                    Vector2 textSize = MeasureTextEx(font, strText.c_str(), 18, 1);

                    //draw the text (using the text size to help draw it in the corner
                    //(font,c string, vector2, font size, font spaceing, color)
                    DrawTextEx(font, obj2Name.c_str(), { obj2X - (textSize.x / 8), obj2Y + (textSize.y / 2) }, 18, 1, WHITE);
                }
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
                        ImGui::Checkbox("Draw Object1", &drawObj1);
                        ImGui::SameLine();
                        ImGui::Checkbox("Draw Object1 Text", &drawObj1Text);

                        //slider, again directly modifies the value and limites between 0 and 300 for this example
                        ImGui::SliderFloat("Radius", &obj1Radius, 0.0f, 300.0f);

                        ImGui::SliderFloat("SpeedX", &obj1SpeedX, 0.0f, 150.0f);
                        ImGui::SliderFloat("SpeedY", &obj1SpeedY, 0.0f, 75.0f);

                        //color picker button, directly modifies the color (3 element float array)
                        ImGui::ColorEdit3("Object1 Color", obj1Color);

                        //text input field, directly modifies the string
                        ImGui::InputText("Text", &obj1NewText);

                        //Buttons
                        if (ImGui::Button("Reset Object1")) {
                            obj1X = 50.0;
                            obj1Y = 50.0;
                            obj1Radius = 50;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Set Text")) {
                            obj1Name = obj1NewText;
                        }
                    }

                    if (item_current == 1) //when Object2 is selected in the Object Select ComboBox
                    {
                        ImGui::Checkbox("Draw Object2", &drawObj2);
                        ImGui::SameLine();
                        ImGui::Checkbox("Draw Object2 Text", &drawObj2Text);

                        //slider, again directly modifies the value and limites between 0 and 300 for this example
                        ImGui::SliderFloat("Length", &obj2Length, 0.0f, 300.0f);
                        ImGui::SliderFloat("Width", &obj2Width, 0.0f, 300.0f);

                        ImGui::SliderFloat("SpeedX", &obj2SpeedX, 0.0f, 150.0f);
                        ImGui::SliderFloat("SpeedY", &obj2SpeedY, 0.0f, 75.0f);

                        //color picker button, directly modifies the color (3 element float array)
                        ImGui::ColorEdit3("Object1 Color", obj2Color);

                        //text input field, directly modifies the string
                        ImGui::InputText("Text", &obj2NewText);

                        //Buttons
                        if (ImGui::Button("Reset Object1")) {
                            obj2X = 1000.0;
                            obj2Y = 50.0;
                            obj2Length = 30;
                            obj2Width = 60;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Set Text")) {
                            obj2Name = obj2NewText;
                        }
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