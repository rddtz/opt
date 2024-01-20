#include <stdio.h>
#include <string.h>

#include "opt.h"

int main(int argc, char *argv[]){

    //Criando um programa para fazer a ou b

    char sabores [2][20] = {"\0"};
    char adress[50] = "\0";
    int status;
    int c;

    while(!optHasError && !(status = search_opt("c,s:2,c:1", argc, argv))){
        switch(opt.code[0]){
            case 'c':
                c = 1;
                break;
            case 'e':
                argcpy(adress, 0, argv, argc);
                break;
            case 's':
                for(int i = 0; i < opt.argc; i++){
                    argcpy(sabores[i], i, argv, argc);
                }
                break;
        }
        remove_args(&argc, argv);
    }

    if(optHasError){
        printf("\n%s\n", optError);
        return optHasError;
    }


    if(c){
        printf("\n- option C activated");
    }

    if(*adress){
        printf("\nA- Do something in: %s", adress);
    }

    if(sabores[0][0]){
        printf("\nFlavours:\n");
        for(int i = 0; i < 2; i++){
            printf("- %s\n", sabores[i]);
        }
    }

    printf("\n");

    return 0;

}


