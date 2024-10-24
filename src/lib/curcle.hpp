#ifndef CURCLE_H
#define CURCLE_H
#include <raylib.h>
#include "vec.hpp"
#include <vector>

class curcle {
    private:
        vec3 pos = vec3(20);
        vec3 speed = vec3(10, 10, 0);
        const float size = 20;
        int ScreenWidth;
        int ScreenHeight;
        vec3 mouseVec;
        bool follow = false;

        void physics() {
            pos += speed*GetFrameTime()*60;
            speed*=.99;
            //boucing
            //std::clog << pos.y() << "\n";
            //std::clog << ScreenHeight << "\n";

            if (pos.y()>=ScreenHeight-size) {
                pos.e[1]=ScreenHeight-size;
                speed.e[1]*=-1;
            }
            mouseVec = vec3(GetMouseX(), GetMouseY(), 0)-pos;
            if (follow) {
                speed+=mouseVec/800;
            }

            if (mouseVec.length()<size*10) {
                follow=true;
            }
        }

        void draw() {
            DrawCircleLinesV(getpos(), size, WHITE); // draw main shape
            //vec3 fullscreenVec = vec3(ScreenWidth, ScreenHeight, 0)/2;


            vec3 L_eye_pos = pos+vec3(size/4, -size/4, 0)+((mouseVec/100));
            vec3 R_eye_pos = pos+vec3(-size/4, -size/4, 0)+((mouseVec/100));

            //

            //Draw eyes
            DrawCircleLinesV((Vector2){L_eye_pos.x(), L_eye_pos.y()}, size/8, WHITE);
            DrawCircleLinesV((Vector2){R_eye_pos.x(), R_eye_pos.y()}, size/8, WHITE);
        }


    public:
        curcle(Color myColor) {
            ScreenWidth = GetScreenWidth();
            ScreenHeight = GetScreenHeight();
            pos = vec3(ScreenWidth, ScreenHeight, 0)/2;
        }

        Vector2 getpos() {
            return (Vector2){pos.x(), pos.y()};
        }
        float getSize() {
            return size;
        }

        vec3 rawpos() {
            return pos;
        }

        void update() {
            physics();
            draw();
        }

        void reset() {
            pos = vec3(ScreenWidth, ScreenHeight, 0)/2;
            speed = vec3(0);
            follow=false;
        }

};


class Enemy {
    private:

    public:
        vec3 pos;

        const unsigned int size = 10;

        Enemy() {
            pos = vec3(
                GetRandomValue(0, GetScreenWidth()),
                GetRandomValue(0, GetScreenHeight()),
                0
            );
        }


        Enemy(int x, int y) {
            pos = vec3(x, y, 0);
        }

        bool collides_with(vec3 targ, float targsize) {
            if ((targ-pos).length()<(size+targsize)) {
                return true;
            }
            return false;
        }

        void draw() {
            DrawCircle(pos.x(), pos.y(), size, RED);
        }
        void reset() {
            pos = vec3(
                GetRandomValue(0, GetScreenWidth()),
                GetRandomValue(0, GetScreenHeight()),
                0
            );
        }
};

class Victory {
        private:

    public:
        vec3 pos;

        const unsigned int size = 10;

        Victory() {
            pos = vec3(
                GetRandomValue(0, GetScreenWidth()),
                GetRandomValue(0, GetScreenHeight()),
                0
            );
        }


        Victory(int x, int y) {
            pos = vec3(x, y, 0);
        }

        bool collides_with(vec3 targ, float targsize) {
            if ((targ-pos).length()<(size+targsize)) {
                return true;
            }
            return false;
        }

        void draw() {
            DrawCircle(pos.x(), pos.y(), size, GREEN);
        }
        void reset() {
            pos = vec3(
                GetRandomValue(0, GetScreenWidth()),
                GetRandomValue(0, GetScreenHeight()),
                0
            ); 
            if ((vec3(GetScreenWidth()/2, GetScreenHeight()/2, 0)).length()<size*3) {
                reset();
            }
        }
};

class enemyManager {
    private:
        std::vector<Enemy> enemies;
        int enCount;
    public:
        enemyManager(int enemycount) {
            for (int i = 0; i < enCount; i++) {
                enemies.push_back(Enemy());
            }
            
        }
        void draw() {
            for (int i = 0; i < enCount; i++) {
                DrawCircle(enemies[i].pos.x(), enemies[i].pos.y(), enemies[i].size, RED);
            }
        }
        bool collided(vec3 targpos, float targsize) {
            for (int i = 0; i < enCount; i++) {
                if (enemies[i].collides_with(targpos, targsize)) return true;
            }
            return false;
        }
        void reset() {
            for (int i = 0; i < enCount; i++) {
                enemies[i].reset();
            }
            add_enemy();
        }
        void add_enemy() {//free enemies, assign new
            enemies.push_back(Enemy());
            enCount++;
        } 
};

#endif