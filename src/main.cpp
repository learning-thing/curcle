#include <iostream>
#include <raylib.h>
#include "curcle.hpp"

int main() {
    std::cout << "hello world\n";
    int collisions = 0;
    int points = 0;
    SetWindowState(FLAG_VSYNC_HINT);
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "I'm a curcle");
    ToggleFullscreen();
    curcle c(WHITE);
    //Enemy e(100, 100);

    enemyManager em(50);
    Victory v;

    while (!WindowShouldClose()) {
        BeginDrawing();
            //ClearBackground(BLACK);
            ClearBackground(BLACK);
            c.update();
            em.draw();
            v.draw();
            if (v.collides_with(c.rawpos(), c.getSize())) {//Got the poi
                c.reset();
                em.reset();
                v.reset();
                points++;
            }
            if (em.collided(c.rawpos(), c.getSize())) {
                c.reset();
                //em.reset();
                //v.reset();
                collisions++;
            }

            DrawFPS(10, 10);
            DrawText(TextFormat("Deaths: %d", collisions), 100, 10, 20, RED);
            DrawText(TextFormat("Points: %d", points), 500, 10, 20, GREEN);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
