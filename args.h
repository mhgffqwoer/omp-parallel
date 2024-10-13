#pragma once
#include <omp.h>

#include <iostream>
#include <vector>
#include <string>

class Args {
   private:
    std::string input_;
    std::string output_;
    int omp_threads_;
	bool omp_ = true;
    int generator_ = 3; //Xorshift32 = default

    void Parse(const std::vector<std::string>& args);

   public:
    std::string GetInput() const { return input_; }

    std::string GetOutput() const { return output_; }

    int GetThreads() const { return omp_threads_; }

    bool OpenMP() const { return omp_; }

    int Generator() const { return generator_; }

    Args(const int argc, const char** argv);
};