#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <stdio.h>

typedef struct Cell
{
    int state; //0=dead, 1=alive.
    int alive_neighbor_count;
} Cell;

typedef enum Mode
{
    PLANE, //No edge glued.
    CYLINDER, //One pair of opposite edges glued, both of them pointing the same direction.
    MOBIUS_STRIP, //One pair of opposite edges glued, both of them pointing in the opposite direction.
    TORUS, //Two pairs of opposite edges glued, both pairs glued in the same direction.
    KLEIN_BOTTLE, //Two pairs of opposite edges glued, one pair glued in the same direction and one in the opposite direction.
//    PROJECTIVE_PLANE //Two pairs of opposite edges glued, both pairs glued in the opposite direction.
} Mode;

typedef struct Board
{
    //Board dimensions.
    int width;
    int height;
    //Describes how edge cells adjacency work.
    Mode Mode;
    //Board data.
    Cell *grid;
} Board;

void load_board_from_file(char *file_path,Board *p_Board);
void generate_random_board(Board *p_Board);
void save_board_to_file(FILE *fp,Board *p_Board);
void free_board(Board *p_Board);

#endif // BOARD_H_INCLUDED
