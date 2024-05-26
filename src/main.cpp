//Game Engine Development - Assignment 1
//Group Members: Brandon Norris & Devin Coles

#include <include/raylib.h>
#include <imgui/imgui.h>
#include <imgui/rlImGui.h>
#include <imgui/imgui_stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


//Shape Parent Class
class Shape {

    public:
        float objScale;
        float objVelocity[2]; //holds speed X and speed Y
        bool drawObj;
        bool drawObjText;
        bool simulateObj;
        bool active;
        float objX;
        float objY;
        float objColor[3]; //color is from 0-1
        std::string objName;
        std::string objNewText;

        //virtual destructor
        virtual ~Shape() {};

        //virtual function declarations, to apply logic from appropriate subclass
        virtual void move(int windowWidth, int windowHeight)=0;
        virtual void draw(Font font)=0;
        virtual void addImgui() = 0;

};

//Circle Child Class
class Circle: public Shape {

    public:

        float objRadius;

        Circle(float objRadius, float objSpeedX, float objSpeedY, float objX, float objY, float objR, float objG, float objB, std::string objName) {
        
            this->objRadius = objRadius;
            this->objScale = 1;
            this->objVelocity[0] = objSpeedX;
            this->objVelocity[1] = objSpeedY;
            this->drawObj = true;
            this->drawObjText = true;
            this->simulateObj = true;
            this->active = true;
            this->objX = objX;
            this->objY = objY;
            this->objColor[0] = objR;
            this->objColor[1] = objG;
            this->objColor[2] = objB;
            this->objName = objName;
            this->objNewText = objName;
        }

        void move(int windowWidth, int windowHeight) {
            objX += objVelocity[0];
            objY += objVelocity[1];
            if (objVelocity[0] > 0 && objX + objRadius*objScale >= windowWidth || objVelocity[0] < 0 && objX - objRadius*objScale <= 0)
                objVelocity[0] = 0 - objVelocity[0];
            if (objVelocity[1] > 0 && objY + objRadius*objScale >= windowHeight || objVelocity[1] < 0 && objY - objRadius*objScale <= 0)
                objVelocity[1] = 0 - objVelocity[1];
        }

