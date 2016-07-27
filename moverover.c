#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s{
    int x;
    int y;
    char cardinal;
} state;

const char cardinals[4] = "NESW";

void turn(state *s, char side) {
    char *cardinal = strchr(cardinals, s->cardinal);
    if(side == 'L') {
        // se for o primeiro da string (North)
        if(cardinal == cardinals) { 
            // pego o último da string (West)
            s->cardinal = cardinals[3];
        } else {
            // se não pego o anterior na string
            s->cardinal = *(--cardinal);
        }
    } else {
        // se for o último da string (West)
        if(cardinal == (cardinals+3)) {
            // pego o primeiro da string (North)
            s->cardinal = cardinals[0];
        } else {
            // se não pego o próximo na string
            s->cardinal = *(++cardinal);
        }
    }
}

void move(state *s, unsigned int width, unsigned int height) {
    switch(s->cardinal) {
        case 'N':
            if(s->y < height) {
                s->y++;
                return;
            }
            break;
        case 'E':
            if(s->x < width) {
                s->x++;
                return;
            }
            break;
        case 'S':
            if(s->y > 0) {
                s->y--;
                return;
            }
            break;
        case 'W':
            if(s->x > 0) {
                s->x--;
                return;
            }
    };
    puts("A movement was ignored to avoid the rover leaving the plateau");
}

void moveRover(state *roverState, char *movements, unsigned int width, unsigned int height) {
    // loop pela string, char by char
    char movement = movements[0];
    do{
        if(movement == 'M') {
            move(roverState, width, height);
        } else {
            turn(roverState, movement);
        }
    } while(movement = *(++movements));
}

void validate(char *outputFileName) {
    // a ideia aqui é ler arquivos output e de teste ao mesmo tempo, comparando-os linha a linha
    FILE *output, *test;
    char outputStr[5], testStr[5];
    char ok = 1;
    int line = 0;

    puts("\n--- STARTING TEST ROUTINE ---\n");

    if((output = fopen(outputFileName, "r")) == 0) {
        perror("Error opening outputted file");
        return;
    }

    if((test = fopen("test/output.txt", "r")) == 0) {
        perror("Error opening test output file");
        return;
    }

    while(!(feof(output) || feof(test))) {
        line++;
        fgets(outputStr, 6, output);
        fgets(testStr, 6, test);
        if(strcmp(outputStr, testStr)) {
            ok = '\0';
            printf("Error found on rover %i\n", line);
        }
        if(!feof(output)) {
            fscanf(output, "\n");
        }
        if(!feof(test)) {
            fscanf(test, "\n");
        }
    }

    fclose(output);
    fclose(test);

    if(ok) {
        puts("Test completed without errors\n");
        return;
    }
    puts("Test completed with errors\n");
}

int main(int argc, char *argv[]) {
    char inputFileName[4096] = "input.txt",
         outputFileName[4096] = "output.txt",
         testing = '\0',
         movements[32767];
    FILE *input, 
         *output;
    state roverState;
    unsigned int width, 
                 height, 
                 r = 0;

    // tratando linha de comando
    
    if(argc >= 2) {
        if(strcmp(argv[1], "-t") == 0) {
            testing = 1;
            strcpy(inputFileName, "test/input.txt");
        } else {
            strcpy(inputFileName, argv[1]);
        }
        if(argc >= 3) {
            strcpy(outputFileName, argv[2]);
        }
    }

    if((input = fopen(inputFileName, "r")) == 0) {
        perror("Error opening input file");
        getch();
        return 0;
    }

    if((output = fopen(outputFileName, "w")) == 0) {
        perror("Error opening output file");
        getch();
        return 0;
    }

    // pego a primeira linha do arquivo
    // coordenadas x,y máximas
    fscanf(input, "%i %i", &width, &height);
    
    while(!feof(input)) {
        // loop pelo arquivo de input
        fscanf(input, "\n");
        if(feof(input)) {
            break;
        }

        printf("\n Starting movements for rover #%i\n", ++r);
        fscanf(input, "%i %i %c\n%s", &(roverState.x), &(roverState.y), &(roverState.cardinal), movements);        
        moveRover(&roverState, movements, width, height);
        fprintf(output, "%i %i %c\n", roverState.x, roverState.y, roverState.cardinal);
    }    

    fclose(input);
    fclose(output);

    if(testing) {
        validate(outputFileName);
    }

    printf("All rovers have been moved.\nOutput file: %s\n", outputFileName);

    getch();
    return 1;
}