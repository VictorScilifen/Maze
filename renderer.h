#ifndef RENDERER_H
#define RENDERER_H

#include <graphics.h>
#include "player.h"
#include "config.h"

void InitRenderer();
void RenderCeiling();
void RenderFloor();
void Render2DWalls(Player player, int** world);


#endif // RENDERER_H