#include "global.h"
//arguments: character pointer file
//return: void
//function: access each line in the binary file, convert it, and printf them
void ReadBfile(char *file){
        FILE *fp;
        NODE p;
        pthread_mutex_lock(&mutex);
        if ((fp = fopen(file, "rb")) == NULL){
                printf("Cannot open binary file\n");
                return;
        }
        while(fread(&p, sizeof(NODE), 1, fp)>0){
                printf("%s, %d\n", p.names, p.size);
        }
        fclose(fp);
        pthread_mutex_unlock(&mutex);
        return;
}
//argument: void pointer bname
//return: Null
//function: run in a thread; save all items in the list to a binary file every 15 seconds
void* AutoSave(void *bname){
        char *fname = (char*)bname;
        FILE *fp;
        NODE *p;
        while (1){
                sleep(15);
                pthread_mutex_lock(&mutex);
                printf("Autosaving. Do not insert or remove\n");
                fp = fopen(fname, "wb");
                if(fp==NULL){
                        pthread_mutex_unlock(&mutex);
                        return NULL;
                }
                for(int i = 0; i < 4; i++){
                        p = stuff[i].first;
                        while(p != NULL){
                                fwrite(p, sizeof(NODE), 1, fp);
                                p = p->next;
                        }
                }
                fclose(fp);
                printf("Autosaving complete\n");
                pthread_mutex_unlock(&mutex);
        }
        return NULL;
}

//Arguemtns: A char pointer that points a string with the file name
//return: void
//function: receive info from the file
void Readfile(char *file, int k){
        FILE *fp;
	char *q;
	char string[50];
        NODE *p;
        char s[] = " ";
        int d = 0;
        if ((fp = fopen(file, "r"))==NULL){
                printf("Cannot open file\n");
                return;
        }
        fseek(fp, 42, SEEK_SET);
        while (fgets(string, 50, fp)!=NULL){
		q = string;
		while(*q!='\0'){
			*q^=k;
			q++;
		}
		sscanf(string, "%s\t\t%d\n", s, &d);
                Insert(s, d);
        }
        fclose(fp);
        return;
}

//Arguemtns: A char pointer that points a string with the file name
//return: void
//function: orint info to the file
void Writefile(char *file, int k){
        FILE *fp;
	char string[50];
	char *q;
        char FL[] = "Name\t\tGroup Size\n";
        char SL[]= "________________________\n";
        if ((fp = fopen(file, "w"))==NULL){
                printf("Cannot open file\n");
                return;
        }
        fprintf(fp, "%s\n%s\n", FL, SL);
        NODE *p;
        pthread_mutex_lock(&mutex);
        for (int x = 0; x < 4; x++){
                p = stuff[x].first;
                while (p != NULL){
			sprintf(string, "%s\t\t%d\n", p->names, p->size);
			q= string;
			while (*q != '\0'){
				*q ^= k;
				q++;
			}
                       	fprintf(fp, "%s\n", string);
                       	p=p->next;
                }
        }
        pthread_mutex_unlock(&mutex);
        fclose(fp);
        return;
}
