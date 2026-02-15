#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char *argv[]) {
    // 1. Command line arguments check
    if (argc != 2) {
        printf("Usage: %s <network_file.txt>\n", argv[0]);
        return 1;
    }

    // 2. Open input file
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    // 3. Initialize and load the Graph and Symbol Table
    printf("Loading City Network from %s...\n", argv[1]);
    G myGraph = GRAPHload(fp);
    fclose(fp);

    if (myGraph == NULL) {
        printf("Error: Failed to load the graph structure.\n");
        return 1;
    }
    printf("Network loaded successfully!\n");

    // 4. Start the TSP Solver (Starting from index 0, e.g., Torino)
    printf("\nInitializing Branch & Bound Optimizer...\n");
    GRAPH_TSP(myGraph, 0);

    // 5. Memory cleanup
    GRAPHfree(myGraph);
    printf("\nMemory successfully freed. Program terminated.\n");

    return 0;
}