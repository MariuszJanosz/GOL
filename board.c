#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void load_board_from_file(char *file_path,Board *p_Board)
{
    //Opens input file for reading.
    FILE *fp;
    if(!(fp=fopen(file_path,"r")))
    {
        printf("Couldn't open file %s!",file_path);
        exit(1);
    }

    //Reads the board dimensions from the file.
    fscanf(fp,"%d",&p_Board->width);
    fscanf(fp,"%d",&p_Board->height);

    //Reads the board mode from the file.
    char str[64];
    fscanf(fp,"%s",str);
    if(strcmp(str,"PLANE")==0)
    {
        p_Board->Mode=PLANE;
    }
    else if(strcmp(str,"CYLINDER")==0)
    {
        p_Board->Mode=CYLINDER;
    }
    else if(strcmp(str,"MOBIUS_STRIP")==0)
    {
        p_Board->Mode=MOBIUS_STRIP;
    }
    else if(strcmp(str,"TORUS")==0)
    {
        p_Board->Mode=TORUS;
    }
    else if(strcmp(str,"KLEIN_BOTTLE")==0)
    {
        p_Board->Mode=KLEIN_BOTTLE;
    }
//    else if(strcmp(str,"PROJECTIVE_PLANE")==0)
//    {
//        p_Board->Mode=PROJECTIVE_PLANE;
//    }
    else
    {
        printf("Invalid mode!");
        exit(1);
    }

    //Allocates memory for the grid.
    if(!(p_Board->grid=malloc(p_Board->width*p_Board->height*sizeof(Cell))))
    {
        printf("Couldn't allocate memory for the grid!");
        exit(1);
    }

    //Initializes the grid by data form the file.
    for(int i=0;i<p_Board->height;i++)
    {
        for(int j=0;j<p_Board->width;j++)
        {
            fscanf(fp,"%d",&p_Board->grid[p_Board->width*i+j].state);
        }
    }

    //Closes file.
    fclose(fp);
}

void generate_random_board(Board *p_Board)
{
    //Enter board dimensions.
    printf("Enter board width: ");
    scanf("%d",&p_Board->width);
    printf("Enter board height: ");
    scanf("%d",&p_Board->height);

    //Allocates memory for the grid.
    if(!(p_Board->grid=malloc(p_Board->width*p_Board->height*sizeof(Cell))))
    {
        printf("Couldn't allocate memory for the grid!");
        exit(1);
    }

    //Enter board mode.
    printf("Board modes:\n");
    printf("1. Plane\n");
    printf("2. Cylinder\n");
    printf("3. Mobius strip\n");
    printf("4. Torus\n");
    printf("5. Klein bottle\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        p_Board->Mode=PLANE;
        break;
    case 2:
        p_Board->Mode=CYLINDER;
        break;
    case 3:
        p_Board->Mode=MOBIUS_STRIP;
        break;
    case 4:
        p_Board->Mode=TORUS;
        break;
    case 5:
        p_Board->Mode=KLEIN_BOTTLE;
        break;
    default:
        printf("Invalid choice!");
        exit(1);
    }

    printf("Approximately what percentage of cells would you like to be alive?\n");
    printf("Enter a number from 0 to 100: ");
    int density;
    scanf("%d",&density);
    if(density<0||density>100)
    {
        printf ("Invalid choice!");
        exit(1);
    }

    //Initializes the grid by random data.
    srand(time(NULL));
    for(int i=0;i<p_Board->height;i++)
    {
        for(int j=0;j<p_Board->width;j++)
        {
            if(rand()%100<density)
            {
                p_Board->grid[p_Board->width*i+j].state=1;
            }
            else
            {
                p_Board->grid[p_Board->width*i+j].state=0;
            }
        }
    }
}

void save_board_to_file(FILE *fp,Board *p_Board)
{
    for(int i=0;i<p_Board->height;i++)
    {
        for(int j=0;j<p_Board->width;j++)
        {
            fprintf(fp,"%d",p_Board->grid[p_Board->width*i+j].state);
            if(j!=p_Board->width-1) fprintf(fp," ");
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
}

void free_board(Board *p_Board)
{
    free(p_Board->grid);
}
