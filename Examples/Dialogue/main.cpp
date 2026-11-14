

// heh custom header files are grate (mispelled great and kept it like that :3)
#include "AATCEngine.h"

/*
References for the AATCEngine 0.2:

BTW this is outdated i'm just too lazy to update them but if you want you
can get some info from here lol

The default resolution is 45x45 since this is text based.
The grid goes left to right increases x and up to down increases y
ex:
0 1 2 3 4 5
1 . . . . .
2 . . . . .
3 . . . . .
4 . . . . .
5 . . . . .
You can increase the resolution by going into the header file, but adjust your text size and/or window size for it!

STRUCTURES:
struct Vector2 { - use this for coords
    int x; - the x
    int y; - the y
};

struct Vector2f { - use for all your float needs. This is more for math rather than actual coords
    float x; - the x
    float y; - the y
};

stuct TwoD { - anything else related that isn't a vector but is two dimensional and integers
    int x; - ze x
    int y; - el y
};

when using any of the structures you can either use them as (ex.) Vector2{0, 2}; or {0, 2} in something like workspace.ShiftViewport();

CLASSES:
class Shape : public gamespace {
protected:
    bool touching = false;

public:
    int Zindex = 0;
    bool Show = true;
    std::string Type;
    std::vector<Vector2> Points;
    char c = '#';

    virtual void Draw() = 0;

    bool IsTouching() const {
        return touching;
    }

    virtual ~Shape() = default;
};


class Line : public Shape {
    public:
        Vector2 StartPos;
        Vector2 EndPos;
    
        void Draw() override;
};

class Rect : public Shape {
    public:
        Vector2 Position;
        Size2D Size;
    
        void Draw() override;
};

class Tri: public Shape {
    public:
        Vector2 Pos1;
        Vector2 Pos2;
        Vector2 Pos3;

        void Draw() override;
};

class Point: public Shape {
    public:
        Vector2 Position;
        
        void Draw() override;
};

class Circle: public Shape {
    public:
        Vector2 Position;
        int Radius;
        
        void Draw() override;
};

workspace - this handles camera and junk more on this soon!

DRAW FUNCTIONS:
DrawLine(int x1, int x2, int y1, int y2, bool render, char c)
You can use this to make your own shapes 

fill(std::vector<std::vector<char>> canvas, int startX, int startY, char replace, char fillwith)
replaces everything in a enclosed space with the selected character

ChangeCanvas(char fillwith)
replaces all characters on screen with the chosen character

RENDERING FUNCTIONS:
plot(std::vector<int> RenderingXValues, std::vector<int> RenderingYValues, std::vector<std::vector<char>> canvas)
Both renders and plots! Something to note is that using any of the draw functions automatically plots it (unless you make render false) and this is just more for customization!

QuickRender(std::vector<int> RXValues, std::vector<int> RYValues, std::vector<std::vector<char>> canvas)
Only renders

SUPPORT FUNCTIONS:
GetXList() - returns all the saved renders for x

GetYList() - returns all the saved renders for y

GetCharList() - returns all the saved characters in the renders

GetCanvas() - returns std::vector<std::vector<char>> canvas

CAMERA FUNCTIONS:
workspace.SetViewport(Vector2 vect) - teleports the camera to the coords

workspace.ShiftViewport(Vector2 vect) - moves the camera based off the numbers!

workspace.GetCamCoords() - returns a Vector2 of the camera/viewport coords

workspace.GetCamX() - returns the camera/viewport x

workspace.GetCamY() - returns the camera/viewport y

TYPES:
"static" - the drawing is a normal object
"GUI" - Acts like a GUI object; doesn't move when camera moves

DELETING FUNCTIONS:
ClearStored() - clears all stored x, y, and char values

clear() - clears the screen of everything, but doesn't clear variables

TrueClear() - clear() and ClearStored() combined

EXTRA FUNCTIONS: (these are just extra functions that you may find useful!)

Clamp(float num, float min, float max) - Clamps or smth

wait(double secs) - waits for the set amount of time

trim(std::string string) - Removes all spaces from a string

Log(std::string log) - Creates a folder (if there isn't one) and a new session file on first log and enters the given string as the log in the file

Math from now on!

Abs(float num) - returns the absolute value of the number

Exp(float num, float exponent) - exponates with the given number and exponent

Root(float num, int index) - finds the root with the given index and number

Mag(float num1, float num2) - finds the magnitude of the two numbers

Unit(Vector2 vect) - unit/normalize the given Vector2 and returns a float version of the vector

Dist(Vector2 vect1, Vector2 vect2) - returns the distance from each other as a double

Circ(bool diameter, float diameter/radius) - returns the circumference with the given value of radius of diameter based off the boolien

pi() - returns a float of pi

Round(float num, int index) - returns the given number rounded with the given index 

TODO:
Lerp()

also make delta time :3

*/

