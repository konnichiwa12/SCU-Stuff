// Name: Dillon Kanai 
// Date: 11/12/20
// Title: Lab8 – read.c
// Description: this code reads the contents of testInput.txt iteratively


int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer [sizeof(int)];
    int i;
    fp = fopen("testInput.txt", "w");
    for (i=0; i<1000; i++){
        sprintf(buffer, "%d\n", rand()%1000);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}

