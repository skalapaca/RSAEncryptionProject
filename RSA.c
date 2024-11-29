/*
    Steven Kalapaca, imz429
    CS 3333 Mathematical Foundations
    RSA Encryption Project
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_RANDOM 100

// Function to calculate greatest common divisor (GCD) of two numbers
unsigned long gcd(unsigned long a, unsigned long b) {
    if(b != 0){
        return gcd(b, a % b);
    }
    else{
        return a;
    }
}

// Function to calculate modulo inverse using extended Euclidean algorithm
unsigned long modInverse(unsigned long a, unsigned long m) {
    unsigned long x = 1;
    if(gcd(a, m) != 1){
        // Modular inverse can not be computed
        return -1;
    }
    else{
        // Begin x at one and increment each time the if statement is not met
        while(x > 0){
            if((a * x) % m == 1){
                return x;
            }
            else{
                x++;
            }
        }
    }
}

unsigned long randomNumber(){
    int rd_num = rand() % (MAX_RANDOM + 1);
}

// Function to generate keys for RSA encryption
void generateKeys(unsigned long p, unsigned long q, unsigned long *n, unsigned long
*e, unsigned long *d) {
    // Compute n, used as part of public and private key
    *n = p * q;
    // Compute phin, used in range for e
    unsigned long phin = (p - 1) * (q - 1);
    // Compute e (e < phin; e and phin are coprime), used as part of public key
    *e = 7;
    // Code to randomly choose an e
    // srand((unsigned int)time(NULL));
    // do {
    //     *e = randomNumber();
    // } while(*e >= phin && gcd(*e, phin) != 1);
    // Compute d, used as part of private key
    *d = modInverse(*e, phin);
}

// Function to calculate exponent
unsigned long long longPow(unsigned long x, unsigned long y) {
    unsigned long result = 1;
    for (unsigned long i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

// Function to encrypt plaintext using RSA
unsigned long long encrypt(unsigned long plaintext, unsigned long e, unsigned long n) {
    return longPow(plaintext, e) % n;
}

// Function to decrypt ciphertext using RSA
unsigned long long decrypt(unsigned long ciphertext, unsigned long d, unsigned long n) {
    return longPow(ciphertext, d) % n;
}

unsigned long main() {
    unsigned long p; // prime number, try 3, 5, 7, 11, 13, ...
    unsigned long q; // prime number, try 3, 5, 7, 11, 13, ...
    unsigned long n, e, d;    

    // Print modular inverse of p and q
    printf("Enter p and q: ");
    scanf("%lu %lu", &p, &q);

    // Generate RSA keys
    generateKeys(p, q, &n, &e, &d);
    printf("Public key (e, n): (%lu, %lu)\n", e, n);
    printf("Private key (d, n): (%lu, %lu)\n\n", d, n);

    //Encrypt and decrypt a sample plaintext, which we assume is given as an integer value
    unsigned long plaintext;
    printf("Enter an integer between 0 and n-1 as plain text to be encrypted: ");
    scanf("%lu", &plaintext);
    printf("Original plaintext: %lu\n", plaintext);
    unsigned long ciphertext = encrypt(plaintext, e, n);
    printf("Encrypted ciphertext: %lu\n", ciphertext);
    unsigned long decrypted = decrypt(ciphertext, d, n);
    printf("Decrypted plaintext: %lu\n\n", decrypted);
    return 0;
} 