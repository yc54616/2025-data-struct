#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_and_copy(const char* basename, int size, int copies) {
    int* data = malloc(sizeof(int) * size);
    if (!data) exit(1);

    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) data[i] = rand() % 1000000;

    for (int i = 0; i < copies; i++) {
        char filename[100];
        if (i == 0)
            sprintf(filename, "data/%s.txt", basename);
        else
            sprintf(filename, "data/%s_copy%d.txt", basename, i);

        FILE* fp = fopen(filename, "w");
        if (!fp) {
            perror("파일 열기 실패");
            exit(1);
        }

        for (int j = 0; j < size; j++)
            fprintf(fp, "%d\n", data[j]);

        fclose(fp);
    }

    free(data);
}

int main() {
    generate_and_copy("data_100", 100, 7);
    generate_and_copy("data_1000", 1000, 7);
    generate_and_copy("data_10000", 10000, 7);
    generate_and_copy("data_100000", 100000, 7);
    return 0;
}
