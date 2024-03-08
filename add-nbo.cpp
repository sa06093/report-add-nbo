#include <stdio.h>
#include <stdint.h>

uint32_t read_nbo(FILE* file) {
    uint32_t num = 0;
    fread(&num, sizeof(uint32_t), 1, file);
    return ((num & 0xFF000000) >> 24) | ((num & 0x00FF0000) >> 8) |
           ((num & 0x0000FF00) << 8) | ((num & 0x000000FF) << 24);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("syntax: add-nbo <file1> <file2>\n");
        printf("sample: add-nbo a.bin b.bin\n");
        return 1;
    }

    FILE* file1 = fopen(argv[1], "rb");
    FILE* file2 = fopen(argv[2], "rb");

    if (file1 == NULL || file2 == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    uint32_t num1 = read_nbo(file1);
    uint32_t num2 = read_nbo(file2);

    fclose(file1);
    fclose(file2);

    uint32_t sum = num1 + num2;

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, sum, sum);

    return 0;
}
