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

GameScenes scene;

Sprite boxBackground, arrowRight, arrowLeft;

GameState game;

Cell* InitCellsMemory() {
    return (Cell*) malloc (totalCells * sizeof(Cell));
}

void LoadMap1() {
    map1 = fopen("files/map1.txt", "wb");

    // Add all features to send

    /*for (int i = 0; i < 10; i++) {

        int numberInsert = rand()%101;

        fwrite(&numberInsert, sizeof(numberInsert), 1, map1);
    }*/

    fclose(map1);
}

void LoadMap2() {
    map2 = fopen("files/map2.txt", "wb");

    // Add all features to send

    fclose(map2);
}

void PrepareMaps() {
    LoadMap1();
    LoadMap2();
}

void InitSprites() {
    boxBackground.image = esat::SpriteFromFile("./assets/boxbg.jpg");
    boxBackground.isVisible = false;
    boxBackground.isActive = false;

    arrowLeft.image = esat::SpriteFromFile("./assets/flechaI.png");
    arrowRight.image = esat::SpriteFromFile("./assets/flechaD.png");
}

void InitialConfig(Pokemon* pokemons) {
    // empezamos en la pokedex, esto se cambia despues
    scene = BILL_CAGE;

    // inicializar pokemon de enlace
    game.currentPokemon = pokemons + 0;

    // la fuente para los textos de todo
    esat::DrawSetTextFont("./assets/pokemon.ttf");
    esat::DrawSetTextSize(10.0f);
}

Pokemon* InitiateMemoryForPokemons() {
    Pokemon* pokemonData = (Pokemon*) malloc (PokemonNames::TOTAL_POKEMON * sizeof(Pokemon));

    Pokemon* current = pokemonData;
    Pokemon* ante = nullptr;

    // enlazar listas de una manera sistematica con un malloc contando el numero de pokemons totales
    for (int i = 0; i < PokemonNames::TOTAL_POKEMON; i++) {

        current = pokemonData + i;

        current->ante = ante;

        if (i < PokemonNames::TOTAL_POKEMON - 1) {
            current->prox = current + 1;
        } else {
            current->prox = nullptr;
        }

        ante = current;
    }
    
    return pokemonData; 
}

// Recordar que si se quieren meter mas pokemon hacer alguna movida de bbdd o algo,
// para no incrementar el switch como un animal
void AddPokemonData(Pokemon* pokemonsData) {
    for (int i = 0; pokemonsData != nullptr; pokemonsData = pokemonsData->prox, i++) {
        switch (i) {
            case 0:
                pokemonsData->info = ARCANINE;
                pokemonsData->image = esat::SpriteFromFile("./assets/pokemons/arcanine.png");
                pokemonsData->type = FIRE;
            break;
            case 1: 
                pokemonsData->info = TORCHIC;
                pokemonsData->image = esat::SpriteFromFile("./assets/pokemons/torchic.png");
                pokemonsData->type = FIRE;
            break;
            case 2:
                pokemonsData->info = BULBASAUR;
                pokemonsData->image = esat::SpriteFromFile("./assets/pokemons/bulbasaur.png");
                pokemonsData->type = WEED;
            break;
            case 3:
                pokemonsData->info = PIKACHU;
                pokemonsData->image = esat::SpriteFromFile("./assets/pokemons/pikachu.png");
                pokemonsData->type = BOLT;
            break;
            case 4:
                pokemonsData->info = GEODUDE;
                pokemonsData->image = esat::SpriteFromFile("./assets/pokemons/geodude.png");
                pokemonsData->type = EARTH;
            break;
            case 5:
                pokemonsData->info = ONIX;
                pokemonsData->image = esat::SpriteFromFile("./assets/pokemons/onix.png");
                pokemonsData->type = EARTH;
            break;
            case 6:
                pokemonsData->info = PIDGEOT;
                pokemonsData->image = esat::SpriteFromFile("./assets/pokemons/pidgeot.png");
                pokemonsData->type = WIND;
            break;
            case 7:
                pokemonsData->info = SQUIRTLE;
                pokemonsData->image = esat::SpriteFromFile("./assets/pokemons/squirtle.png");
                pokemonsData->type = WATER;
            break;
            case 8:
                pokemonsData->info = EKANS;
                pokemonsData->image = esat::SpriteFromFile("./assets/pokemons/ekans.png");
                pokemonsData->type = POISONOUS;
            break;  
            case 9:
                pokemonsData->info = ARBOK;
                pokemonsData->image = esat::SpriteFromFile("./assets/pokemons/arbok.png");
                pokemonsData->type = POISONOUS;
            break;
        }
    }
}

void ControlsDetectBox(Pokemon* pokemonData) {

    if (pokemonData->prox != nullptr) {
        if (esat::IsSpecialKeyDown(esat::kSpecialKey_Right)) {
            game.currentPokemon =  pokemonData->prox;
            printf("%d", game.currentPokemon->info);
        }
    }
        
    if (pokemonData->ante != nullptr) {
        if (esat::IsSpecialKeyDown(esat::kSpecialKey_Left)) {
            game.currentPokemon = pokemonData->ante;
        }
    }

    if (esat::IsKeyDown('p')) {
        scene = MAP_1;
    }
}

void DrawPokemonInfo(Pokemon* pokemonInfo) {
    esat::DrawText(windowX / 2, 500, "Game over");
}

void DrawInstancePokemons() {
    ControlsDetectBox(game.currentPokemon);

    // Dibujar solo la info del pokemon seleccionado
    esat::DrawSprite(game.currentPokemon->image, windowX / 3, windowY / 3.5f);
    DrawPokemonInfo(game.currentPokemon);
}

void ControlFlow(GameScenes scene, Pokemon* pokemonData) {
    if (scene == BILL_CAGE) {
        DrawInstancePokemons();
    }
}

int esat::main(int argc, char **argv) {

    // inicializar la memoria para los cells
    Cell* dataToSave = InitCellsMemory();
    Pokemon* pokemonsData = InitiateMemoryForPokemons();
    

    esat::WindowInit(windowX, windowY);
    esat::WindowSetMouseVisibility(true);

    InitSprites();
    InitialConfig(pokemonsData);

    AddPokemonData(pokemonsData);

    while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
        last_time = esat::Time();

        esat::DrawBegin();
        esat::DrawClear(0, 0, 0);

        // control de mapeo directo en otro sitio, mover vaya cruck
        if (scene == BILL_CAGE) {
            boxBackground.isVisible = true;
            boxBackground.isActive = true;

            esat::DrawSprite(boxBackground.image, 0, 0);

            if (game.currentPokemon->ante != nullptr) {
                esat::DrawSprite(arrowLeft.image, 10, windowY / 2);
            }

            if (game.currentPokemon->prox != nullptr) {
                esat::DrawSprite(arrowRight.image, windowX - 50, windowY / 2);
            }
        }

        ControlFlow(scene, pokemonsData);

        esat::DrawEnd();

        do { current_time = esat::Time(); }
        while ((current_time - last_time) <= 1000.0 / fps);

        esat::WindowFrame();
    }

    // Chao chao memoria

    free(dataToSave);
    free(pokemonsData);

    esat::WindowDestroy();
    return 0;
}