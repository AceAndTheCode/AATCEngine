// me when i found out about #pragma once 
#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <chrono>
#include <string>
#include <thread>
#include <fstream>
#include <filesystem>

/*
Made by: AceAndTheCode
AATCEngine.h release V0.2

One could only wonder why it's called AATCEngine...

I would put update notes but i don't ever remember what i add so good luck
lost media guys :D

All rights are not reserved and you can just lowkey steal from me :(
You wouldn't tho right? :]
Just a basic graphics engine I made cause I was bored...

uhh pls credit ig

the true reason behind this whole graphics library? I lowkey could not for the
life of me figure out how to download the other graphic libraries and i have
a deep love for ASCII so yeah. Also i lowkey didn't want to download stuff
if im using another person's computer, but tbh i would have to download this
so it kind of defeats the purpose... I still love cpp and text-based games!!!

Also the reason i made a bunch of math functions rather than use <cmath> is cause
i wanted this to use the minimum amount of libraries and especially no outside of
the default libraries so i made the math functions to replace <cmath> :3

Also <vector> and <array> are my new true loves of libraries (other than <chrono> and <thread>
they will always be my true loves) for c++
*/

// I LOVE YOU BRESENHAM

namespace fs = std::filesystem;

// functions setup

// 2D graphics setup
const int Width = 32;
const int Height = 32;
const int SetFPS = 10;
std::vector<int> RXValues;
std::vector<int> RYValues;
std::vector<char> RCValues;
char CanvasChar = '.';
using Canvas = std::vector<std::vector<char>>;

Canvas mainCanvas(Width, std::vector<char>(Height, CanvasChar));
// structures
struct Vector2 { int x; int y; };

struct Vector2f { float x; float y; };

struct Size2D { int width; int height; };

// classes for me lovely engine :3
class gamespace {
    protected:
        Vector2 CamPos;
    public:
        bool ShowGrid = false;
        void ShiftViewport(Vector2 vect);
        void SetViewport(Vector2 vect);
        Vector2 GetCamCoords();
        int GetCamX();
        int GetCamY();
};


// definetly not stealing from Roblox :3
gamespace workspace;

class Shape : public gamespace {
protected:
    bool touching = false;

public:
    int Zindex = 0;
    bool Show = false;
    std::string Type;
    std::vector<Vector2> Points;

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
        char c = '#';
    
        void Draw() override;
};

class Rect : public Shape {
    public:
        Vector2 Position;
        Size2D Size;
        char c = '#';
    
        void Draw() override;
};

class Tri: public Shape {
    public:
        Vector2 Pos1;
        Vector2 Pos2;
        Vector2 Pos3;
        char c = '#';

        void Draw() override;
};

class Point: public Shape {
    public:
        Vector2 Position;
        char c = '#';
        
        void Draw() override;
};

class Circle: public Shape {
    public:
        Vector2 Position;
        int Radius;
        char c = '#';
        
        void Draw() override;
};

class Label: public Shape {
    public:
        Vector2 Position;
        std::string Text = "";
        
        void Draw() override;
};

class Sprite: public Shape {
    public:
        Vector2 Position;
        std::string Path = "";
        
        void Draw() override;
};


// there's probably a better way but i made it like this and im not recoding
class Logger {
protected:
    int LogCount = 1;
private:
    std::ofstream logFile;

public:
    Logger() {
        std::filesystem::create_directories("Logs");
        logFile.open("Logs/latest.txt", std::ios::out | std::ios::trunc);
    }

    void Log(const std::string& msg) {
        logFile<<LogCount<<" : "<<msg<<'\n';
        LogCount += 1;
    }
};

// basic functions

// this is honestly the goat of all functions... Love you multiplication
void wait(double Secs) {
    std::cout<<"\n";
    Secs = Secs * 1000;
    int secs = Secs;
    std::this_thread::sleep_for(std::chrono::milliseconds(secs));
}

// this is for me because let's all agree we are not remembering the ASCII escape code T-T
void clear() {
    std::cout<<"\033[H\033[2J\033[3J"<<std::flush;
}

// math

