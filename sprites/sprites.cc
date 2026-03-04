#include <stdlib.h>
#include <stdio.h>
#include "../Lib_Graph/ESAT_rev248/include/esat/sprite.h"
#include "../Lib_Graph/ESAT_rev248/include/esat/draw.h"
#include "../structs.h"

// Sprites cargados
SpriteSheet ss_battle;
SpriteSheet ss_boxbg;
SpriteSheet ss_pokeball;
SpriteSheet ss_red;
SpriteSheet ss_tiles;

bool visible_colliders = false;

void LoadSpriteSheet(const char *path, SpriteSheet *ss, int sprite_w = 20, int sprite_h = 20){
    //Initializes the values
    ss->sprite_sheet_image = esat::SpriteFromFile(path);
    ss->cols = esat::SpriteWidth(ss->sprite_sheet_image)/sprite_w; 
    ss->rows = esat::SpriteHeight(ss->sprite_sheet_image)/sprite_h;
    ss->sprite_w = sprite_w;
    ss->sprite_h = sprite_h;
}

void LoadSpriteSheets(){
    LoadSpriteSheet("./assets/battle.png", &ss_battle);
    LoadSpriteSheet("./assets/boxbg.png", &ss_boxbg);
    LoadSpriteSheet("./assets/pokeball.png", &ss_pokeball,48,72);
    LoadSpriteSheet("./assets/red.png", &ss_red);
    LoadSpriteSheet("./assets/tiles.png", &ss_tiles);
}

void ReleaseSpriteSheet(SpriteSheet *ss){
    esat::SpriteRelease(ss->sprite_sheet_image);
}

void ReleaseSpriteSheets(){
    ReleaseSpriteSheet(&ss_battle);
    ReleaseSpriteSheet(&ss_boxbg);
    ReleaseSpriteSheet(&ss_pokeball);
    ReleaseSpriteSheet(&ss_red);
    ReleaseSpriteSheet(&ss_tiles);
}

void ReleaseSprite(Sprite *s){
    esat::SpriteRelease(s->image);
}

// Draws parameter collider borders
void DrawCollider(Collider collider, bool is_solid = false, bool remove_border = true){
    float *coords = (float*) malloc(sizeof(float)*10);
    *(coords+0) = collider.P1.x;
    *(coords+1) = collider.P1.y;

    *(coords+2) = collider.P1.x;
    *(coords+3) = collider.P2.y;

    *(coords+4) = collider.P2.x;
    *(coords+5) = collider.P2.y;

    *(coords+6) = collider.P2.x;
    *(coords+7) = collider.P1.y;

    *(coords+8) = collider.P1.x;
    *(coords+9) = collider.P1.y;

    if(is_solid){
        if(remove_border){
            esat::DrawSetStrokeColor(0,0,0);
        }
        esat::DrawSolidPath(coords,5);
    }else{
        esat::DrawPath(coords,5);
    }
    free(coords);
}

// NO USAR
// ES SOLO PARA EL SPRITE UPDATE
// SI LO USAIS POR SEPARADO SEGURAMENTE GENERARÁ MEMORY LEAK
// Retrieves the sprite of a SpriteSheet given the SpriteSheet, its Row and its Column as parameter 
esat::SpriteHandle GetSpriteFromSheet(SpriteSheet sprite_sheet, int ss_row, int ss_col){
    esat::SpriteHandle result;
    if(ss_row >= sprite_sheet.rows || ss_col >= sprite_sheet.cols ){
        result = nullptr;
        printf("----LOG ERROR - NOT VALID ROW/COL FROM SPRITESHEET\n");
    }else{
        result = (esat::SubSprite(
            sprite_sheet.sprite_sheet_image,
            sprite_sheet.sprite_w*ss_col,
            sprite_sheet.sprite_h*ss_row,
            sprite_sheet.sprite_w,
            sprite_sheet.sprite_h
        ));
    }
    return result;
}

//Sets sprite position to the one provided as parameter
void SpriteSetPosition(Sprite *sprite, mlib::Vec2 new_pos){
    sprite->position = new_pos;
    sprite->collider.P1 = new_pos;
    sprite->collider.P2 = {
        new_pos.x+(sprite->sprite_sheet->sprite_w), 
        new_pos.y+(sprite->sprite_sheet->sprite_h)
    };
}

