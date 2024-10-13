#pragma once
#include <omp.h>

#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "args.h"
#include "hit.h"

float Miller_rand(uint32_t& seed);

void NoOmpRun_Miller(const Args& args);

void OmpRun_Miller(const Args& args);