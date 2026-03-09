#include "Ball.h"
#include "Paddle.h"
#include "Colors.h"
#include <raylib.h>
#include <cmath>
#include <algorithm>

void Ball::IncreaseSpeed()
{
    current_hits++;
    
    // Increase speed every few hits
    if (current_hits >= hits_until_speedup)
    {
        current_hits = 0;
        
        // Increase magnitude while preserving direction
        float current_magnitude = sqrt(speed_x * speed_x + speed_y * speed_y);
        float new_magnitude = current_magnitude + speed_increment;
        
        if (new_magnitude <= max_speed)
        {
            float ratio = new_magnitude / current_magnitude;
            speed_x *= ratio;
            speed_y *= ratio;
        }
    }
}

void Ball::ClampSpeed()
{
    float current_magnitude = sqrt(speed_x * speed_x + speed_y * speed_y);
    
    if (current_magnitude > max_speed)
    {
        float ratio = max_speed / current_magnitude;
        speed_x *= ratio;
        speed_y *= ratio;
    }
    
    // Ensure minimum speed
    if (current_magnitude < base_speed)
    {
        float ratio = base_speed / current_magnitude;
        speed_x *= ratio;
        speed_y *= ratio;
    }
}

float Ball::GetCurrentSpeed()
{
    return sqrt(speed_x * speed_x + speed_y * speed_y);
}

void Ball::Draw()
{
    DrawCircle(x, y, radius, Yellow);
    
    // Draw speed indicator (optional visual feedback)
    float speed_ratio = GetCurrentSpeed() / max_speed;
    Color glow_color = {255, 255, 255, (unsigned char)(speed_ratio * 100)};
    DrawCircle(x, y, radius + 5, glow_color);
}

void Ball::ResetBall()
{
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    // Reset to base speed
    current_hits = 0;
    
    int speed_choices[2] = {-1, 1};
    speed_x = base_speed * speed_choices[GetRandomValue(0, 1)];
    speed_y = base_speed * speed_choices[GetRandomValue(0, 1)];
}

void Ball::Update(int& player_score, int& cpu_score)
{
    x += speed_x;
    y += speed_y;

    // Bounce off top and bottom
    if (y + radius >= GetScreenHeight() || y - radius <= 0)
    {
        speed_y *= -1;
        y = std::clamp(y, (float)radius, (float)(GetScreenHeight() - radius));
    }

    // Scoring logic
    if (x + radius >= GetScreenWidth())
    {
        cpu_score++;
        ResetBall();
    }

    if (x - radius <= 0)
    {
        player_score++;
        ResetBall();
    }
}

void Ball::BounceFromPaddle(Paddle& p)
{
    // Calculate where the ball hit the paddle (-1 = top, 0 = center, 1 = bottom)
    float paddle_center = p.y + p.height / 2;
    float hit_position = (y - paddle_center) / (p.height / 2);
    hit_position = std::clamp(hit_position, -1.0f, 1.0f);
    
    // Reverse horizontal direction
    speed_x *= -1;
    
    // Add vertical component based on where it hit
    // Max deflection angle is 60 degrees
    float max_angle = 60.0f * DEG2RAD;
    float angle = hit_position * max_angle;
    
    // Get current horizontal speed magnitude
    float speed_magnitude = abs(speed_x);
    
    // Calculate new speeds maintaining the magnitude but adding vertical component
    speed_y = speed_magnitude * tan(angle);
    
    // Add slight speed boost
    speed_x *= 1.05f;
    speed_y *= 1.05f;
    
    ClampSpeed();
    IncreaseSpeed();
}