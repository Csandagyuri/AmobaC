#ifndef BEMENET_H_INCLUDED
#define BEMENET_H_INCLUDED

bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer);
int billentyuzetrol_hossz(void);
void eger_koordinata( int *x, int *y, bool *quit);

#endif // BEMENET_H_INCLUDED
