# 🏓 Pong Game

> A classic arcade Pong experience rebuilt in C++ with smooth physics, a reactive CPU opponent, and progressive speed mechanics.

---

## ✨ Features

- 🎮 **Player vs CPU** — go head-to-head against a reactive CPU opponent
- 📐 **Angle-based deflection** — where you hit the paddle changes the ball's trajectory
- ⚡ **Progressive speed** — rallies get faster the longer they go, resetting on each score
- 🏆 **Live scoreboard** — scores displayed in real time
- 🎨 **Custom color palette** — clean green-toned visuals with rounded paddles

---

## 📁 Project Structure

| File | Description |
|------|-------------|
| `main.cpp` | Game loop, initialization & collision detection |
| `Ball.cpp / Ball.h` | Ball movement, physics & speed scaling |
| `Paddle.cpp / Paddle.h` | Player and CPU paddle logic |
| `Colors.h` | Custom color palette |

---

## 🛠️ Requirements

- C++17 or later
- [raylib](https://www.raylib.com/) v4.0+
- A C++ compiler — `g++`, `clang++`, or MSVC

---

## 🚀 Building

**Linux / macOS**

```bash
g++ main.cpp Ball.cpp Paddle.cpp -o pong -lraylib -lm
```

**Windows (MinGW)**

```bash
g++ main.cpp Ball.cpp Paddle.cpp -o pong.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

> Make sure raylib headers and libraries are on your include/library paths.

---

## 🕹️ Controls

| Key | Action |
|-----|--------|
| Arrow Up | Move paddle up |
| Arrow Down | Move paddle down |
| ESC / close window | Quit |

---

## 🎯 How to Play

- You control the **right paddle** — the CPU controls the left
- Get the ball past your opponent to score a point
- Hit the **edge of your paddle** for sharper, trickier angles
- Survive long rallies — the ball speeds up every 4 hits and resets to base speed when someone scores

---

## ⚙️ Physics Configuration

Tune the feel of the game directly in `Ball.h`:

| Property | Default | Description |
|----------|---------|-------------|
| `base_speed` | `7.0` | Starting ball speed |
| `max_speed` | `15.0` | Maximum ball speed cap |
| `speed_increment` | `0.5` | Speed added per speed-up event |
| `hits_until_speedup` | `4` | Paddle hits between each speed increase |

---

## 📜 License

Feel free to use, modify, and build on this project. Have fun!