// wowza...
float intPower(float base, int exponent) {
    float result = 1.0f;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

float Clamp(float num, float min, float max) {
    if (num < min) {
        num = min;
    }else if(num > max) {
        num = max;
    }
    
    return num;
}

// yes i made a whole function for pi... dont ask why
float pi() {
    return 3.1415926535898;
}

// idk who this comes from i just heard it's called the nth root or smth and 
// stole it from math :3
float nthRoot(float value, int n) {
    if (value < 0 && n % 2 == 0) {
        return 0;
    }
    float guess = value / n;
    for (int i = 0; i < 20; ++i) {
        guess = ((n - 1) * guess + value / intPower(guess, n - 1)) / n;
    }
    return guess;
}

float Exp(float num, float e) {
    if (e == 1) { return num; }
    if (e == 0) { return 1; }
    if (e > 1) {
        return intPower(num, static_cast<int>(e));
    }
    if (e < 1) {
        int denominator = static_cast<int>(1.0f / e);
        return nthRoot(num, denominator);
    }
    
    return 0;
}

float Round(float num, int index) {
    float test = 0;
    if (num > 0) {
        do {
            test += 1 / Exp(10, index);
        } while (test <= num);
    }else {
        do {
            test -= 1 / Exp(10, index);
        } while (test >= num);
    }
    test -= 1 / Exp(10, index);
    float temp = num - test;
    if (temp < 0.5 / Exp(10, index)) {
        return num - temp;
    }else {
        return num + (1 / Exp(10, index) - temp);
    }
}

float Abs(float num) {
    if (num < 0) {
        return num * -1;
    }else {
        return num;
    }
}

float Root(float num, float index) {
    if (num <= 0 || index <= 0) { return 0; }
    return Exp(num, (1 / index));
}

// yum... triangles
float Mag(float num1, float num2) {
    float csquared = Exp(num1, 2) + Exp(num2, 2);
    return Root(csquared, 2);
}

// surprisingly this only took like 3 test runs to make it work!
Vector2f Unit(Vector2 vect) {
    if (vect.x == 0 && vect.y == 0) { return Vector2f{0, 0}; }
    return Vector2f{vect.x / Mag(vect.x, vect.y), vect.y / Mag(vect.x, vect.y)};
}

// Yes this made my head hurt
double Dist(Vector2 vect1, Vector2 vect2) {
    return Root((Exp((vect2.x - vect1.x), 2) + Exp(vect2.y - vect1.y, 2)), 2);
}

float Circ(bool diameter, float radius) {
    float c;
    if (diameter) {
        c = pi() * radius;
    }else{
        c = 2 * pi() * radius;
    }
    
    return c;
}

float Cos(float adj, float hyp) {
    return adj / hyp;
}

float Tan(float op, float adj) {
    return op / adj;
}

float Sin(float op, float hyp) {
    return op / hyp;
}

float Min(float num1, float num2) {
    if (num1 < num2) {
        return num1;
    }else {
        return num2;
    }
}

float Max(float num1, float num2) {
    if (num1 > num2) {
        return num1;
    }else {
        return num2;
    }
}

// my head hurts
float CopySign(float num1, float num2) {
    if (num1 >= 0) {
        return Abs(num2);
    }else {
        return Abs(num2) * -1;
    }
}

// REMINDERS:
// make Floor() function
// make Ciel() function

// strings

std::string trim(std::string str) {
    std::string newStr = "";
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c != ' ') {
            newStr += c;
        }
    }
    return newStr;
}

// lets be honest i don't know if i put the & in the right area :P
void swap(auto &x, auto &y) {
    auto e = x;
    x = y;
    y = e;
}

bool MadeLog = false;

/*
Random example code from the inter-webs
std::chrono::time_point<std::chrono::steady_clock> lastTime = std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
std::chrono::duration<float> elapsedTime = currentTime - lastTime;
float deltaTime = elapsedTime.count();
lastTime = currentTime;*/



// how to make new threads :3
// std::jthread VarName(Function, FunctionVariable);

float GetDelta() {
    if (!MadeLog) {
        // one day ill come back to this... but not now
    }
    return 1.0;
}


// functions for 2d graphics

// yummy... (why did i add this? This has like no function realistically T-T)
void ClearStored() {
    RXValues = {};
    RYValues = {};
    RCValues = {};
    mainCanvas = Canvas(Width, std::vector<char>(Height, '.'));
}

// the much better version of ClearStored()
void TrueClear() {
    RXValues = {};
    RYValues = {};
    RCValues = {};
    mainCanvas = Canvas(Width, std::vector<char>(Height, '.'));
    clear();
}

void ChangeCanvas(char c) {
    CanvasChar = c;
    mainCanvas = Canvas(Width, std::vector<char>(Height, c));
}

std::vector<std::vector<char>>& GetCanvas() {
    return mainCanvas;
}
std::vector<int>& GetXList() {
    return RXValues;
}
std::vector<int>& GetYList() {
    return RYValues;
}

std::vector<char>& GetCharList() {
    return RCValues;
}

void gamespace::ShiftViewport(Vector2 vect) {
    // can anyone translate this? (a math joke btw)
    CamPos.x += vect.x;
    CamPos.y += vect.y;
}
void gamespace::SetViewport(Vector2 vect) {
    // kinda like a teleport :D
    CamPos = vect;
}

Vector2 gamespace::GetCamCoords() {
    return CamPos;
}

int gamespace::GetCamX() {
    return CamPos.x;
}

int gamespace::GetCamY() {
    return CamPos.y;
}

