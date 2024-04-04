#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* The RGB values of a pixel. */
struct Pixel {
    int red;
    int green;
    int blue;
};

/* A linked list of strings to store comments. */
struct Comment {
    char *text;
    struct Comment *next;
};

/* An image loaded from a PPM file. */
struct PPM {
    int width; /* Width of the image in pixels */
    int height; /* Height of the image in pixels */
    int max; /* Maximum pixel value */
    struct Pixel *pixels; /* Dynamically-allocated array of pixel data */
    struct Comment *comments; /* Linked list of comment strings */
};

/* Adds a new comment to the linked list of comments in img. */
void addComment(struct PPM *img, const char *text)
{
    struct Comment *newComment = malloc(sizeof(struct Comment));

    if (!newComment) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    newComment->text = strdup(text);

    if (!newComment->text) {
        fprintf(stderr, "Memory allocation failed\n");
        free(newComment);
        return;
    }

    newComment->next = img->comments;
    img->comments = newComment;
}


void freePPM(struct PPM *img)
{
    free(img->pixels);
    struct Comment *c = img->comments;
    while (c != NULL) {
        struct Comment *next = c->next;
        free(c->text);
        free(c);
        c = next;
    }
    free(img);
}

/* Reads an image from an open PPM file.
 * Returns a new struct PPM, or NULL if the image cannot be read. */
struct PPM *getPPM(FILE * f)
{
    char magic[3];
    int width, height, max;
    struct Pixel *pixels;
    struct Comment *comments = NULL;

    /* Read the PPM header */
    if (fscanf(f, "%2s\n", magic) != 1) {
        fprintf(stderr, "Error reading magic number\n");
        return NULL;
    }

    if (strcmp(magic, "P3") == 0) {
        /* Plain PPM file */
        if (fscanf(f, "%d %d\n%d\n", &width, &height, &max) != 3) {
            fprintf(stderr, "Error reading image dimensions or maximum pixel value\n");
            return NULL;
        }
    } else if (strcmp(magic, "P6") == 0) {
        /* Normal PPM file */
        if (fscanf(f, "%d %d\n%d\n", &width, &height, &max) != 3) {
            fprintf(stderr, "Error reading image dimensions or maximum pixel value\n");
            return NULL;
        }
    } else {
        fprintf(stderr, "Invalid PPM format: %s\n", magic);
        return NULL;
    }

    /* Allocate memory for the pixel data */
    pixels = malloc(sizeof(struct Pixel) * width * height);
    if (!pixels) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    /* Read the pixel data */
    if (strcmp(magic, "P3") == 0) {
        /* Plain PPM file - read pixel data as decimal numbers */
        int i;
        for (i = 0; i < width * height; i++) {
            if (fscanf(f, "%d %d %d", &pixels[i].red, &pixels[i].green, &pixels[i].blue) != 3) {
                fprintf(stderr, "Error reading pixel data\n");
                free(pixels);
                return NULL;
            }
        }
    } else if (strcmp(magic, "P6") == 0) {
        /* Normal PPM file - read pixel data as binary */
        int i;
        for (i = 0; i < width * height; i++) {
            unsigned char r, g, b;
            if (fread(&r, 1, 1, f) != 1 ||
                fread(&g, 1, 1, f) != 1 ||
                fread(&b, 1, 1, f) != 1) {
                fprintf(stderr, "Error reading pixel data\n");
                free(pixels);
                return NULL;
            }
            pixels[i].red = r;
            pixels[i].green = g;
            pixels[i].blue = b;
        }
    }

    /* Create the PPM struct */
    struct PPM *img = malloc(sizeof(struct PPM));
    if (!img) {
        fprintf(stderr, "Memory allocation failed\n");
        free(pixels);
        return NULL;
    }

    img->width = width;
    img->height = height;
    img->max = max;
    img->pixels = pixels;
    img->comments = comments;

    /* Read any comments */
    while (1) {
        int c = fgetc(f);
        if (c == '#') {
            char *text = malloc(sizeof(char) * 100);
            if (!text) {
                fprintf(stderr, "Memory allocation failed\n");
                return NULL;
            }

            if (fgets(text,100,f) == NULL) {
                fprintf(stderr, "Error reading comment\n");
                free(text);
                freePPM(img);
                return NULL;
            }
            struct Comment *new_comment = malloc(sizeof(struct Comment));
            
            if (!new_comment) {
                fprintf(stderr, "Memory allocation failed\n");
                free(text);
                freePPM(img);
                return NULL;
            }
            
             new_comment->text = text;
             new_comment->next = comments;
             comments = new_comment;
             
             } else {
                ungetc(c, f);
                break;
                }
    } 
    return img;
}

/* Write img to stdout in PPM format. */
void showPPM(const struct PPM *img)
{
    int i, j;
    const struct Pixel *pixels = img->pixels;
    const struct Comment *comment = img->comments;

    /* Write the PPM header */
    printf("P3\n%d %d\n%d\n", img->width, img->height, img->max);

    /* Write comments */
    while (comment != NULL) {
        printf("# %s", comment->text);
        comment = comment->next;
    }

    /* Write pixel data */
    for (i = 0; i < img->height; i++) {
        for (j = 0; j < img->width; j++) {
            printf("%d %d %d ", pixels[i * img->width + j].red,
                   pixels[i * img->width + j].green,
                   pixels[i * img->width + j].blue);
                   printf("\n");
        }
    }
}

