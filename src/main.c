#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // for getopt
#include "defs.h"
#include "param.h"
#include "ncd.h"
#include "msg.h"
#include "mem.h"
#include "alphabet.h"
#include "common.h"
#include "buffer.h"
#include "levels.h"
#include "dna.h"
#include "similarity.h"

void PrintUsage(void) {
    fprintf(stderr,
        "Usage: ncd [options] <reference_file> <target_file>\n"
        "Options:\n"
        "  -h                     Show this help message\n"
        "  -v                     Verbose mode\n"
        "  --dna                  DNA mode\n"
        "  --threads <n>          Number of threads\n"
        "  -m <model>             Model parameters\n"
        "  -r <ref>               Reference file\n"
        "\n");
}

int main(int argc, char *argv[]) {
    NCD_PARAMETERS *P;
    char *modelStr = NULL;
    
    P = (NCD_PARAMETERS *) Malloc(1 * sizeof(NCD_PARAMETERS));
    P->verbose = 0;
    P->dna = 0;
    P->threads = 1;
    P->reference = NULL;
    P->filename = NULL;
    P->nModels = 1;
    P->model = NULL;
    
    int i;
    for(i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-h") == 0) {
            PrintUsage();
            return EXIT_SUCCESS;
        }
        else if(strcmp(argv[i], "-v") == 0)
            P->verbose = 1;
        else if(strcmp(argv[i], "--dna") == 0)
            P->dna = 1;
        else if(strcmp(argv[i], "--threads") == 0 && i+1 < argc)
            P->threads = atoi(argv[++i]);
        else if(strcmp(argv[i], "-m") == 0 && i+1 < argc)
            modelStr = argv[++i];
        else if(strcmp(argv[i], "-r") == 0 && i+1 < argc)
            P->reference = argv[++i];
        else if(P->filename == NULL)
            P->filename = argv[i];
    }

    if(P->reference == NULL || P->filename == NULL) {
        PrintUsage();
        return EXIT_FAILURE;
    }

    // Initialize model parameters
    if(modelStr != NULL) {
        P->model = (MODEL_PAR *) Malloc(1 * sizeof(MODEL_PAR));
        *P->model = ArgsUniqModelNCD(modelStr, 0);
    }

    // Initialize alphabet
    P->A = CreateAlphabet();
    P->nSym = 4;  // DNA alphabet size

    // Run NCD and calculate similarity
    NormalizedCompressionDistance(P);
    double similarity = 0.0;
    double ncd = 0.0;
    
    // Read NCD from stdout
    char line[1024];
    FILE *tmp = tmpfile();
    FILE *stdout_bak = stdout;
    stdout = tmp;
    NormalizedCompressionDistance(P);
    stdout = stdout_bak;
    
    rewind(tmp);
    while (fgets(line, sizeof(line), tmp)) {
        if (sscanf(line, "1\t%lf", &ncd) == 1) {
            similarity = (1.0 - ncd) * 100.0;  // Convert to percentage
            if (similarity < 0) similarity = 0;  // Clamp to 0-100 range
            if (similarity > 100) similarity = 100;
            break;
        }
    }
    fclose(tmp);

    // Print in CSV format with headers
    static int header_printed = 0;
    if (!header_printed) {
        printf("InputSeq,SeqReference,Similarity(%%),SCD\n");
        header_printed = 1;
    }
    printf("%s,%s,%.2f,%.6f\n", P->filename, P->reference, similarity, ncd);

    // Cleanup
    if(P->model != NULL)
        Free(P->model);
    Free(P->A);
    Free(P);
    return EXIT_SUCCESS;
} 