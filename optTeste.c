#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

    char string_opt[] = "c,s:2,e:1";
    char av[] = "dhaudiw";

    char teste[100];
    strcpy(teste, strstr(string_opt, av+1) - 1);

    printf("%c", (strstr(string_opt, av+1) - 1)[0]);

    return 0;
}

