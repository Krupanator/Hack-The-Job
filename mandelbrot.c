#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "time.h"

void giveUsage(char *prog){
    printf("usage: %s [-c [centre.x] [centre.y]] [-w [range]] [i [itermax]]\n", prog);
    exit(-1);
}

typedef struct XY{
    float x;
    float y;
} XY;

int N = 2000;
XY midpoint = {0,0};
double range = 0.005;
int iteratemax = 255;
float **image = NULL;

int saveToPPM(float** img){
    float decCol;
    int R,G,B;
    float iter;
    FILE* ppmImage;
    ppmImage = fopen("fractal.ppm", "wb");
    fprintf(ppmImage, "P3\n");
    fprintf(ppmImage, "%d %d\n",N, N);
    fprintf(ppmImage, "255\n");

    // int temp;
    float freq1 = ((float)rand()/RAND_MAX) /10;
    float freq2 = ((float)rand()/RAND_MAX) /10;
    float freq3 = ((float)rand()/RAND_MAX) /10;
    int phase1 = (rand()%5) + 1;
    int phase2 = (rand()%5) + 1;
    int phase3 = (rand()%5) + 1;

    // printf("rand values: %f, %f, %f\n", freq1, freq2, freq3);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            iter = img[i][j];
            decCol = (1- iter) / iteratemax * (float)16777215;
            decCol = fabsf(decCol);

            R = decCol/(256 * 256);
            G = ((int)decCol/256) % 256;
            B = (int)decCol % 256;

            

            R = (unsigned char)(sin(freq1 * iter + phase1) * 230 + 25);
            G = (unsigned char)(sin(freq2 * iter + phase2) * 230 + 25);
            B = (unsigned char)(sin(freq3 * iter + phase3) * 230 + 25);
            // R = (unsigned char)(sin(0.016 * iter + 4) * 230 + 25);
            // G = (unsigned char)(sin(0.013 * iter + 2) * 230 + 25);
            // B = (unsigned char)(sin(0.01 * iter + 1) * 230 + 25);

            fprintf(ppmImage, "%d %d %d\n", R, G, B);
        }
    }
    return 1;
}

int main(int argc, char **argv){
    short iter = 0;
    int escape = 0;
    float Zn, contIter;
    XY c,z_new,z;
    int seed = 0;

    if(argc < 1){
        giveUsage(argv[0]);
    }
    //parse command line args
    for (int i=1 ; i < argc-1; i++) {
        if (strcmp(argv[i],"-c") == 0) {
            i++;
            midpoint.x = atof(argv[i]);
            i++;
            midpoint.y = atof(argv[i]);
        }
        if (strcmp(argv[i],"-w") == 0) {
            i++;
            range = atof(argv[i]);
        }
        if (strcmp(argv[i],"-i") == 0) {
            i++;
            iteratemax = atoi(argv[i]);
        }
        if (strcmp(argv[i],"-n") == 0) {
            i++;
            N = atoi(argv[i]);
            // printf("n: %d\n", n);
            // N = n;
        }
        if (strcmp(argv[i],"-s") == 0) {
            i++;
            seed = atoi(argv[i]);
        }
    }

    if(seed == 0){
        srand(time(NULL));
    }else{
        srand(seed);
    }

    // if ((image = malloc(N * N * sizeof(float))) == NULL){
    //     fprintf(stderr,"Failed to malloc memory to image\n");
    //     exit(-1);
    // }

    if ((image = malloc(N * sizeof(float*))) == NULL){
        fprintf(stderr,"Failed to malloc memory to image\n");
        exit(-1);
    }
    for(int i = 0; i < N; i++){
        if((image[i] = malloc(N * sizeof(float))) == NULL){
            fprintf(stderr,"Failed to malloc memory to image\n");
        exit(-1);
        }
    }

    // printf("bingus\n");
    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         escape = 0;
    //         iter = 0;
    //         z.x = 0;
    //         z.y = 0;
    //         c.x = midpoint.x + (j - (double)N / 2) * range;
    //         c.y = midpoint.y + (i - (double)N / 2) * range;
    //         while( iter < iteratemax && escape == 0){
    //             iter++;
    //             z_new.x = z.x * z.x - z.y *z.y + c.x;
    //             z_new.y = 2 * z.x * z.y + c.y;
    //             z.x = z_new.x;
    //             z.y = z_new.y;
    //             if(z.x * z.x + z.y * z.y > 4){
    //                 escape = 1;
    //             }
    //         }
    //         // image[j*N+i] = iter;
    //         image[i][j] = iter;
    //         // printf("iter saved [i][j] = [%d] [%d] %d\n", i, j, iter);
    //     }
    // }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            escape = 0;
            iter = 0;
            z.x = 0;
            z.y = 0;
            c.x = midpoint.x + (j - (double)N / 2) * range;
            c.y = midpoint.y + (i - (double)N / 2) * range;
            while( z.x * z.x + z.y * z.y < 4 && iter < iteratemax){
                iter++;
                z_new.x = z.x * z.x - z.y *z.y + c.x;
                z_new.y = 2 * z.x * z.y + c.y;
                z.x = z_new.x;
                z.y = z_new.y;
                // if(z.x * z.x + z.y * z.y > 4){
                //     escape = 1;
                // }
            }
            Zn = sqrt( z.x * z.x + z.y * z.y);
            contIter = iter + 1 - (log(2) / Zn) / log(2);
            // image[j*N+i] = iter;
            // printf("iter: %d\n", iter);
            image[i][j] = contIter;
            // printf("iter saved [i][j] = [%d] [%d] %d\n", i, j, iter);
        }
    }

    printf("saving to ppm file\n");
    saveToPPM(image);
    printf("saving to ppm file complete\n");
        
    return 0;
}