#ifndef OPT_H_INCLUDED
#define OPT_H_INCLUDED

#define MAX_OPTL 1000 //Max Argument Length for a Option
#define MAX_ERROR 200 //Max error size message

#include <string.h>

//Struct to store the data from options
typedef struct option {
    int place; //Where in argv this options appears
    int argc; //How many arguments the option have (designed by string_opt)
    char code[8]; //String code for the option, ex: b for -b (designed by string_opt)

} OPTION;

//Variables
char optvalue[MAX_OPTL];

char optError[MAX_ERROR]; //If there is a error parsing the options, u can print the
                          //error messege using this string
short optHasError; //flag to see if there is a error in the option handling process

extern OPTION opt; //Option being handled at the moment
//--------------------


/*search_opt:
  This function is used to get the next (if there are) option in the argv items and
change the global OPTION variable, so u just need to access it after using the
search_opt to know its info.
  This function will return status depending on how the operation goes, u can use it
together with the optHasError variable as the condition to the option parsing loop.*/
short search_opt(char string_opt[], int argc, char *argv[]);
/*                      ^ the string_opt is a string with the following formatation:
                                              "c,s:2,e:1"
                          the options are designed by a char and separated by a comma (,)
                          u can use the : character to design that the option has arguments
                          and a number after to tell how many arguments it will have, in this
                          case, s has 2 arguments and e has 1, c don't have argumetns.
*/
//-------------------------------------------------

//get_argc:
//This funcion receives the string_opt and the argv item where a option appears and
//returns the number of arguments that the function is designed to have;
//The error that might happen with this functions come from bad formating of string_opt
int get_argc(char argv[], char string_opt[]);
    //A item in argv ^         ^ the string_opt that contains the options pattern
//-------------------------------------------------

/* remove_args:
 This function receives a pointer to argc and argv, and works using the actual option
in the opt global variable to remove the arguments and call to that option in the argv matrix */
void remove_args(int *argc, char *argv[]);
//----------------------------------

/* get_argv:
 Function used by argcpy to copy a argument option from ARGV to optvalue, it uses the global
OPTION opt variable to get the place where its options are, but this function doesn't have
any error handling method, so isn't recommended to be used alone, even if u can.*/
void get_argv(char *argv[], int p);

/*argcpy:
 Copy the value from the pº argument of the actual option in opt to value string passed as
argument. As said, the p is the argument u wanna get, so if u want the first argument, u must
set the p as 0. If the p is greater than the arguments designed to the options, it will
return a -2 error, u can see the error with the optError string.
*/
short argcpy(char value[], int p, char *argv[], int argc);

/*-------------------------------
//USE RECOMENDATION AND TIPS:

1: As the search_opt function just gets the next option, u can use it out of a loop, but its
recommended to use it inside a while to parse all options ate once, the while conditions might be:

                this condition must come first or it will ignore the errors
                  |
                  V
          while(!optHasError && !(status = search_opt("c,s:e,e:1", argc, argv))){ //status must be declared as int
                 ...switch, if or whatever u want here;
                 remove_args(&argc, argv);
          }

 This way it will stop when get a error or when u parse all the options.
 WARNING: remenber to always use the remove_args function on the end of a iteration or it will
 get a infinite loop where u always get the same option with search_opt.

 2: Use the optHasError and optError to see what is wrong, if you are using the while loop
 before said, u can use the following code segment right outside it to see if there are any errors:

                    if(optHasError){
                        printf("\n%s\n", optError);
                        return optHasError;
                    }

  this way, if your while stops prematurely by a error, u can see what is going on.

 3: The argcpy just get 1 argument at once, so if u wanna to fill a matrix with the arguments
 u need to put it inside a for loop, remember that u can directly use the OPTION opt variable,
 so u can use it here to iterate between the args:

            for(int i = 0; i < opt.argc; i++){
                    argcpy(my_arguments_matrix[i], i, argv, argc);
            }

*/

#endif // OPT_H_INCLUDED
