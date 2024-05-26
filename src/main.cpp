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

//original dimensions: 1280 x 800
//const int windowWidth = 1000;
//const int windowHeight = 500;


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

            if (objSpeedX >= 0) {
                objRight = true;
            }
            else {
                objRight = false;
                this->objSpeedX = -objSpeedX;
            }

            if (objSpeedY >= 0) {
                objDown = true;
            }
            else {
                objDown = false;
                this->objSpeedY = -objSpeedY;
            }
        }

        void move(int windowWidth, int windowHeight) {
            if (objRight)
            {
                objX += objSpeedX;
                if (objX + objRadius >= windowWidth)
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
                if (objY + objRadius >= windowHeight)
                    objDown = false;
            }
            else
            {
                objY -= objSpeedY;
                if (objY - objRadius <= 0)
                    objDown = true;
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

        void addImgui() {
            //checkboxes, they directly modify the value (which is why we send a reference)
            ImGui::Checkbox("Draw Object1", &drawObj);
            ImGui::SameLine();
            ImGui::Checkbox("Draw Object1 Text", &drawObjText);

            //slider, again directly modifies the value and limites between 0 and 300 for this example
            ImGui::SliderFloat("Radius", &objRadius, 0.0f, 300.0f);

            ImGui::SliderFloat("SpeedX", &objSpeedX, 0.0f, 150.0f);
            ImGui::SliderFloat("SpeedY", &objSpeedY, 0.0f, 75.0f);

            //color picker button, directly modifies the color (3 element float array)
            ImGui::ColorEdit3("Object1 Color", objColor);

            //text input field, directly modifies the string
            ImGui::InputText("Text", &objNewText);

            //Buttons
            if (ImGui::Button("Reset Object1")) {
                objX = 50.0;
                objY = 50.0;
                objRadius = 50;
            }
            ImGui::SameLine();
            if (ImGui::Button("Set Text")) {
                objName = objNewText;
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

            if (objSpeedX >= 0) {
                objRight = true;
            }
            else {
                objRight = false;
                this->objSpeedX = -objSpeedX;
            }

            if (objSpeedY >= 0) {
                objDown = true;
            }
            else {
                objDown = false;
                this->objSpeedY = -objSpeedY;
            }
        }

        void move(int windowWidth, int windowHeight) {
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

        void addImgui() {
            ImGui::Checkbox("Draw Object2", &drawObj);
            ImGui::SameLine();
            ImGui::Checkbox("Draw Object2 Text", &drawObjText);

            //slider, again directly modifies the value and limites between 0 and 300 for this example
            ImGui::SliderFloat("Length", &objLength, 0.0f, 300.0f);
            ImGui::SliderFloat("Width", &objWidth, 0.0f, 300.0f);

            ImGui::SliderFloat("SpeedX", &objSpeedX, 0.0f, 150.0f);
            ImGui::SliderFloat("SpeedY", &objSpeedY, 0.0f, 75.0f);

            //color picker button, directly modifies the color (3 element float array)
            ImGui::ColorEdit3("Object1 Color", objColor);

            //text input field, directly modifies the string
            ImGui::InputText("Text", &objNewText);

            //Buttons
            if (ImGui::Button("Reset Object1")) {
                objX = 1000.0;
                objY = 50.0;
                objLength = 30;
                objWidth = 60;
            }
            ImGui::SameLine();
            if (ImGui::Button("Set Text")) {
                objName = objNewText;
            }
        }
};

//object update function
void updateShape(Shape& obj, Font font, int windowWidth, int windowHeight) {
    if (obj.drawObj) {
        obj.draw(font);
    }
    obj.move(windowWidth, windowHeight);
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

                rects.push_back(Rect(tLength, tWidth, tSpeedX, tSpeedY, tX, tY, tRed, tGreen, tBlue, tName));
            }
        }
        
        input.close();

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "Assignment1Soln");

    //initialize the raylib ImGui backend
    rlImGuiSetup(true);
    //increase ImGui item size to 2x
    ImGui::GetStyle().ScaleAllSizes(2);

    // Set raylib to target 60 frames-per-second (this does not mean it will actually RUN at 60 fps)
    SetTargetFPS(60);

    // General variables
    //--------------------------------------------------------------------------------------


    //circle & rect initialization

    //Object Parameters: Circle(float Radius, float SpeedX, float SpeedY, float X, float Y, float Red, float Green, float Blue, string Name)
    // Circle obj1 = Circle(50.0f, 1.0f, 0.5f, 50.0f, 50.0f, 0.0f, 0.0f, 1.0f, "Object1");

    //Object Parameters: Rect(float Length, float Width, float SpeedX, float SpeedY, float X, float Y, float Red, float Green, float Blue, string Name)
    //Rect obj2 = Rect(30, 60, 1.0f, 0.5f, 900.0f, 50.0f, 1.0f, 0.5f, 0.0f, "Object2");


    //vector for shape storage
    //std::vector<Shape*> shapes;

    bool posY = true;
    bool posX = true;

    //Let's draw some text to the screen too
    bool drawText = false;
    std::string strText = "Some Text";
    std::string newText = strText;

    //load a font (Raylib gives warning if font can't be found, then uses default as fallback)
    Font font = LoadFont("assets/Orbitron.ttf");

    //shapes[0]->draw(font);
    //shapes[1]->draw(font);

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
            updateShape(rects[i], font, screenWidth, screenHeight);
        }

        for (int i = 0; i < circles.size(); i++) {
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
        ImGui::SetNextWindowSize(ImVec2(350, 250));
        //creates a new window
        ImGui::Begin("Assignment 1 Controls", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::Text("All Shape Controls");

        ImGui::Text("Selected Shape Controls");
        //A listbox to select which object is being modified

        const char* items[] = {"CGreen","CCyan","CYellow","RRed","RMagenta","RBlue"};
        static int item_current = 0;
        ImGui::Combo("Object\nSelect", &item_current, items, IM_ARRAYSIZE(items), 1);

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