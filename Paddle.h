#pragma once
#include <raylib.h>

class Paddle
{
protected:
    void LimitMovement();

public:
    float x, y;
    float width, height;
    int speed;

    void Draw();
    void Update();
};

class CpuPaddle : public Paddle
{
public:
    float reaction_offset = 0.0f;  // Simulates imperfect CPU reaction (0 = perfect)
    float speed_multiplier = 1.0f; // Scales movement speed by difficulty
    
    void Update(int ball_y);
};