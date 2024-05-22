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

//original dimensions: 1280 x 800
const int windowWidth = 1000;
const int windowHeight = 500;


//Shape Parent Class
class Shape {

    public:
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

        //virtual function declarations, to apply logic from appropriate subclass
        virtual void move() {};
        virtual void draw(Font font) {};

};

//Circle Child Class
class Circle: public Shape {

    public:

        float objRadius;

        Circle(float objRadius, float objSpeedX, float objSpeedY, float objX, float objY, float objR, float objG, float objB, std::string objName) {
        
            this->objRadius = objRadius;
            this->objSpeedX = objSpeedX;
            this->objSpeedY = objSpeedY;
            this->drawObj = true;
            this->drawObjText = true;
            this->objX = objX;
            this->objY = objY;
            this->objColor[0] = objR;
            this->objColor[1] = objG;
            this->objColor[2] = objB;
            this->objName = objName;
            this->objNewText = objName;
        }

        void move() {
            if (objRight)
            {
                objX += objSpeedX;
                if (objX + objRadius >= windowWidth)
                    this->objRight = false;
            }
            else
            {
                objX -= objSpeedX;
                if (objX - objRadius <= 0)
                    this->objRight = true;
            }

            if (objDown)
            {
                objY += objSpeedY;
                if (objY + objRadius >= windowHeight)
                    this->objDown = false;
            }
            else
            {
                objY -= objSpeedY;
                if (objY - objRadius <= 0)
                    this->objDown = true;
            }
        }

        void draw(Font font) {
            DrawCircle((int)objX, (int)objY, objRadius, ColorFromNormalized({ objColor[0],objColor[1],objColor[2],1.0f }));
            if (drawObjText)
            {
                //get the size (x and y) of the text object
                //(font,c string, font size, font spaceing)
                Vector2 textSize = MeasureTextEx(font, objName.c_str(), 18, 1);

                //draw the text (using the text size to help draw it in the corner
                //(font,c string, vector2, font size, font spaceing, color)
                DrawTextEx(font, objName.c_str(), { objX - (textSize.x / 2), objY - (textSize.y / 2) }, 18, 1, WHITE);
            }
        }
};

//Rect Child Class
class Rect : public Shape {

    public:

        float objLength;
        float objWidth;

        Rect(float objLength, float objWidth, float objSpeedX, float objSpeedY, float objX, float objY, float objR, float objG, float objB, std::string objName) {
            this->objLength = objLength;
            this->objWidth = objWidth;
            this->objSpeedX = objSpeedX;
            this->objSpeedY = objSpeedY;
            this->drawObj = true;
            this->drawObjText = true;
            this->objX = objX;
            this->objY = objY;
            this->objColor[0] = objR;
            this->objColor[1] = objG;
            this->objColor[2] = objB;
            this->objName = objName;
            this->objNewText = objName;
        }

        void move() {
            if (objRight)
            {
                objX += objSpeedX;
                if (objX + objWidth >= windowWidth)
                    objRight = false;
            }
            else
            {
                objX -= objSpeedX;
                if (objX <= 0)
                    objRight = true;
            }

            if (objDown)
            {
                objY += objSpeedY;
                if (objY + objLength >= windowHeight)
                    objDown = false;
            }
            else
            {
                objY -= objSpeedY;
                if (objY <= 0)
                    objDown = true;
            }
        }

        void draw(Font font) {
            if (drawObj) {
                DrawRectangle((int)objX, (int)objY, objWidth, objLength, ColorFromNormalized({ objColor[0],objColor[1],objColor[2],1.0f }));

                if (drawObjText)
                {
                    //get the size (x and y) of the text object
                    //(font,c string, font size, font spaceing)
                    Vector2 textSize = MeasureTextEx(font, objName.c_str(), 18, 1);

                    //draw the text (using the text size to help draw it in the corner
                    //(font,c string, vector2, font size, font spaceing, color)
                    DrawTextEx(font, objName.c_str(), { (objX + objWidth/2) - (textSize.x / 2), (objY + objLength/2) - (textSize.y / 2) }, 18, 1, WHITE);
                }
            }
        }

};