bool Running = true;
char Input;

int XSteps = 0;
int YSteps = 0;

// Log setup
Logger Log;

// Player stuff
Point Player;

// NPCS
Point Leo;

// GUI
Rect DialogueBox;
Rect DialoguePortrait;
Sprite Portrait;
Label DialogueText;

void DrawScreen() {
    Leo.Draw();
    Player.Draw();
}

void Collisions() {
    Player.Position = {Player.Position.x += XSteps, Player.Position.y += YSteps};
    if (Player.Position.x == Leo.Position.x && Player.Position.y == Leo.Position.y) {
        Player.Position = {Player.Position.x -= XSteps, Player.Position.y -= YSteps};
    }
}

void DialogueBoxAnim() {
    for (int i = 1; i < 13; i++) {
        DialogueBox.Size = {30, i};
        TrueClear();
        Portrait.Draw();
        DialoguePortrait.Draw();
        DialogueBox.Draw();
        if (i >= 3) {
            DialogueText.Draw();
        }
        DrawScreen();
        wait(0.05);
    }
}

void Interactions() {
    if (Dist(Player.Position, Leo.Position) <= 1) {
        Portrait.Path = "Sprites/Leo.txt";
        DialogueText.Text = "Hi! My name is Leo!";
        DialogueBoxAnim();
        while (true) {
            TrueClear();
            Portrait.Draw();
            DialoguePortrait.Draw();
            DialogueBox.Draw();
            DialogueText.Draw();
            DrawScreen();
            ScreenshotCanvas("Sprites");
            std::cin>>Input;
            if (Input == 'z') {
                break;
            }
        };
    }
}

void Controls() {
    YSteps = 0;
    XSteps = 0;
    std::cout<<"Use WASD to move or Q to quit\n";
    std::cout<<"> ";
    std::cin>>Input;
    if (Input == 'w') {
        YSteps = -1;
    }
    if (Input == 's') {
        YSteps = 1;
    }
    if (Input == 'a') {
        XSteps = -1;
    }
    if (Input == 'd') {
        XSteps = 1;
    }
    if (Input == 'e') {
        Interactions();
    }
    if (Input == 'q') {
        Running = false;
        Log.Log("Quitting game!");
    }
    Collisions();
}

int main() {
    clear();
    Log.Log("Started Program");
    
    Player.Show = true;
    Player.c = '@';
    Leo.Show = false;
    Leo.c = '?';
    Leo.Position = {10, 10};
    DialoguePortrait.Show = false;
    DialoguePortrait.Position = {25, 12};
    DialoguePortrait.c = 'O';
    DialoguePortrait.Size = {6, 6};
    DialogueBox.Show = false;
    DialogueBox.c = 'O';
    DialogueBox.Position = {1, 19};
    DialogueBox.Size = {30, 12};
    DialogueText.Position = {2, 20};
    DialogueText.Show = false;
    Portrait.Show = false;
    Portrait.Position = {DialoguePortrait.Position.x + 1, DialoguePortrait.Position.y + 1};
    

    while (Running) {
        TrueClear();
        
        DrawScreen();
        Controls();
    };
    
    return 0;
}