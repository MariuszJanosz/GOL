#include "board.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    //Creates board.
    Board Board;

    //Menu
    printf("1. Load an initial state from a file.\n");
    printf("2. Generate a random initial state.\n");
    printf("Enter your choice: ");
    char choice;
    choice=getchar();
    //Clears stdin buffer.
    char ch;
    if(choice!='\n')
    {
        while(ch=getchar()!='\n');
    }

    if(choice=='1')
    {
        //Gets the input file path.
        printf("Enter a path to a file with an initial state: ");
        char file_path[128];
        scanf("%s",file_path);

        //Loads board from the file.
        load_board_from_file(file_path,&Board);
        count_alive_neighbors(&Board);
    }
    else if(choice=='2')
    {
        generate_random_board(&Board);
        count_alive_neighbors(&Board);
    }
    else
    {
        printf("Invalid choice!");
        exit(1);
    }

    //Options.
    int how_many_generations;
    printf("How many generations would you like to generate? ");
    scanf("%d",&how_many_generations);
    char result_file_name[64];
    printf("How would you like to name output file? ");
    scanf("%s",result_file_name);

    //Save result to the file.
    FILE *fp;
    if(!(fp=fopen(result_file_name,"w")))
    {
        printf("Couldn't create result file!");
        exit(1);
    }

    //Saves board info.
    fprintf(fp,"%d %d ",Board.width,Board.height);
    switch (Board.Mode)
    {
    case PLANE:
        fprintf(fp,"%s\n","PLANE");
        break;
    case CYLINDER:
        fprintf(fp,"%s\n","CYLINDER");
        break;
    case MOBIUS_STRIP:
        fprintf(fp,"%s\n","MOBIUS_STRIP");
        break;
    case TORUS:
        fprintf(fp,"%s\n","TORUS");
        break;
    case KLEIN_BOTTLE:
        fprintf(fp,"%s\n","KLEIN_BOTTLE");
        break;
    }

    //Saves initial state.
    fprintf(fp,"Generation 0\n");
    save_board_to_file(fp,&Board);

    for(int index=0;index<how_many_generations;index++)
    {
        generate_next_generation(&Board);

        fprintf(fp,"Generation %d\n",index+1);
        save_board_to_file(fp,&Board);
    }

    free_board(&Board);

    return 0;
}
