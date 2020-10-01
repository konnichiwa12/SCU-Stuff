#include "global.h"
LIST  stuff[4] = {{NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL}};
pthread_mutex_t mutex;
//arguments: how many arguments there are (including ./a.out) and the normal and binary file name (after ./a.out)
//return: an int (0 only, to quit)
//Main function, loop forever to accept commands and call functions based on commands(1 to call Insert(), 2 to call Remove(), 3 to call showList(), 4 to search for a size, 5 to show a list backwards, 6 to show all names backwards, and 7 to print contents of the binary file)

int main(int argc, char *argv[]){
        int key = atoi(argv[3]);
	if (argc < 4){
                printf("The file name(s) is missing\n");
                return 0;
        }
        else if (argc > 6){
                printf("Too many inputs\n");
                return 0;
        }
        Readfile(argv[1], key);
        pthread_t thread;
	char name[10];
        int number;
        int quitvariable = 1;
        int command = 0;
        pthread_mutex_init(&mutex, NULL);
        pthread_create(&thread, NULL, AutoSave, (void *)argv[2]);
        for(;;){
                printf("Please put in one of the following commands: \n1 to insert \n2 to remove \n3 to show list \n4 to Search sizes\n5 to show each list backwards\n6 to show all names backwards\n7 to show contents of binary list\n0 to quit\n\n");
                scanf("%d", &command);
                if (command == 1){
                        printf("What is your name? Put in up to 10 characters.\n");
                        scanf("%s", name);
                        if (searchCopies(name)==1){
                                printf("There is already a group with that name\n");
                                continue;
                        }
                        else{
                                printf("What is the size of your group?\n");
                                scanf("%d", &number);
                                Insert(name, number);
                        }
                }
                else if(command == 2){
                        Remove();
                }
                else if (command == 3){
                        showlist();
                }
                else if (command == 0){
                        NODE *p;
                        Writefile(argv[1], key);
                        quitarrays();
                        pthread_cancel(thread);
                        return 0;
                }
                else if (command == 4){
                        SearchSize();
                }
                else if (command == 5){
                        recursearrays();
                }
                else if (command == 6){
                        recursearraysname();
                }
                else if (command == 7){
                        ReadBfile(argv[2]);
                }
                else{
                        printf("That is not one of the choices.\n");
                }
        }
}
