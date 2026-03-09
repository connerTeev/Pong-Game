#include "Paddle.h"
#include <raylib.h>

void Paddle::LimitMovement()
{
    if (y <= 0)
        y = 0;

    if (y + height >= GetScreenHeight())
        y = GetScreenHeight() - height;
}

void Paddle::Draw()
{
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8f, 0, WHITE);
}

void Paddle::Update()
{
    if (IsKeyDown(KEY_UP))
        y -= speed;

    if (IsKeyDown(KEY_DOWN))
        y += speed;

    LimitMovement();
}

void CpuPaddle::Update(int ball_y)
{
    // Apply reaction offset to simulate imperfect CPU tracking on lower difficulties
    float target_y = ball_y + reaction_offset;

    if (y + height / 2 > target_y)
        y -= speed * speed_multiplier;

    if (y + height / 2 <= target_y)
        y += speed * speed_multiplier;

    LimitMovement();
}
