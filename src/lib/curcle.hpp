#ifndef CURCLE_H
#define CURCLE_H
#include <iostream>
#include <raylib.h>
#include "vec2.hpp"
#include <vector>

class curcle {
    private:
        vec2 pos = vec2(20);
        vec2 speed = vec2(10, 10);
        const float size = 20;
        int ScreenWidth;
        int ScreenHeight;
        vec2 mouseVec;
        bool follow = false;

        void physics() {
            pos += speed*GetFrameTime()*60;
            speed*=.99;
            //boucing
            //std::clog << pos.y() << "\n";
            //std::clog << ScreenHeight << "\n";
            /*
            if (pos.y()>=ScreenHeight-size) {
                pos.e[1]=ScreenHeight-size;
                speed.e[1]*=-1;
            }*/
            mouseVec = vec2(GetMouseX(), GetMouseY())-pos;
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


            vec2 L_eye_pos = pos+vec2(size/4, -size/4)+((mouseVec/100));
            vec2 R_eye_pos = pos+vec2(-size/4, -size/4)+((mouseVec/100));

            //

            //Draw eyes
            DrawCircleLinesV((Vector2){L_eye_pos.x(), L_eye_pos.y()}, size/8, WHITE);
            DrawCircleLinesV((Vector2){R_eye_pos.x(), R_eye_pos.y()}, size/8, WHITE);


            //Draw directiion indicator when out of bounds
            float overshoot=0;
            static const unsigned int marginOffset = 30;
            if (pos.y()<0-size) {
                overshoot=abs(pos.y());
                DrawCircle(pos.x(), marginOffset, 20-(overshoot/20), BLUE);
            }
            if (pos.y()>ScreenHeight+size) {
                overshoot=pos.y()-ScreenHeight;
                DrawCircle(pos.x(), ScreenHeight-marginOffset, 20-(overshoot/20), BLUE);
            }
            if (pos.x()<0) {
                overshoot=abs(pos.x());
                DrawCircle(marginOffset, pos.y(), 20-(overshoot/20), BLUE);
            }
            if (pos.x()>ScreenWidth+size) {
                overshoot=pos.x()-(ScreenWidth+size);
                DrawCircle(ScreenWidth-marginOffset, pos.y(), 20-(overshoot/20), BLUE);
            }
        }


    public:
        curcle(Color myColor) {
            ScreenWidth = GetScreenWidth();
            ScreenHeight = GetScreenHeight();
            pos = vec2(ScreenWidth, ScreenHeight)/2;
        }

        Vector2 getpos() {
            return (Vector2){pos.x(), pos.y()};
        }
        float getSize() {
            return size;
        }

        vec2 rawpos() {
            return pos;
        }

        void update() {
            physics();
            draw();
        }

        void reset() {
            pos = vec2(ScreenWidth, ScreenHeight)/2;
            speed = vec2(0);
            follow=false;
            
        }

};


class Enemy {
    private:

    public:
        vec2 pos;

        const unsigned int size = 10;

        Enemy() {
            pos = vec2(
                GetRandomValue(0, GetScreenWidth()),
                GetRandomValue(0, GetScreenHeight())
            );
            float distFromSpawn = (vec2(GetScreenWidth()/2, GetScreenHeight()/2)-pos).length();
            //std::clog << "Distance from spawn: " << distFromSpawn << "\n";

            if (distFromSpawn<size*5) {
                reset();
                //std::clog << "I'm too close to spawn!!\n";
            }
        }


        Enemy(int x, int y) {
            pos = vec2(x, y);
        }

        bool collides_with(vec2 targ, float targsize) {
            if ((targ-pos).length()<(size+targsize)) {
                return true;
            }
            return false;
        }

        void draw() {
            DrawCircle(pos.x(), pos.y(), size, RED);
        }
        void reset() {
            pos = vec2(
                GetRandomValue(0, GetScreenWidth()),
                GetRandomValue(0, GetScreenHeight())
            );
            float distFromSpawn = (vec2(GetScreenWidth()/2, GetScreenHeight()/2)-pos).length();
            //std::clog << "Distance from spawn: " << distFromSpawn << "\n";

            if (distFromSpawn<size*10) {
                reset();
                //std::clog << "I'm too close to spawn!!\n";
            }
            
        }
};

class Victory {
        private:

    public:
        vec2 pos;

        const unsigned int size = 10;

        Victory() {
            pos = vec2(
                GetRandomValue(0, GetScreenWidth()),
                GetRandomValue(0, GetScreenHeight())
            );
        }


        Victory(int x, int y) {
            pos = vec2(x, y);
        }

        bool collides_with(vec2 targ, float targsize) {
            if ((targ-pos).length()<(size+targsize)) {
                return true;
            }
            return false;
        }

        void draw() {
            DrawCircle(pos.x(), pos.y(), size, GREEN);
        }
        void reset() {
            pos = vec2(
                GetRandomValue(0, GetScreenWidth()),
                GetRandomValue(0, GetScreenHeight())
            ); 
            if ((vec2(GetScreenWidth()/2, GetScreenHeight()/2)).length()<size*3) {
                reset();
            }
        }
};

class enemyManager {
    private:
        std::vector<Enemy> enemies;
        int enCount = 0;
    public:
        enemyManager(int enemycount) {
            enCount = enemycount;
            for (int i = 0; i < enCount; i++) {
                enemies.push_back(Enemy());
            }
            
        }
        void draw() {
            for (int i = 0; i < enCount; i++) {
                DrawCircle(enemies[i].pos.x(), enemies[i].pos.y(), enemies[i].size, RED);
            }
        }
        bool collided(vec2 targpos, float targsize) {
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