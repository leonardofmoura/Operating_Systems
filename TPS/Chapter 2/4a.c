#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_NAME_LEN    50
#define MAX_GRADE_LEN   2


int main() {
    char name[MAX_NAME_LEN];
    char grade[MAX_GRADE_LEN];
    char space = ' ';
    char new_line = '\n';

    int grade_file = open("grades.txt",O_WRONLY | O_APPEND);

    while(1) {
        //clears both arrays
        memset(name,0,sizeof(name));
        memset(grade,0,sizeof(grade));

        printf("Name of the student(type \"exit\" to exit)\n>>");
        scanf("%s",name);  

        if (!strcmp(name,"exit")) { //breaks if the stings are equal
            break;
        }

        //saves in the textfile grades.txt
        for (int i = 0; i < MAX_NAME_LEN; i++) {
            if (name[i] == 0) {
                break;
            }
            write(grade_file,&name[i],sizeof(char));
        }

        write(grade_file,&space,sizeof(char));
        write(grade_file,&space,sizeof(char));
        write(grade_file,&space,sizeof(char));

        printf("Grade of the student\n>>");
        scanf("%s",grade);

        for (int i = 0; i < MAX_GRADE_LEN; i++) {
            if (grade[i] == 0) {
                break;
            }
            write(grade_file,&grade[i],sizeof(char));
        }

        write(grade_file,&new_line,sizeof(char));
    }

    close(grade_file);

    return 0;
}