#include "rand_1.h"
#include "rand_2.h"
#include "rand_3.h"

int main(const int argc, const char** argv) {
    Args args(argc, argv);
    if (args.Generator() == 1) {
        if (args.OpenMP()) OmpRun_Miller(args);
        else NoOmpRun_Miller(args);
    } if (args.Generator() == 2) {
        if (args.OpenMP()) OmpRun_MT(args);
        else NoOmpRun_MT(args);
    } if (args.Generator() == 3) {
        if (args.OpenMP()) OmpRun_Xorshift32(args);
        else NoOmpRun_Xorshift32(args);
    }
}