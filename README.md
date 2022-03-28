# cryptography
A Minimal Dependency Library for Crypotgraphy Written in C

## Introduction
Welcome to the `anshulkamath`'s big unsigned integer library! This library is the second iteration of such a library. The original repository can be found on anshulkamath's GitHub [here](https://github.com/anshulkamath/big-uint-dep)!

## How to use this library
This library will offer implementations for several cryptographic algorithms, such as ECDSA and RSA. Furthermore, this library will build the infrastructure it needs from scratch. Namely, we implement our own big, unsigned integer operations. Integers are represented as arrays of 32-bit, unsigned integers, where each digit (or "limb", as we call it) is a successive power of 2^32. Finally, we represent these arrays in little-endian, so `arr[0]` represents the least significant digit while `arr[1]` represents the most significant digit.
