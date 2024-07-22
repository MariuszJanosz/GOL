#include "game.h"
#include "board.h"

typedef struct neighbors_indexes
{
    int upper_left;
    int upper;
    int upper_right;
    int left;
    int right;
    int bottom_left;
    int bottom;
    int bottom_right;
} Indexes;

Indexes neighbors_indexes(int x,int y,int width,int height, Mode Mode)
{
    //Initializes result, -1 means there is no such neighbor.
    Indexes result;
    result.upper_left=width*(y-1)+(x-1);
    result.upper=width*(y-1)+(x);
    result.upper_right=width*(y-1)+(x+1);
    result.left=width*(y)+(x-1);
    result.right=width*(y)+(x+1);
    result.bottom_left=width*(y+1)+(x-1);
    result.bottom=width*(y+1)+(x);
    result.bottom_right=width*(y+1)+(x+1);

    switch (Mode)
    {
    case PLANE:
        if(x==0)
        {
            result.upper_left=-1;
            result.left=-1;
            result.bottom_left=-1;
        }
        if(x==width-1)
        {
            result.upper_right=-1;
            result.right=-1;
            result.bottom_right=-1;
        }
        if(y==0)
        {
            result.upper_left=-1;
            result.upper=-1;
            result.upper_right=-1;
        }
        if(y==height-1)
        {
            result.bottom_left=-1;
            result.bottom=-1;
            result.bottom_right=-1;
        }
        break;
    case CYLINDER:
        if(x==0)
        {
            result.upper_left=width*(y-1)+(width-1);
            result.left=width*(y)+(width-1);
            result.bottom_left=width*(y+1)+(width-1);
        }
        if(x==width-1)
        {
            result.upper_right=width*(y-1);
            result.right=width*(y);
            result.bottom_right=width*(y+1);
        }
        if(y==0)
        {
            result.upper_left=-1;
            result.upper=-1;
            result.upper_right=-1;
        }
        if(y==height-1)
        {
            result.bottom_left=-1;
            result.bottom=-1;
            result.bottom_right=-1;
        }
        break;
    case MOBIUS_STRIP:
        if(x==0)
        {
            result.upper_left=width*(height-1-(y-1))+(width-1);
            result.left=width*(height-1-(y))+(width-1);
            result.bottom_left=width*(height-1-(y+1))+(width-1);
        }
        if(x==width-1)
        {
            result.upper_right=width*(height-1-(y-1));
            result.right=width*(height-1-(y));
            result.bottom_right=width*(height-1-(y+1));
        }
        if(y==0)
        {
            result.upper_left=-1;
            result.upper=-1;
            result.upper_right=-1;
        }
        if(y==height-1)
        {
            result.bottom_left=-1;
            result.bottom=-1;
            result.bottom_right=-1;
        }
        break;
    case TORUS:
        if(x==0)
        {
            result.upper_left=width*(y-1)+(width-1);
            result.left=width*(y)+(width-1);
            result.bottom_left=width*(y+1)+(width-1);
        }
        if(x==width-1)
        {
            result.upper_right=width*(y-1);
            result.right=width*(y);
            result.bottom_right=width*(y+1);
        }
        if(y==0)
        {
            result.upper_left=width*(height-1)+(x-1);
            result.upper=width*(height-1)+(x);
            result.upper_right=width*(height-1)+(x+1);
        }
        if(y==height-1)
        {
            result.bottom_left=(x-1);
            result.bottom=(x);
            result.bottom_right=(x+1);
        }
        if(x==0&&y==0)
        {
            result.upper_left=width*(height-1)+(width-1);
        }
        if(x==0&&y==height-1)
        {
            result.bottom_left=(width-1);
        }
        if(x==width-1&&y==0)
        {
            result.upper_right=width*(height-1);
        }
        if(x==width-1&&y==height-1)
        {
            result.bottom_right=0;
        }
        break;
    case KLEIN_BOTTLE:
        if(x==0)
        {
            result.upper_left=width*(height-1-(y-1))+(width-1);
            result.left=width*(height-1-(y))+(width-1);
            result.bottom_left=width*(height-1-(y+1))+(width-1);
        }
        if(x==width-1)
        {
            result.upper_right=width*(height-1-(y-1));
            result.right=width*(height-1-(y));
            result.bottom_right=width*(height-1-(y+1));
        }
        if(y==0)
        {
            result.upper_left=width*(height-1)+(x-1);
            result.upper=width*(height-1)+(x);
            result.upper_right=width*(height-1)+(x+1);
        }
        if(y==height-1)
        {
            result.bottom_left=(x-1);
            result.bottom=(x);
            result.bottom_right=(x+1);
        }
        if(x==0&&y==0)
        {
            result.upper_left=(width-1);
        }
        if(x==0&&y==height-1)
        {
            result.bottom_left=width*(height-1-0)+(width-1);
        }
        if(x==width-1&&y==0)
        {
            result.upper_right=0;
        }
        if(x==width-1&&y==height-1)
        {
            result.bottom_right=width*(height-1)+0;
        }
        break;
//    case PROJECTIVE_PLANE: //On projective plane cannot define neighborhood properly.
//        if(x==0)
//        {
//            result.upper_left=width*(height-1-(y-1))+(width-1);
//            result.left=width*(height-1-(y))+(width-1);
//            result.bottom_left=width*(height-1-(y+1))+(width-1);
//        }
//        if(x==width-1)
//        {
//            result.upper_right=width*(height-1-(y-1));
//            result.right=width*(height-1-(y));
//            result.bottom_right=width*(height-1-(y+1));
//        }
//        if(y==0)
//        {
//            result.upper_left=width*(height-1)+(width-1-(x-1));
//            result.upper=width*(height-1)+(width-1-(x));
//            result.upper_right=width*(height-1)+(width-1-(x+1));
//        }
//        if(y==height-1)
//        {
//            result.bottom_left=(width-1-(x-1));
//            result.bottom=(width-1-(x));
//            result.bottom_right=(width-1-(x+1));
//        }
//        if(x==0&&y==0)
//        {
//            result.upper_left=0;
//        }
//        if(x==0&&y==height-1)
//        {
//            result.bottom_left=width*(height-1-0)+0;
//        }
//        if(x==width-1&&y==0)
//        {
//            result.upper_right=width*0+(width-1);
//        }
//        if(x==width-1&&y==height-1)
//        {
//            result.bottom_right=width*(height-1)+(width-1);
//        }
//        break;
    }
    return result;
}

