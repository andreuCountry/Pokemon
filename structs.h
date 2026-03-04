#include "mathlib.h"
#include <esat/draw.h>
#include <esat/sprite.h>

#ifndef STRUCTS_H
#define STRUCTS_H

enum Direction {
    RIGHT,
    LEFT,
    UP,
    DOWN
};

struct Collider{
    mlib::Vec2 P1 = {0.0f,0.0f};
    mlib::Vec2 P2 = {20.0f ,20.0f};
};

// Structure composed by the values needed to manage
// Image subdivision from a SpriteSheet-like format
struct SpriteSheet{
    //SpriteSheet image
    esat::SpriteHandle sprite_sheet_image;
    int sprite_w, sprite_h;
    //Row total and Column total for this spritesheet
    int rows, cols;
};

// Estructura que se compone de los valores necesarios para manejar un sprite junto a sus posibles animaciones, visibilidad y el estado de colisiones.
struct Sprite{
    esat::SpriteHandle image;
    SpriteSheet *sprite_sheet;
    mlib::Vec2 position;
    Collider collider; // Color block + logic
    // ss_row -> SpriteSheet row
    // indiceAnimacion -> SpriteSheet column
    unsigned char ss_row = 0, ss_col = 0;
    bool isVisible;
    bool isActive; //isActive indica si está dispuesto a comprobar colisiones
};

#endif