//Displaces de position of the sprite by the values of the Vec2 parameter
void SpriteMove(Sprite *sprite, mlib::Vec2 dir_v){
    sprite->position = mlib::SumVec2(sprite->position,dir_v);
    sprite->collider.P1 = mlib::SumVec2(sprite->collider.P1,dir_v);
    sprite->collider.P2 = mlib::SumVec2(sprite->collider.P2,dir_v);
}

mlib::Vec2 GetSpriteCenter(Sprite s){
    return mlib::SumVec2(
        s.position,
        {(s.sprite_sheet->sprite_w)*0.5f, (s.sprite_sheet->sprite_h)*0.5f}
    ); 
}

//Devuelve el vector correspondiente al centro del primer sprite en direccion al centro del segundo
mlib::Vec2 GetVecSpriteToSprite(Sprite s1, Sprite s2){
    return (mlib::SubsVec2(GetSpriteCenter(s2), GetSpriteCenter(s1)));
}


// Dada una estructura SpriteSheet y una estructura Sprite, actualiza la imagen del Sprite en base al SpriteSheet y el tipoAnimacion(Fila) e indiceAnimacion(Columna) que tiene el Sprite asignados.
void SpriteUpdate(Sprite *sprite){
    // Mediante la variable local buffer, se asegura de liberar la imagen previa que tenía asignada el Sprite para prevenir leaks de memoria
    esat::SpriteHandle buffer = sprite->image;
    sprite->image = GetSpriteFromSheet(*(sprite->sprite_sheet), sprite->ss_row, sprite->ss_col);

    if(buffer != NULL){
        esat::SpriteRelease(buffer);
    }
}

void SpriteInit(Sprite *sprite, SpriteSheet *ss){
    sprite->image = nullptr;
    sprite->sprite_sheet = ss;
    sprite->position = {0, 0};
    sprite->collider.P1 = {0, 0};
    sprite->collider.P2 = {(float) ss->sprite_w, (float) ss->sprite_h};
    sprite->ss_row = 0;
    sprite->ss_col = 0;
    sprite->isVisible = true;
    sprite->isActive = true;
}

void NextAnimationSprite(Sprite *sprite){
    // Avanza indice de animación. 
    sprite->ss_col++;
    // Si despues de sumar el indice es mayor o igual a las columnas totales de coordenadas
    // de animacion, lo instancia a 0 para reiniciar la animacion
    if(sprite->ss_col >= sprite->sprite_sheet->cols){
        sprite->ss_col = 0;
    }
}

void NextAnimationSprite(Sprite **sprite){
    // Avanza indice de animación. 
    (*sprite)->ss_col++;
    // Si despues de sumar el indice es mayor o igual a las columnas totales de coordenadas
    // de animacion, lo instancia a 0 para reiniciar la animacion
    if((*sprite)->ss_col >= (*sprite)->sprite_sheet->cols){
        (*sprite)->ss_col = 0;
    }
}

void PrevAnimationSprite(Sprite *sprite){
    // Avanza indice de animación. 
    sprite->ss_col--;
    // Si despues de restar el indice es 255 (-1 en unsigned char)
    // lo instancia al ultimo sprite de la secuencia de animación para reiniciarla
    if(sprite->ss_col == 255){
        sprite->ss_col = (sprite->sprite_sheet->cols)-1;
    }
}

void DrawSpriteCustom(Sprite s, bool mirror = false){
    esat::SpriteTransform st;

    if(s.isVisible){
        if(mirror){
            esat::SpriteTransformInit(&st);
            // Invertir la escala hace que se dibuje a la inversa
            st.scale_x = -1;
            // Por lo tanto la x se debe de ajustar en el caso de que se invierta
            st.x = s.position.x + s.sprite_sheet->sprite_w;
            st.y = s.position.y;
            esat::DrawSprite(s.image, st);
        }else{
            esat::DrawSprite(s.image, s.position.x, s.position.y);
        }
    }

    if(visible_colliders){
        if(s.isActive){
            esat::DrawSetStrokeColor(0,255,0);
        }else{
            esat::DrawSetStrokeColor(255,0,0);
        }

        DrawCollider(s.collider);
    }
}