void count_alive_neighbors(Board *p_Board)
{
    for(int i=0;i<p_Board->height;i++)
    {
        for(int j=0;j<p_Board->width;j++)
        {
            p_Board->grid[p_Board->width*i+j].alive_neighbor_count=0;
            Indexes neighbors=neighbors_indexes(j,i,p_Board->width,p_Board->height,p_Board->Mode);
            if(neighbors.upper_left!=-1)
            {
                p_Board->grid[p_Board->width*i+j].alive_neighbor_count+=p_Board->grid[neighbors.upper_left].state;
            }
            if(neighbors.upper!=-1)
            {
                p_Board->grid[p_Board->width*i+j].alive_neighbor_count+=p_Board->grid[neighbors.upper].state;
            }
            if(neighbors.upper_right!=-1)
            {
                p_Board->grid[p_Board->width*i+j].alive_neighbor_count+=p_Board->grid[neighbors.upper_right].state;
            }
            if(neighbors.left!=-1)
            {
                p_Board->grid[p_Board->width*i+j].alive_neighbor_count+=p_Board->grid[neighbors.left].state;
            }
            if(neighbors.right!=-1)
            {
                p_Board->grid[p_Board->width*i+j].alive_neighbor_count+=p_Board->grid[neighbors.right].state;
            }
            if(neighbors.bottom_left!=-1)
            {
                p_Board->grid[p_Board->width*i+j].alive_neighbor_count+=p_Board->grid[neighbors.bottom_left].state;
            }
            if(neighbors.bottom!=-1)
            {
                p_Board->grid[p_Board->width*i+j].alive_neighbor_count+=p_Board->grid[neighbors.bottom].state;
            }
            if(neighbors.bottom_right!=-1)
            {
                p_Board->grid[p_Board->width*i+j].alive_neighbor_count+=p_Board->grid[neighbors.bottom_right].state;
            }
        }
    }
}

void generate_next_generation(Board *p_Board)
{
    //Generates next generation.
    for(int i=0;i<p_Board->height;i++)
    {
        for(int j=0;j<p_Board->width;j++)
        {
            if(p_Board->grid[p_Board->width*i+j].state==1)
            {
                if(p_Board->grid[p_Board->width*i+j].alive_neighbor_count<2||p_Board->grid[p_Board->width*i+j].alive_neighbor_count>3)
                {
                    p_Board->grid[p_Board->width*i+j].state=0; //Over and under populated living cells are dying.
                }
            }
            else
            {
                if(p_Board->grid[p_Board->width*i+j].alive_neighbor_count==3)
                {
                    p_Board->grid[p_Board->width*i+j].state=1; //Dead cells with exactly 3 living neighbors become alive.
                }
            }
        }
    }
    count_alive_neighbors(p_Board);
}
