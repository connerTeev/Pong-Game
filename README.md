🏓 Pong Game

A classic arcade Pong experience — rebuilt in C++ with smooth physics, smart CPU AI, and progressive speed mechanics.


✨ Features

🎮 Player vs CPU — go head-to-head against a reactive CPU opponent
📐 Angle-based deflection — where you hit the paddle changes the ball's trajectory
⚡ Progressive speed — rallies get faster the longer they go, resetting on each score
🏆 Live scoreboard — scores displayed in real time
🎨 Custom color palette — clean green-toned visuals with rounded paddles


📁 Project Structure
pong/
├── main.cpp        🎮  Game loop, initialization & collision detection
├── Ball.cpp/.h     🟡  Ball movement, physics & speed scaling
├── Paddle.cpp/.h   🟦  Player and CPU paddle logic
└── Colors.h        🎨  Custom color palette

🛠️ Requirements

C++17 or later
raylib v4.0+
A C++ compiler — g++, clang++, or MSVC


🚀 Building
🐧 Linux / 🍎 macOS
bashg++ main.cpp Ball.cpp Paddle.cpp -o pong -lraylib -lm
🪟 Windows (MinGW)
bashg++ main.cpp Ball.cpp Paddle.cpp -o pong.exe -lraylib -lopengl32 -lgdi32 -lwinmm

Make sure raylib headers and libraries are on your include/library paths.


🕹️ Controls
KeyAction↑Move paddle up↓Move paddle downESC / close windowQuit

🎯 How to Play

You control the right paddle — the CPU controls the left
Get the ball past your opponent to score a point 🥅
Hit the edge of your paddle for sharper, trickier angles
Survive long rallies — the ball speeds up over time and resets when someone scores


⚙️ Physics Configuration
Tune the feel of the game directly in Ball.h:
PropertyDefaultDescriptionbase_speed7.0🐢 Starting ball speedmax_speed15.0🐇 Maximum ball speedspeed_increment0.5📈 Speed added per speed-up eventhits_until_speedup4🎯 Hits between each speed increase

📜 License
Feel free to use, modify, and build on this project. Have fun! 🎉