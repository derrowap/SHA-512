/**
 * Author: Austin Derrow-Pinion
 * Class: CSSE/MA 479 - Cryptography
 * Purpose: Homework 08
 * Due: 05/11/2017
 *
 * An implementation of SHA-512, a hashing algorithm to output a 512-bit digest
 * given a variable length message as input.
 */

#include "sha-512.h"

/**
 * Reads input from the open file, fp, and stores the data in the buffer.
 * When the end of the file is reached, the global variable, file_ended,
 * is set to 1. Pads the end of the buffer according to the algorithm.
 * 
 * Returns: 0 if there needs to be another hash block.
 *          1 if there does not need to be another hash block.
 */
int readInputFile(char buffer[INPUT_SIZE], FILE *fp) {
  int i, output = 0;
  if (file_ended)
    output = 1;
  for (i = 0; i < INPUT_SIZE; i++) {
    if (file_ended) {
      /* pad the buffer */
      buffer[i] = 0;
    } else if (!fread(buffer + i, 1, 1, fp)) {
      file_ended = 1;
      buffer[i] = 0x80;
      output = i < INPUT_SIZE - 3;
    } else {
      L += 8;
    }
  }
  if (output) {
    buffer[INPUT_SIZE - 1] = (char)(L & 0x000000FF);
    buffer[INPUT_SIZE - 2] = (char)((L >> 8) & 0x000000FF);
    buffer[INPUT_SIZE - 3] = (char)((L >> 16) & 0x000000FF);
    buffer[INPUT_SIZE - 4] = (char)((L >> 24) & 0x000000FF);
  }
  return output;
}

/**
 * Updates the hash buffer (a, b, c, d, e, f, g, h) during a round in the
 * SHA-512 algorithm.
 */
void updateHashBuffer(int t) {
  unsigned long int temp = h + Ch(e, f, g) + Sigma1(e) + W[t] + K[t];
  h = g;
  g = f;
  f = e;
  e = d + temp;
  d = c;
  c = b;
  b = a;
  a = Sigma0(b) + Maj(b, c, d) + temp;
}

/**
 * Assigns the word schedule from the given input.
 */
void assignWordScedule(char M[INPUT_SIZE]) {
  int i, j;
  for (i = 0; i < 16; i++) {
    W[i] = 0;
    for (j = 0; j < 8; j++) {
      W[i] = ((W[i] << 8) & 0xFFFFFFFFFFFFFF00) | (M[i * 8 + j] & 0xFF);
    }
  }
  for (i = 16; i < 80; i++) {
    W[i] = W[i - 16] + sigma0(W[i - 15]) + W[i - 7] + sigma1(W[i - 2]);
  }
}

int main(int argc, char** argv) {
  int i, j, input_ended = 0, hash_block = 0;
  char M[INPUT_SIZE];
  unsigned long int H[8] = {a, b, c, d, e, f, g, h};

  /* ensure an input file is given */
  if (argc != 2) {
    printf("An input file is required, for example:\n");
    printf("\t./sha-512 shainput.txt\n");
    exit(1);
  }

  /* open the input file containing message to produce digest for */
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("Error: Could not read input file %s\n", argv[1]);
    exit(1);
  }

  while (!input_ended) {
    /* read the next block of the message */
    input_ended = readInputFile(M, fp);

    // printf("--- Hash of Block %02d ---\n", hash_block);

    /* assign word schedule for rounds */
    assignWordScedule(M);

    /* print W word registers */
    // for (i = 0; i < 80; i++) {
    //   printf("W(%02d) = %016lx\n", i, W[i]);
    // }
    // printf("  Initial abcdefgh: %lx %lx %lx %lx %lx %lx %lx %lx\n",
    //   a, b, c, d, e, f, g, h);

    /* execute compression function rounds */
    for (i = 0; i < 80; i++) {
      updateHashBuffer(i);
      // printf("After R%02d abcdefgh: %lx %lx %lx %lx %lx %lx %lx %lx\n",
      //   i, a, b, c, d, e, f, g, h);
    }

    /* update the hash buffer with current digest */
    a += H[0];
    b += H[1];
    c += H[2];
    d += H[3];
    e += H[4];
    f += H[5];
    g += H[6];
    h += H[7];
    H[0] = a;
    H[1] = b;
    H[2] = c;
    H[3] = d;
    H[4] = e;
    H[5] = f;
    H[6] = g;
    H[7] = h;

    printf("Hash after block %d: %016lx %016lx %016lx %016lx %016lx %016lx "
      "%016lx %016lx\n",
      hash_block++, H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);
  }

  /* display final digest */
  printf("Total message length in bits before padding: %d\n", L);
  printf("Total message length in bits after padding: %d\n", 1024 * hash_block);
  printf("Final hash: %016lx%016lx%016lx%016lx%016lx%016lx%016lx%016lx\n",
    H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);

  /* close the input file */
  fclose(fp);

  return 0;
}
