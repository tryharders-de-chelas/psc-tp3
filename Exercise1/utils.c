#include "utils.h"

void check_if_allocated(void *ptr) {
    if (ptr == NULL) {
        printf("[error] - memory couldn't be allocated\n");
        exit(EXIT_FAILURE);
    }
}

void check_if_file_opened(FILE *file) {
    if (file == NULL) {
        printf("[error] - couldn't open the file\n");
        exit(EXIT_FAILURE);
    }
}