/* Opens and reads a PPM file, returning a pointer to a new struct PPM.
 * On error, prints an error message and returns NULL. */
struct PPM *readPPM(const char *filename)
{
    /* Open the file for reading */
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "File %s could not be opened.\n", filename);
        return NULL;
    }

    /* Load the image using getPPM */
    struct PPM *img = getPPM(f);

    /* Close the file */
    fclose(f);

    if (img == NULL) {
        fprintf(stderr, "File %s could not be read.\n", filename);
        return NULL;
    }

    return img;
}

/* Encode the string text into the red channel of image img.
 * Returns a new struct PPM, or NULL on error. */
struct PPM *encode(const char *text, const struct PPM *img)
{
    int i, j;

    int text_len = strlen(text);

    /* Check that there are enough pixels in the image to encode the message */
    int num_pixels = img->width * img->height;
    if (text_len * 8 > num_pixels) {
        fprintf(stderr, "Message too large to encode in image\n");
        return NULL;
    }

    /* Allocate memory for the new image */
    struct PPM *new_img = malloc(sizeof(struct PPM));
    if (!new_img) {
        perror("malloc");
        return NULL;
    }
    new_img->width = img->width;
    new_img->height = img->height;
    new_img->max = img->max;
    new_img->pixels = malloc(sizeof(struct Pixel) * num_pixels);
    if (!new_img->pixels) {
        perror("malloc");
        free(new_img);
        return NULL;
    }

    /* Copy the original image to the new image and encode the message */
    memcpy(new_img->pixels, img->pixels, sizeof(struct Pixel) * num_pixels);

    /* Encode each character of the message in the red channel of successive pixels */
    for (i = 0, j = 0; i < text_len; i++, j += 8) {
        char c = text[i];
        int k;
        for (k = 0; k < 8; k++) {
            int bit = (c >> (7 - k)) & 1;
            int index = j + k;
            new_img->pixels[index].red = (new_img->pixels[index].red & 0xfe) | bit;
        }
    }

    return new_img;
}

/* Decode the message hidden in the red channel of the new image using the old image as a reference.
 * Returns a string containing the hidden message, or NULL on error. */
char *decode(const struct PPM *oldimg, const struct PPM *newimg) {
    
    int i, j;
    int num_pixels = oldimg->width * oldimg->height;
    char *message = malloc(sizeof(char) * (num_pixels / 8 + 1));
    if (!message) {
        perror("malloc");
        return NULL;
    }

    /* Decode each character of the message from the red channel of successive pixels */
    for (i = 0, j = 0; j < num_pixels; i++, j += 8) {
        char c = 0;
        int k;
        for (k = 0; k < 8; k++) {
            int index = j + k;
            int bit = newimg->pixels[index].red & 1;
            c = (c << 1) | bit;
        }
        message[i] = c;
    }

    /* Remove all unsigned characters from the message and count consecutive spaces */
    int spaces = 0; // Counter for consecutive spaces
    for (i = 0; i < strlen(message); i++) {
        if (message[i] < 0) {
            message[i] = '\0';
            break;
        }
        if (message[i] == ' ') {
            spaces++;
        } else {
            spaces = 0;
        }
        if (spaces >= 10) {
            message[i+1] = '\0'; // Terminate message at this point
            break;
        }
    }

    return message;
}

int main(int argc, char *argv[])
{
    /* Initialise the random number generator, using the time as the seed */
    srand(time(NULL));

    /* Parse command-line arguments */
    if (argc == 3 && strcmp(argv[1], "t") == 0) {
        /* Mode "t" - test PPM reading and writing */

        struct PPM *img = readPPM(argv[2]);
        showPPM(img);

    } else if (argc == 3 && strcmp(argv[1], "e") == 0) {
        /* Mode "e" - encode PPM */

        struct PPM *oldimg = readPPM(argv[2]);

        /* prompt for a message from the user, and read it into a string */
        fprintf(stderr, "Enter message to encode: ");
        char message[1000];
        fgets(message, 1000, stdin);

        struct PPM *newimg;
        /* encode the text into the image with encode, and assign to newimg */
        newimg = encode(message,oldimg);

        /* write the image to stdout with showPPM */
        showPPM(newimg);

    } else if (argc == 4 && strcmp(argv[1], "d") == 0) {
        /* Mode "d" - decode PPM */

        struct PPM *oldimg;
        /* get original file filename from argv, load it with
           readPPM, then assign to oldimg */
        oldimg = readPPM(argv[2]);

        struct PPM *newimg;
        /* get encoded file filename from argv, load it with
           readPPM, then assign to newimg */
        newimg = readPPM(argv[3]);

        char *message;
        /* decode the encodedPPM with the comparisonPPM and assign to message */
        message = decode(oldimg, newimg);

        /* print the decoded message to stdout */
        fprintf(stderr, "Decoded message: %s\n", message);

    } else {
        fprintf(stderr, "Unrecognised or incomplete command line.\n");
        return 1;
    }

    return 0;
}
