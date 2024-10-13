#pragma once
#include <omp.h>

#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "args.h"
#include "hit.h"

void NoOmpRun_MT(const Args& args);

void OmpRun_MT(const Args& args);