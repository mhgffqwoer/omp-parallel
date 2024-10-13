#pragma once
#include <omp.h>

#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "args.h"
#include "hit.h"

#define UINT32_MAX 4294967295U

class Xorshift32 {
   private:
    uint32_t state;

   public:
    Xorshift32(uint32_t seed) : state(seed) {}

    float next() {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        return static_cast<float>(state) / (static_cast<float>(UINT32_MAX) + 1);
    }
};

void NoOmpRun_Xorshift32(const Args& args);

void OmpRun_Xorshift32(const Args& args);