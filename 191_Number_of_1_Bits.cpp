/*
Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).

For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, so the function should return 3.
*/

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ones = 0;
        while (n) {
            n &= n-1;
            ones++;
        }
        
        return ones;
    }
};

// A more straightforward solution:
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int numberOfOnes = 0;
        for (int i = 0; i < 32; i++) {
            if (n & 1) numberOfOnes++;
            n >>= 1;
        }
        return numberOfOnes;
    }
};
