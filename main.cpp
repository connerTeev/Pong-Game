#include <iostream>
#include <raylib.h>

#include "Ball.h"
#include "Paddle.h"
#include "Colors.h"

using namespace std;

// Game states
enum GameState { MENU, PLAYING };

int player_score = 0;
int cpu_score = 0;

Ball ball;
Paddle player;
CpuPaddle cpu;

// Difficulty settings applied to the CPU paddle
struct DifficultyConfig
{
    float speed_multiplier;
    float reaction_offset;
};

const DifficultyConfig EASY   = { 0.55f, 40.0f  };
const DifficultyConfig MEDIUM = { 0.80f, 15.0f  };
const DifficultyConfig HARD   = { 1.05f,  0.0f  };

void ApplyDifficulty(DifficultyConfig config)
{
    cpu.speed_multiplier  = config.speed_multiplier;
    cpu.reaction_offset   = config.reaction_offset;
}

// Draw a button and return true if it was clicked this frame
bool DrawButton(const char* label, int x, int y, int w, int h, Color base_color)
{
    Rectangle rect = { (float)x, (float)y, (float)w, (float)h };
    bool hovered = CheckCollisionPointRec(GetMousePosition(), rect);

    Color draw_color = hovered ? WHITE : base_color;
    Color text_color = hovered ? Dark_Green : WHITE;

    DrawRectangleRounded(rect, 0.4f, 0, draw_color);

    int font_size = 28;
    int text_w = MeasureText(label, font_size);
    DrawText(label, x + (w - text_w) / 2, y + (h - font_size) / 2, font_size, text_color);

    return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

int main()
{
    cout << "Starting the game" << endl;

    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Pong!");
    SetTargetFPS(60);

    // Ball setup
    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    // Player paddle setup
    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height - player.height / 2;
    player.speed = 6;

    // CPU paddle setup
    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 6;
    ApplyDifficulty(MEDIUM); // default difficulty

    GameState state = MENU;
    int selected_difficulty = 1; // 0 = Easy, 1 = Medium, 2 = Hard

    // Button layout
    const int btn_w = 220;
    const int btn_h = 60;
    const int btn_gap = 20;
    const int total_w = btn_w * 3 + btn_gap * 2;
    const int diff_y = screen_height / 2;
    const int start_y = diff_y + btn_h + 50;

    int easy_x   = screen_width / 2 - total_w / 2;
    int medium_x = easy_x + btn_w + btn_gap;
    int hard_x   = medium_x + btn_w + btn_gap;
    int start_x  = screen_width / 2 - btn_w / 2;


    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        if (state == MENU)
        {
            // Background
            ClearBackground(Dark_Green);
            DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
            DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
            DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);

            // Title
            const char* title = "PONG";
            int title_size = 120;
            int title_w = MeasureText(title, title_size);
            DrawText(title, screen_width / 2 - title_w / 2, screen_height / 4 - 60, title_size, WHITE);

            // Difficulty label
            const char* diff_label = "SELECT DIFFICULTY";
            int label_size = 24;
            int label_w = MeasureText(diff_label, label_size);
            DrawText(diff_label, screen_width / 2 - label_w / 2, diff_y - 50, label_size, WHITE);

            // Difficulty buttons
            Color easy_color   = (selected_difficulty == 0) ? Light_Green : Green;
            Color medium_color = (selected_difficulty == 1) ? Light_Green : Green;
            Color hard_color   = (selected_difficulty == 2) ? Light_Green : Green;

            if (DrawButton("EASY",   easy_x,   diff_y, btn_w, btn_h, easy_color))
            {
                selected_difficulty = 0;
                ApplyDifficulty(EASY);
            }
            if (DrawButton("MEDIUM", medium_x, diff_y, btn_w, btn_h, medium_color))
            {
                selected_difficulty = 1;
                ApplyDifficulty(MEDIUM);
            }
            if (DrawButton("HARD",   hard_x,   diff_y, btn_w, btn_h, hard_color))
            {
                selected_difficulty = 2;
                ApplyDifficulty(HARD);
            }

            // Start button
            if (DrawButton("START GAME", start_x, start_y, btn_w, btn_h, Yellow))
            {
                // Reset scores and ball before starting
                player_score = 0;
                cpu_score    = 0;
                ball.ResetBall();
                state = PLAYING;
            }
        }
        else if (state == PLAYING)
        {
            // Updating
            ball.Update(player_score, cpu_score);
            player.Update();
            cpu.Update(ball.y);

            // Collision detection
            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                Rectangle{player.x, player.y, player.width, player.height}))
            {
                ball.BounceFromPaddle(player);
            }
            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
            {
                ball.BounceFromPaddle(cpu);
            }

            // Drawing
            ClearBackground(Dark_Green);
            DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
            DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
            DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
            ball.Draw();
            cpu.Draw();
            player.Draw();
            DrawText(TextFormat("%i", cpu_score),    screen_width / 4 - 20,     20, 80, WHITE);
            DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

            // ESC returns to menu
            if (IsKeyPressed(KEY_ESCAPE))
                state = MENU;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}