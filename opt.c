#include "opt.h"

OPTION opt = {0, 0, "\0"}; //Initializing the global option struct

//Main Function, used to see if there are options.
short search_opt(char string_opt[], int ac, char *av[]){

    optHasError = 0;
    strcpy(optvalue, "\0"); //Clean the past opt argument
    strcpy(optError, "\0");

    //Go through the argv matrix searching for options occurrences
    for(int i = 0; i < ac; i++){
        if(av[i][0] == '-'){
                   //Exists                              isn't a argument of [char]:                      isn't ':'                     ins't ','
            if((strstr(string_opt, av[i]+1)) && (strstr(string_opt, av[i]+1) - 1)[0] != ':' && strstr(string_opt, av[i]+1)[0] != ':' && strstr(string_opt, av[i]+1)[0] != ','){ //See if it is a valid options

                strcpy(opt.code, av[i]+1); //Options have just 1 letter for now
                opt.place = i;
                opt.argc = get_argc(av[i] + 1, string_opt);
                if(opt.argc == -1){
                    return -1;
                }
                // ^ Get how much arguments the option is designed to has

                return 0; //Zero is everything Ok
            }
            else {
                strcpy(optError, "Error search_opt -1: Option -# didn't exists.");
                optError[29] = av[i][1];
                optHasError = -1;
                return -1;
            }
        }
    }

    strcpy(optError, "Ending search_opt with status code -2: No more options.");
    return -2;
}

short argcpy(char value[], int q, char *argv[], int argc){

    q++;
    int tamanho = strlen(argv[opt.place + 1]);

    if(tamanho > MAX_OPTL) {
        strcpy(optError, "Error argcpy -1: Argument size exceeds MAX_OPTL.");
        optHasError = -1;
        return -1;
    }

    if(q > opt.argc) {
        strcpy(optError, "Error argcpy -2: Option -# has only # arguments, but trying to find argument #.");
        optError[25] = opt.code[0];
        optError[36] = opt.argc + '0';
        optError[77] = q + '0';
        optHasError = -2;
        return -2;
    }

    if(argc - 1 < opt.place + q){
        strcpy(optError, "Error argcpy -3: Option -# needs # arguments but find ARGV end.");
        optError[25] = opt.code[0];
        optError[33] = opt.argc + '0';
        optHasError = -3;
        return -3;
    }


    get_argv(argv, q);
    strcpy(value, optvalue);

    return 0;

}

void get_argv(char *argv[], int q){

    strcpy(optvalue, argv[opt.place + q]);
    return;

}


int get_argc(char av[], char string_opt[]){

    char *where = strstr(string_opt, av);

    if(where[1] == ':'){
        if(strchr("0123456789", where[2])){
                return where[2] - '0';
        } else {
            strcpy(optError, "Error get_argc -1: Expects to find a number after \":\" but find \"#\" in string_opt.");
            optError[64] = where[2];
            optHasError = -1;
        }
    }
    return 0;
}

void remove_args(int *ac, char *av[]){

    int i;
    int qua = opt.argc + 1;
    int pos = opt.place;

    for(int j = 0; j < qua; j++){ //iterates for remove the arguments and call of option
        if(*ac - 1 >= pos){ //if isn't the end of ARGV
            for(i = pos; i < *ac - 1; i++){
                strcpy(av[i], av[i+1]); // moves all 1 for left and overwrite what we want to delete
            }
            strcpy(av[i], "\0"); //clean the end of ARGV
            *ac--; //and match argc with the real number ARGV items
        } else {
            return;
        }
    }
    return;
}
