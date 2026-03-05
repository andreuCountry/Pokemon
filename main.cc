#include <stdio.h>
#include <stdlib.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/sprite.h>
#include <esat/input.h>
#include <esat/time.h>
#include "structs.h"
#include "sprites/sprites.h"

double current_time, last_time;
int fps = 60;

float windowX = 800.0f, windowY = 608.0f;
float defaultHeight = 16.0f, defaultWidth = 16.0f;

FILE *map1;
FILE *map2;

float totalCells = (windowX / defaultWidth) * (windowY / defaultHeight);

Cell* InitCellsMemory() {
    return (Cell*) malloc (totalCells * sizeof(Cell));
}

void LoadMap1() {
    map1 = fopen("files/map1.dat", "w+b");

    // Add all features to send

    /*for (int i = 0; i < 10; i++) {

        int numberInsert = rand()%101;

        fwrite(&numberInsert, sizeof(numberInsert), 1, map1);
    }*/

    fclose(map1);
}

void LoadMap2() {
    map2 = fopen("files/map2.dat", "r+b");

    // Add all features to send

    fclose(map2);
}

void PrepareMaps() {
    LoadMap1();
    LoadMap2();
}

int esat::main(int argc, char **argv) {

    // inicializar la memoria para los cells
    Cell* dataToSave = InitCellsMemory();
    

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