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
    int grade_file = open("grades.dat",O_RDONLY);
    struct StudentGrade sg;

    while(read(grade_file,&sg,sizeof(struct StudentGrade)) != 0) {
        printf("%s     %s\n",sg.name,sg.grade);
    }
    
    close(grade_file);

    return 0;
}