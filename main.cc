#include <stdio.h>
#include <stdlib.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/sprite.h>
#include <esat/input.h>
#include <esat/time.h>

double current_time, last_time;
int fps = 60;

float windowX = 1200.0f, windowY = 800.0f;

int esat::main(int argc, char **argv) {
    esat::WindowInit(windowX, windowY);
    esat::WindowSetMouseVisibility(true);

    while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
        last_time = esat::Time();

        esat::DrawBegin();
        esat::DrawClear(0, 10, 0);

        esat::DrawEnd();

        do { current_time = esat::Time(); }
        while ((current_time - last_time) <= 1000.0 / fps);

        esat::WindowFrame();
    }


    esat::WindowDestroy();
    return 0;
}