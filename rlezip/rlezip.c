#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dirent.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define MAX_PATH 1024
#define BUFFER_SIZE 4096

// Run-Length Encoding compress
void rle_compress(FILE *input, FILE *output) {
    int count;
    char last, current;

    while ((count = fread(&current, 1, 1, input)) != 0) {
        int run_length = 1;
        while (run_length < 255 && (count = fread(&last, 1, 1, input)) != 0 && last == current) {
            run_length++;
        }
        fwrite(&current, 1, 1, output);
        fwrite(&run_length, 1, 1, output);
        if (count != 0 && last != current) {
            fseek(input, -1, SEEK_CUR);
        }
    }
}

void compress_from_memory(const uint8_t *data, size_t data_len, uint8_t *output, size_t *output_len) {
    uint8_t current, last;
    size_t input_index = 0, output_index = 0;

    while (input_index < data_len) {
        current = data[input_index++];
        int run_length = 1;

        while (run_length < 255 && input_index < data_len && data[input_index] == current) {
            run_length++;
            input_index++;
        }

        // Ensure we don't exceed buffer size
        if (output_index + 1 < *output_len) {
            output[output_index++] = current;
            output[output_index++] = (uint8_t) run_length;
        } else {
            // Buffer overflow
            break;
        }
    }

    *output_len = output_index; // Set the actual compressed length
}

void zip_directory(const char *dir_name, const char *zip_name) {
    DIR *dir;
    struct dirent *entry;
    char path[MAX_PATH];

    FILE *output = fopen(zip_name, "wb");
    if (!output) {
        perror("Failed to open output zip file");
        exit(1);
    }

    dir = opendir(dir_name);
    if (!dir) {
        perror("Failed to open directory");
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Only for normal files in directories
            snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

            // save file name length and file name
            unsigned char name_length = strlen(entry->d_name);
            fwrite(&name_length, 1, 1, output);
            fwrite(entry->d_name, 1, name_length, output);

            FILE *input = fopen(path, "rb");
            if (input) {
                rle_compress(input, output);
                fclose(input);
            }
        }
    }

    closedir(dir);
    fclose(output);
}

int main() {
    #ifdef __EMSCRIPTEN__
    const char *dir_to_zip = "/working/target_directory";
    const char *output_zip_name = "/working/output.zip";
    #else
    const char *dir_to_zip = "target_directory";
    const char *output_zip_name = "output.zip";
    #endif

    zip_directory(dir_to_zip, output_zip_name);
    printf("Zipped %s to %s\n", dir_to_zip, output_zip_name);
    return 0;
}