//object update function
void updateShape(Shape& obj, Font font) {
    if (obj.drawObj) {
        obj.draw(font);
    }
    obj.move();
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = windowWidth;
    const int screenHeight = windowHeight;

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

    //Object Parameters: Circle(float Radius, float SpeedX, float SpeedY, float X, float Y, float Red, float Green, float Blue, string Name)
    Circle obj1 = Circle(50.0f, 1.0f, 0.5f, 50.0f, 50.0f, 0.0f, 0.0f, 1.0f, "Object1");


    //shape properties to draw on the screen (circle for this example)
    //units of size and speed are in pixels
    
    //Object Parameters: Rect(float Length, float Width, float SpeedX, float SpeedY, float X, float Y, float Red, float Green, float Blue, string Name)
    Rect obj2 = Rect(30, 60, 1.0f, 0.5f, 900.0f, 50.0f, 1.0f, 0.5f, 0.0f, "Object2");


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

        /*
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
        */

        /*
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
            if (obj2X <= 0)
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
            if (obj2Y <= 0)
                obj2Down = true;
        }
        */


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            //********** Raylib Drawing Content **********

            //drawing from object rather than individual vars
            //draw function for circle moved into circle class
            updateShape(obj1, font);

            //drawing from object rather than individual vars
            //draw function for rect moved into rect class
            updateShape(obj2, font);



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
                        ImGui::Checkbox("Draw Object1", &obj1.drawObj);
                        ImGui::SameLine();
                        ImGui::Checkbox("Draw Object1 Text", &obj1.drawObjText);

                        //slider, again directly modifies the value and limites between 0 and 300 for this example
                        ImGui::SliderFloat("Radius", &obj1.objRadius, 0.0f, 300.0f);

                        ImGui::SliderFloat("SpeedX", &obj1.objSpeedX, 0.0f, 150.0f);
                        ImGui::SliderFloat("SpeedY", &obj1.objSpeedY, 0.0f, 75.0f);

                        //color picker button, directly modifies the color (3 element float array)
                        ImGui::ColorEdit3("Object1 Color", obj1.objColor);

                        //text input field, directly modifies the string
                        ImGui::InputText("Text", &obj1.objNewText);

                        //Buttons
                        if (ImGui::Button("Reset Object1")) {
                            obj1.objX = 50.0;
                            obj1.objY = 50.0;
                            obj1.objRadius = 50;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Set Text")) {
                            obj1.objName = obj1.objNewText;
                        }
                    }

                    if (item_current == 1) //when Object2 is selected in the Object Select ComboBox
                    {
                        ImGui::Checkbox("Draw Object2", &obj2.drawObj);
                        ImGui::SameLine();
                        ImGui::Checkbox("Draw Object2 Text", &obj2.drawObjText);

                        //slider, again directly modifies the value and limites between 0 and 300 for this example
                        ImGui::SliderFloat("Length", &obj2.objLength, 0.0f, 300.0f);
                        ImGui::SliderFloat("Width", &obj2.objWidth, 0.0f, 300.0f);

                        ImGui::SliderFloat("SpeedX", &obj2.objSpeedX, 0.0f, 150.0f);
                        ImGui::SliderFloat("SpeedY", &obj2.objSpeedY, 0.0f, 75.0f);

                        //color picker button, directly modifies the color (3 element float array)
                        ImGui::ColorEdit3("Object1 Color", obj2.objColor);

                        //text input field, directly modifies the string
                        ImGui::InputText("Text", &obj2.objNewText);

                        //Buttons
                        if (ImGui::Button("Reset Object1")) {
                            obj2.objX = 1000.0;
                            obj2.objY = 50.0;
                            obj2.objLength = 30;
                            obj2.objWidth = 60;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Set Text")) {
                            obj2.objName = obj2.objNewText;
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