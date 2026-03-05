#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

FILE *f;

void Semilla() {
    srand(time(NULL));
}

int main() {
    Semilla();

    f = fopen("files/map1.dat", "wb");

    for (int i = 0; i < 10; i++) {

        int numberInsert = rand()%101;

        fwrite(&numberInsert, sizeof(numberInsert), 1, f);
    }

    fclose(f);
    return 0;
}