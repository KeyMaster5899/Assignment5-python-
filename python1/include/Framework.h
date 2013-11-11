#ifndef _FRMWRKWRP_
#define _FRMWRKWRP_
#include "MathLibrary.h"

void			FMWKInitialise(unsigned int width, unsigned int height);
void			FMWKUpdate(Vector3 colour = Vector3());
bool			FMWKWindowOpen();
void			FMWKShutdown();
void			FMWKBackgroundColour(Vector3 colour);

float			getDeltaTime();
int				getTotalTime();
Vector2			getMousePosition();
bool			getMouseDown(int key);
bool			getMouseRel(int key);
bool			getKeyRel(int key);
bool			getKeyDown(int key);	
bool			getKeyDown(const char akey);

unsigned int	SpriteCreate(const char* filepath, unsigned int width, unsigned int height);
void			SpriteMove(unsigned int spriteid, Vector2 position);
void			SpriteMove(unsigned int spriteid, Vector3 position);
void			SpriteRotate(unsigned int spriteid, float rotation);
void			SpriteDraw(unsigned int spriteid);
void			SpriteSetAlpha(const unsigned int sprite_id,float aAlpha);
void			SpriteSetUV(unsigned int spriteid, float un, float vn, float ux, float vx);
void			SpriteDelete(unsigned int spriteid);

void			DrawLine(Vector2 begin, Vector2 end, Vector3 colour);
void			DrawText(const char *text, Vector2 a_position);
void			DrawText(const float num, Vector2 a_position);
void			DrawText(const int num, Vector2 a_position);
void			ResizeText(unsigned int size);
#endif