// woah... im being lazy and making it just replace screenshots and not make a new file each screenshot :3
void ScreenshotCanvas(fs::path Destination) {
    std::ofstream File;
    File.open(Destination / "Screenshot.txt", std::ios::out | std::ios::trunc);
    auto canvas = GetCanvas();
    
    for (int i = 0; i < RXValues.size(); ++i) {
        int x = RXValues[i];
        int y = RYValues[i];
        char c = RCValues[i];
        if (x >= 0 && x < Width && y >= 0 && y < Height) {
            canvas[y][x] = c;
        }
    }
    
    std::string str;
    
    for (int y = 0; y < Height; ++y) {
        for (int x = 0; x < Width; ++x) {
            str += canvas[y][x];
            str += ' ';
        }
        str += '\n';
    }
    File<<str;
    File.close();
}

// drawing junk
void UpdateShapes() {
    // this will check if certain shapes touch each other
}

// you know i could probably just make it default to the global vector tables
// but i have a feeling some person is just going to figure out some cool
// use of this function so im being lazy :3
void plot(const std::vector<int>& newX, const std::vector<int>& newY, const std::vector<char>& newC, std::vector<std::vector<char>>& canvas) {
    for (int i = 0; i < newX.size(); ++i) {
        int x = newX[i];
        int y = newY[i];
        char c = newC[i];
        if (x >= 0 && x < Width && y >= 0 && y < Height) {
            canvas[y][x] = c;
        }
    }
    for (int y = 0; y < Height; ++y) {
        if (workspace.ShowGrid) {
            std::cout<<y<<" ";
        }
        for (int x = 0; x < Width; ++x) {
            std::cout << canvas[y][x];
            std::cout<<' ';
        }
        std::cout << '\n';
    }
}

// Iterative Flood Fills are c00l and yes i lowkey copied the functionality of someone elses code
// but i forgot who so... :P
void fill(std::vector<std::vector<char>>& canvas, int startX, int startY, char targetChar, char replacementChar) {
    if (startX < 0 || startX >= Width || startY < 0 || startY >= Height) return;
    if (canvas[startY][startX] != targetChar) return;
    if (canvas[startY][startX] == replacementChar) return;

    std::queue<std::pair<int, int>> q;
    q.push({startX, startY});
    canvas[startY][startX] = replacementChar;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx >= 0 && nx < Width && ny >= 0 && ny < Height) {
                if (canvas[ny][nx] == targetChar) {
                    canvas[ny][nx] = replacementChar;
                    q.push({nx, ny});
                }
            }
        }
    }
}


/*
to be so honest this is a renemant of the old version and i was too lazy to
update the line function so it looks out of place lol.
I might update it sometime... (I'm never updating it and i just copied the
code from some website teaching junk and added all my functions...)
*/
void DrawLine(int x1, int y1, int x2, int y2, bool render, char c, std::vector<Vector2> &Points) {
    std::vector<std::vector<char>>& canvas = GetCanvas();
    int dx = Abs(x2 - x1);
    int dy = Abs(y2 - y1);
    int sx = (x2 > x1) ? 1 : -1;
    int sy = (y2 > y1) ? 1 : -1;
    bool swapXY = dy > dx;
    if (swapXY) { 
        swap(dx, dy); 
    }
    std::vector<int> xValues;
    std::vector<int> yValues;
    std::vector<char> cValues;
    int error = 2 * dy - dx;
    int x = x1;
    int y = y1;
    for (int i = 0; i <= dx; ++i) {
        xValues.push_back(x);
        yValues.push_back(y);
        cValues.push_back(c);
        Points.push_back({x, y});
        if (error >= 0) {
            if (swapXY) { x += sx; } else { y += sy; }
            error -= 2 * dx;
        }
        if (swapXY) { y += sy; } else { x += sx; }
        error += 2 * dy;
    }
    
    // this is why i love semicolons in c++ :3
    for (int i = 0; i < xValues.size(); i++) { RXValues.push_back(xValues[i]); }
    for (int i = 0; i < yValues.size(); i++) { RYValues.push_back(yValues[i]); }
    for (int i = 0; i < cValues.size(); i++) { RCValues.push_back(cValues[i]); }
    if (render) {
        plot(RXValues, RYValues, RCValues, canvas);
    }
}

void Line::Draw() {
    // I'm like half sure this does nothing...
    if (!c) {
        c = '#';
    }
    if (Type == "static") {
        StartPos.x += workspace.GetCamX();
        EndPos.x += workspace.GetCamX();
        StartPos.y += workspace.GetCamY();
        EndPos.y += workspace.GetCamY();
    }
    
    DrawLine(StartPos.x, StartPos.y, EndPos.x, EndPos.y, Show, c, Points);
}

