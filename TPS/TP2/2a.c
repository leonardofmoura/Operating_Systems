#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: 2a <source> <destination>");
        return 0;
    }

    FILE* source = fopen(argv[1],"r");
    FILE* destination = fopen(argv[2],"a");

    fseek(source,0,SEEK_END);
    long size = ftell(source);

    void* contents = malloc(size*sizeof(char));

    fseek(source,0,SEEK_SET);
    fread(contents,1,size,source);
    fwrite(contents,1,size,destination);

    fclose(source);
    fclose(destination);
    free(contents);

    return 0;
}