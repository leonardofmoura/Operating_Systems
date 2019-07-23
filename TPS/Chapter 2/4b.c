#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_NAME_LEN    50
#define MAX_GRADE_LEN   2

struct StudentGrade {
    char  name[MAX_NAME_LEN];
    char grade[MAX_NAME_LEN];
};

int main() {
    struct StudentGrade sg;
    char space = ' ';
    char new_line = '\n';

    int grade_file = open("grades.dat",O_WRONLY | O_APPEND);

    while(1) {
        printf("Name of the student(type \"exit\" to exit)\n>>");
        scanf("%s",sg.name);  

        if (!strcmp(sg.name,"exit")) { //breaks if the stings are equal
            break;
        }

        printf("Grade of the student\n>>");
        scanf("%s",sg.grade);

        write(grade_file,&sg,sizeof(struct StudentGrade));
    }

    close(grade_file);

    return 0;
}