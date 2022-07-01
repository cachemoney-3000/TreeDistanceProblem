#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *file;
FILE *out;

typedef struct Distance {
    int x;
    int y;
} Distance;

typedef struct TreeInfo {
    int numPartners;
    Distance* distance;
} TreeInfo;

float calculate(Distance* dist, int n, int i);
void freeMemory(TreeInfo* info, int numCases);
void execute(int numCases);

int main() {
    file  = fopen("in.txt", "r");

    if(file == NULL) {
        printf("File not found");
        exit(1);
    }

    int i, j;
    int numCases;
    fscanf(file, "%d", &numCases);

    execute(numCases);

    return 0;
}

// Calculates the sum of all distances of the trees using recursion
float calculate(Distance* dist, int n, int i){
    // Base case
    if (i == 0) return 0;

    // Get the first coordinate
    int x1 = dist[i - 1].x;
    int y1 = dist[i - 1].y;
    // Get the second coordinate
    int x2 = dist[i - 2].x;
    int y2 = dist[i - 2].y;
    // Solve for their difference
    int xDiff = x1 - x2;
    int yDiff = y1 - y2;
    // Solve for their squared
    float xx = xDiff * xDiff;
    float yy = yDiff * yDiff;
    // Solve for the distance
    float squareRoot = sqrt(xx + yy);

    // Calculate the sum of all distance
    return squareRoot + calculate(dist, n - 1, i - 2);
}

// Free the memory allocated
void freeMemory(TreeInfo* info, int numCases) {
    int i;
    for (i = 0; i < numCases; i++){
        free(info[i].distance);
    }
    free(info);
}

void execute(int numCases){
    int i, j;
    out = fopen("out.txt", "w");

    // Scan all the cases
    TreeInfo* info = malloc(numCases * sizeof(TreeInfo));
    for (i = 0; i < numCases; i++){
        // Get how many partnered trees are there
        int nTrees;
        fscanf(file, "%d", &nTrees);
        int n2 = nTrees * 2;
        info[i].numPartners = nTrees;

        // Get the distances of each partnered trees
        info[i].distance = malloc(n2 * sizeof(Distance));
        for (j = 0; j < nTrees * 2; j++) {
            int x, y;
            fscanf(file, "%d %d", &x, &y);
            info[i].distance[j].x = x;
            info[i].distance[j].y = y;
        }

        // Prints out the result
        float sum = calculate(info[i].distance, info[i].numPartners, n2);
        printf("%0.3f\n", sum);
        fprintf(out, "%0.3f\n", sum);
    }

    freeMemory(info, numCases);
    fclose(file);
    fclose(out);

    return;
}