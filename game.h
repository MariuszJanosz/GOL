#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "board.h"

void count_alive_neighbors(Board *p_Board);
void generate_next_generation(Board *p_Board);

#endif // GAME_H_INCLUDED