void Rect::Draw() {
    if (!Size.width || !Size.height) {
        return;
    }
    if (!c) {
        c = '#';
    }
    if (Type == "static") {
        Position.x += workspace.GetCamX();
        Position.y += workspace.GetCamY();
    }
    
    DrawLine(Position.x, Position.y, Position.x + (Size.width - 1), Position.y, false, c, Points);
    DrawLine(Position.x, Position.y, Position.x, Position.y + (Size.height - 1), false, c, Points);
    DrawLine(Position.x + (Size.width - 1), Position.y, Position.x + (Size.width - 1), Position.y + (Size.height - 1), false, c, Points);
    DrawLine(Position.x, Position.y + (Size.height - 1), Position.x + (Size.width - 1), Position.y + (Size.height - 1), Show, c, Points);
}

void Tri::Draw() {
    if (!c) {
        c = '#';
    }
    std::vector<std::vector<char>>& canvas = GetCanvas();
    if (Type == "static") {
        Pos1.x += workspace.GetCamX();
        Pos2.x += workspace.GetCamX();
        Pos3.x += workspace.GetCamX();
        Pos1.y += workspace.GetCamY();
        Pos2.y += workspace.GetCamY();
        Pos3.y += workspace.GetCamY();
    }
    
    DrawLine(Pos1.x, Pos1.y, Pos2.x, Pos2.y, false, c, Points);
    DrawLine(Pos2.x, Pos2.y, Pos3.x, Pos3.y, false, c, Points);
    DrawLine(Pos3.x, Pos3.y, Pos1.x, Pos1.y, Show, c, Points);
}

void Point::Draw() {
    if (!c) {
        c = '#';
    }
    std::vector<std::vector<char>>& canvas = GetCanvas();
    if (Type == "static") {
        Position.x += workspace.GetCamX();
        Position.y += workspace.GetCamY();
    }
    
    RXValues.push_back(Position.x);
    RYValues.push_back(Position.y);
    RCValues.push_back(c);
    
    if (Show) {
        plot(RXValues, RYValues, RCValues, canvas);
    }
}

void Label::Draw() {
    std::vector<std::vector<char>>& canvas = GetCanvas();
    if (Type == "static") {
        Position.x += workspace.GetCamX();
        Position.y += workspace.GetCamY();
    }
    
    for (size_t i = 0; i < Text.size(); ++i) {
        char c = Text[i];
        RXValues.push_back(Position.x + i);
        RYValues.push_back(Position.y);
        RCValues.push_back(c);
    }
    
    if (Show) {
        plot(RXValues, RYValues, RCValues, canvas);
    }
}

void Sprite::Draw() {
    std::vector<std::vector<char>>& canvas = GetCanvas();
    if (Type == "static") {
        Position.x += workspace.GetCamX();
        Position.y += workspace.GetCamY();
    }
    
    if (Path == "") {
        return;
    }
    
    fs::path SpriteFilePath = Path;
    
    std::ifstream SpriteFile = SpriteFilePath;
    
    std::string Text = "";
    
    int LineNum = 0;
    
    while (std::getline(SpriteFile, Text)) {
        for (size_t i = 0; i < Text.size(); ++i) {
            char c = Text[i];
            RXValues.push_back(Position.x + i);
            RYValues.push_back(Position.y + LineNum);
            if (c == ' ') {
                RCValues.push_back(CanvasChar);
            }else {
                RCValues.push_back(c);
            }
        }
        LineNum += 1;
    }
    
    if (Show) {
        plot(RXValues, RYValues, RCValues, canvas);
    }
}

void Circle::Draw() {
    if (!c) {
        c = '#';
    }
    if (!Radius) {
        Radius = 3;
    }
    std::vector<std::vector<char>>& canvas = GetCanvas();
    if (Type == "static") {
        Position.x += workspace.GetCamX();
        Position.y += workspace.GetCamY();
    }
    
    std::vector<int> xValues;
    std::vector<int> yValues;
    std::vector<char> cValues;
    int N = 2 * Radius + 1;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int X = i - Radius;
            int Y = j - Radius;
            int distanceSquared = X * X + Y * Y;

           if (distanceSquared >= (Radius * Radius - Radius) && distanceSquared <= (Radius * Radius + Radius)) {
                xValues.push_back(Position.x + X);
                yValues.push_back(Position.y + Y);
                Points.push_back({Position.x + X, Position.y + Y});
                cValues.push_back(c);
            }
        }
    }

    for (int i = 0; i < xValues.size(); i++) {
        RXValues.push_back(xValues[i]);
    }
    for (int i = 0; i < yValues.size(); i++) {
        RYValues.push_back(yValues[i]);
    }
    for (int i = 0; i < cValues.size(); i++) {
        RCValues.push_back(cValues[i]);
    }

    if (Show) {
        plot(RXValues, RYValues, RCValues, canvas);
    }
}