#include <errno.h>
#include <png.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void fatal_error(const char *message, ...) {
    va_list args;
    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

int main() {
    const char *png_file = "inputs/10.png";
    png_structp png_ptr;
    png_infop info_ptr;
    FILE *fp;
    png_uint_32 width;
    png_uint_32 height;
    int bit_depth;
    int color_type;
    int interlace_method;
    int compression_method;
    int filter_method;
    int j;
    png_bytepp rows;
    fp = fopen(png_file, "rb");
    if (!fp) {
        fatal_error("Cannot open '%s': %s\n", png_file, strerror(errno));
    }
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fatal_error("Cannot create PNG read structure");
    }
    info_ptr = png_create_info_struct(png_ptr);
    if (!png_ptr) {
        fatal_error("Cannot create PNG info structure");
    }
    png_init_io(png_ptr, fp);
    png_read_png(png_ptr, info_ptr, 0, 0);
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 &interlace_method, &compression_method, &filter_method);
    rows = png_get_rows(png_ptr, info_ptr);
    printf("Width is %d, height is %d\n", width, height);
    int rowbytes;
    rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    printf("Row bytes = %d\n", rowbytes);

    char ch = 0;
    int bytes = 0;

    for (j = 0; j < height; j++) {
        int i;
        png_bytep row;
        row = rows[j];
        for (i = 0; i < rowbytes; i += 3) {
            png_byte pixel;
            pixel = row[i];

            ch = ch << 1;
            if (pixel & 1 == 1) {
                ch |= 1;
            }
            bytes++;
            if (bytes == 8) {
                if (ch == 0) {
                    break;
                }
                printf("%c", ch);
                ch = 0;
                bytes = 0;
            }
        }
    }

    printf("\n");

    return 0;
}
