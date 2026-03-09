/*#pragma once
#include <raylib.h>

// Forward declaration
class Paddle;

class Ball
{
public:
    // Position and size
    float x, y;
    int speed_x, speed_y;
    int radius;

    // Functions
    void Draw();
    void Update(int& player_score, int& cpu_score);
    void ResetBall();
    void IncreaseSpeed();
    void BounceFromPaddle(Paddle& p);
};
*/

#pragma once
#include <raylib.h>

// Forward declaration
class Paddle;

class Ball
{
public:
    // Position and size
    float x, y;
    float speed_x, speed_y;
    int radius;
    
    // Physics properties
    float max_speed = 15.0f;
    float base_speed = 7.0f;
    float speed_increment = 0.5f;
    int hits_until_speedup = 4;
    int current_hits = 0;

    // Functions
    void Draw();
    void Update(int& player_score, int& cpu_score);
    void ResetBall();
    void IncreaseSpeed();
    void BounceFromPaddle(Paddle& p);
    
private:
    void ClampSpeed();
    float GetCurrentSpeed();
};