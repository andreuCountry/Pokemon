#ifndef SPRITES_H
#define SPRITES_H

#include "../structs.h"
#include "../utils/utils.h"

extern SpriteSheet ss_rocket;
extern SpriteSheet ss_rocket_trail;
extern SpriteSheet ss_astronaut;
extern SpriteSheet ss_collectibles;
extern SpriteSheet ss_enemies;
extern SpriteSheet ss_explosion;
extern bool visible_colliders;

void LoadSpriteSheet(const char *path, SpriteSheet *ss, int sprite_w, int sprite_h);
void LoadSpriteSheets();
void ReleaseSpriteSheet(SpriteSheet *ss);
void ReleaseSpriteSheets();
void ReleaseSprite(Sprite *s);
void DrawCollider(Collider collider, bool is_solid, bool remove_border);
void SpriteSetPosition(Sprite *sprite, mlib::Vec2 new_pos);
void SpriteMove(Sprite *sprite, mlib::Vec2 dir_v);
mlib::Vec2 GetSpriteCenter(Sprite s);
mlib::Vec2 GetVecSpriteToSprite(Sprite s1, Sprite s2);
void SpriteUpdate(Sprite *sprite);
void SpriteInit(Sprite *sprite, SpriteSheet *ss);
void NextAnimationSprite(Sprite *sprite);
void PrevAnimationSprite(Sprite *sprite);
void DrawSpriteCustom(Sprite s, bool mirror = 0);
void NextAnimationSprite(Sprite **sprite);
#endif