        void draw(Font font) {
            DrawCircle((int)objX, (int)objY, objRadius*objScale, ColorFromNormalized({ objColor[0],objColor[1],objColor[2],1.0f }));
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

        void addImgui() {
            ImGui::Checkbox("Active", &active);

            //Slider for scale, scale is multiplied with default object bounds to increase draw size and collision detection
            ImGui::SliderFloat("Scale", &objScale, 0.1f, 5.0f);

            //Creates two drag boxes on the same line. The one on the left is for X speed and the one on the right is for Y speed. Also creates a title "Velocity" to the right of them
            ImGui::DragFloat2("Velocity", objVelocity, -1.0f, 1.0f);

            //color picker button, directly modifies the color (3 element float array)
            ImGui::ColorEdit3("Color", objColor);

            //text input field, directly modifies the string
            ImGui::InputText("Name", &objNewText);
            objName = objNewText;
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
            this->objScale = 1;
            this->objVelocity[0] = objSpeedX;
            this->objVelocity[1] = objSpeedY;
            this->drawObj = true;
            this->drawObjText = true;
            this->simulateObj = true;
            this->active = true;
            this->objX = objX;
            this->objY = objY;
            this->objColor[0] = objR;
            this->objColor[1] = objG;
            this->objColor[2] = objB;
            this->objName = objName;
            this->objNewText = objName;
        }

        void move(int windowWidth, int windowHeight) {
            objX += objVelocity[0];
            objY += objVelocity[1];
            if (objVelocity[0] > 0 && objX + objWidth*objScale >= windowWidth || objVelocity[0] < 0 && objX <= 0)
                objVelocity[0] = 0 - objVelocity[0];
            if (objVelocity[1] > 0 && objY + objLength*objScale >= windowHeight || objVelocity[1] < 0 && objY <= 0)
                objVelocity[1] = 0 - objVelocity[1];
        }

        void draw(Font font) {
            if (drawObj) {
                DrawRectangle((int)objX, (int)objY, objWidth*objScale, objLength*objScale, ColorFromNormalized({ objColor[0],objColor[1],objColor[2],1.0f }));

                if (drawObjText)
                {
                    //get the size (x and y) of the text object
                    //(font,c string, font size, font spaceing)
                    Vector2 textSize = MeasureTextEx(font, objName.c_str(), 18, 1);

                    //draw the text (using the text size to help draw it in the corner
                    //(font,c string, vector2, font size, font spaceing, color)
                    DrawTextEx(font, objName.c_str(), { (objX + objWidth*objScale/2) - (textSize.x / 2), (objY + objLength*objScale/2) - (textSize.y / 2) }, 18, 1, WHITE);
                }
            }
        }

        void addImgui() {
            //Checkbox that modifies the active boolean, when false, the object is not drawn and does not move
            ImGui::Checkbox("Active", &active);

            //Slider for scale, scale is multiplied with default object bounds to increase draw size and collision detection
            ImGui::SliderFloat("Scale", &objScale, 0.1f, 5.0f);

            //Creates two drag boxes on the same line with the title Velocity to the right of them
            ImGui::DragFloat2("Velocity", objVelocity, -1.0f, 1.0f);

            //color picker button, directly modifies the color (3 element float array)
            ImGui::ColorEdit3("Color", objColor);

            //text input field, directly modifies the string
            ImGui::InputText("Name", &objNewText);
            objName = objNewText;
        }
};

//object update function
void updateShape(Shape& obj, Font font, int windowWidth, int windowHeight) {
    if (obj.active) {
        if (obj.drawObj) {
            obj.draw(font);
        }
        if (obj.simulateObj) {
            obj.move(windowWidth, windowHeight);
        }
    }
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    std::vector<Circle> circles{};
    std::vector<Rect> rects{};

    int screenWidth = 300;
    int screenHeight = 300;

    //file read testing
    std::ifstream input;
    input.open("assets/input.txt");
    std::string line;
    

        //reading from file
        while(getline(input, line)) {

            std::istringstream iss(line);
            std::string temp;

            iss >> temp;

            if (temp == "Window") {
                std::vector<std::string> tempv;
                while (getline(iss, temp, ' ')) {
                    tempv.push_back(temp);
                }

                for (int i = 0; i < tempv.size(); i++) {
                    std::cout << tempv[i] << " ";
                }
                std::cout << std::endl;

                screenWidth = std::stoi(tempv[2]);
                screenHeight = std::stoi(tempv[3]);
            }
            else if (temp == "Font") {

            }
            else if (temp == "Circle") {
                //creates a temporary vector of all attributes listed in a line of the input file & creates a circle
                std::vector<std::string> tempv;
                while (getline(iss, temp, ' ')) {
                    tempv.push_back(temp);
                }
                
                for (int i = 0; i < tempv.size(); i++) {
                    std::cout << tempv[i] << " ";
                }
                std::cout << std::endl;

                //parsing vector elements to individual temp variables for circle creation
                std::string tName = tempv[1];
                float tRadius = std::stof(tempv[9]);
                float tSpeedX = std::stof(tempv[4]);
                float tSpeedY = std::stof(tempv[5]);
                float tX = std::stof(tempv[2]);
                float tY = std::stof(tempv[3]);
                float tRed = std::stof(tempv[6]);
                float tGreen = std::stof(tempv[7]);
                float tBlue = std::stof(tempv[8]);
                
                //Object Parameters: Circle(float Radius, float SpeedX, float SpeedY, float X, float Y, float Red, float Green, float Blue, string Name)   
                circles.push_back(Circle(tRadius, tSpeedX, tSpeedY, tX, tY, tRed, tGreen, tBlue, tName));
                
            }
            else if (temp == "Rectangle") {
                std::vector<std::string> tempv;
                while (getline(iss, temp, ' ')) {
                    tempv.push_back(temp);
                }

                for (int i = 0; i < tempv.size(); i++) {
                    std::cout << tempv[i] << " ";
                }
                std::cout << std::endl;

                std::string tName = tempv[1];
                float tLength = std::stof(tempv[9]);
                float tWidth = std::stof(tempv[10]);
                float tSpeedX = std::stof(tempv[4]);
                float tSpeedY = std::stof(tempv[5]);
                float tX = std::stof(tempv[2]);
                float tY = std::stof(tempv[3]);
                float tRed = std::stof(tempv[6]);
                float tGreen = std::stof(tempv[7]);
                float tBlue = std::stof(tempv[8]);

                //Object Parameters: Rect(float Length, float Width, float SpeedX, float SpeedY, float X, float Y, float Red, float Green, float Blue, string Name)
                rects.push_back(Rect(tLength, tWidth, tSpeedX, tSpeedY, tX, tY, tRed, tGreen, tBlue, tName));
            }
        }
        
        input.close();

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "Assignment1 BNDC");

