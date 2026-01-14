/* AVIS FILE: dx_textures.c
   DESCRIPTION: Texture stub implementation for Cyborg KB
   AUTHOR: CGPT / MercWar
   PURPOSE: Simulate textures in screen saver
   DATE: 2026-01-14
   TAGS: #dx #texture #avis
*/

#include <windows.h>
#include <stdlib.h>
#include "dx_textures.h"

/* AVIS: Load a texture (stub just allocates struct) */
Texture* LoadTexture(const char* filename)
{
    Texture* tex = (Texture*)malloc(sizeof(Texture));
    tex->name = filename;
    tex->width = 1920;   /* AVIS: placeholder resolution */
    tex->height = 1080;
    tex->pixels = NULL;

    char buf[256];
    wsprintf(buf, "LoadTexture Stub: %s", filename);
    MessageBox(NULL, buf, "AVIS Texture", MB_OK);

    return tex;
}

/* AVIS: Free a texture */
void FreeTexture(Texture* tex)
{
    if(tex) free(tex);
    MessageBox(NULL, "FreeTexture Stub Called", "AVIS Texture", MB_OK);
}

/* AVIS: Draw full-screen texture stub */
void DrawTextureFullScreen(Texture* tex)
{
    char buf[256];
    wsprintf(buf, "DrawTextureFullScreen Stub: %s", tex ? tex->name : "NULL");
    MessageBox(NULL, buf, "AVIS Texture", MB_OK);
}
