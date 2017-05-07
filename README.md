# SHA-512
Implementation of the SHA-512 algorithm for CSSE/MA 479 - Cryptography class at Rose-Hulman.

To execute the program, a Makefile is included to make it simple:
```
> make
> ./sha-512 shainput.txt
```

The program reads from the file `shainput.txt`, or any other text file you provide, to get the input
of the hash function. For example, if the contents of shainput.txt is
```
Description of SHA-512. The SHA-512 compression function operates on a 1024-bit message block and a 512-bit intermediate hash value. It is essentially a 512-bit block cipher algorithm which encrypts the intermediate hash value using the message block as key. Hence there are two main components to describe: (1) the SHA-512 compression function, and (2) the SHA-512 message schedule.
```
Then the output will look like
```
Hash after block 0: 1e491a31cd7f6ed0 ba7fa0d5eec5b082 205df1a7e9ad2e6b a339446aad18aa1c fa531c11c143a5e1 82253b3bd03a45b5 3a86cd892ddc04e3 f1730fed7749e7e4
Hash after block 1: baf5256d2b43278b 79aa71311c00fdb3 f56832a82f7eea84 d6f372a5c66c389e 9382c14b349ed826 994de6cd7a32e36f b410c78fecfde219 77f0bceb59094aa8
Hash after block 2: 9db949c4454c7a77 557ad20d5b0826e8 d5642226af2d3edb 8a868a681e8841bd ed240100fc19ccb8 fb78c135984342be 33a72f7332dbd123 ce7a225f66749765
Hash after block 3: 05d25ab314c10ff2 5219e9fa8ca23cf2 6923ad653796c027 fb23501eeb8a6454 029d2144d7146a5e 24d123c551720151 3994c04b85b3ffa8 1afb04d609138a62
Total message length in bits before padding: 3064
Total message length in bits after padding: 4096
Final hash: 05d25ab314c10ff25219e9fa8ca23cf26923ad653796c027fb23501eeb8a6454029d2144d7146a5e24d123c5517201513994c04b85b3ffa81afb04d609138a62

```