    //initialize the raylib ImGui backend
    rlImGuiSetup(true);
    //increase ImGui item size to 2x
    ImGui::GetStyle().ScaleAllSizes(2);

    // Set raylib to target 60 frames-per-second (this does not mean it will actually RUN at 60 fps)
    SetTargetFPS(60);

    // General variables
    //--------------------------------------------------------------------------------------
    //vector for shape storage
    //std::vector<Shape*> shapes;

    bool drawShapes = true;
    bool drawShapeText = true;
    bool simulate = true;

    bool posY = true;
    bool posX = true;

    //Let's draw some text to the screen too
    bool drawText = false;
    std::string strText = "Some Text";
    std::string newText = strText;

    //load a font (Raylib gives warning if font can't be found, then uses default as fallback)
    Font font = LoadFont("assets/Orbitron.ttf");

    

    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        //********** Raylib Drawing Content **********


        //circle / rect drawing / movement; both done through updateShape function


        //iterator for drawing shapes from vector; currently not working

        for (int i = 0; i < rects.size(); i++) {
            rects[i].drawObj = drawShapes;
            rects[i].drawObjText = drawShapeText;
            rects[i].simulateObj = simulate;
            updateShape(rects[i], font, screenWidth, screenHeight);
        }

        for (int i = 0; i < circles.size(); i++) {
            circles[i].drawObj = drawShapes;
            circles[i].drawObjText = drawShapeText;
            circles[i].simulateObj = simulate;
            updateShape(circles[i], font, screenWidth, screenHeight);
        }
        

        //updateShape(obj1, font);
        //updateShape(obj2, font);

        //draw the text
        if (drawText) {
            //get the size (x and y) of the text object
            //(font,c string, font size, font spaceing)
            Vector2 textSize = MeasureTextEx(font, strText.c_str(), 18, 1);

            //draw the text (using the text size to help draw it in the corner
            //(font,c string, vector2, font size, font spaceing, color)
            DrawTextEx(font, strText.c_str(), { 0.0f, screenHeight - textSize.y }, 18, 1, WHITE);
        }

        //********** ImGUI Content *********

        //Draw imgui stuff last so it is over the top of everything else
        rlImGuiBegin();

        //sets the next window to be at this position
        //also uses the imgui.ini that gets created at first run
        ImGui::SetNextWindowSize(ImVec2(350, 350));
        //creates a new window
        ImGui::Begin("Assignment 1 Controls", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SeparatorText("All Shape Controls");

        ImGui::Checkbox("Draw Shapes", &drawShapes);
        ImGui::SameLine();
        ImGui::Checkbox("Draw Text", &drawShapeText);
        ImGui::SameLine();
        ImGui::Checkbox("Simulate", &simulate);

        ImGui::SeparatorText("Selected Shape Controls");
        //A listbox to select which object is being modified

        const char* items[] = {"CGreen","CCyan","CYellow","RRed","RMagenta","RBlue"};
        static int item_current = 0;
        ImGui::Combo("Shape", &item_current, items, IM_ARRAYSIZE(items), 0);

        for (int i = 0; i < circles.size(); i++) {
            if (item_current == i) //when Text is selected in the Object Select ComboBox
            {
                circles[i].addImgui();
            }
        }

        for (int i = 0; i < rects.size(); i++) {
            //updateShape(rects[i], font);
            if (item_current == i+circles.size()) //when Text is selected in the Object Select ComboBox
            {
                rects[i].addImgui();
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