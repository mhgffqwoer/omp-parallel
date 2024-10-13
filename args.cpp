#include "args.h"

Args::Args(const int argc, const char** argv) {
	std::vector<std::string> args(argc - 1);
	for (int i = 1; i < argc; ++i) args[i - 1] = argv[i];
	Parse(args);  
}

void Args::Parse(const std::vector<std::string>& args) {
	for (int i = 0; i < args.size(); ++i) {
		if (args[i] == "--no-omp") omp_ = false;
		if (args[i] == "--omp-threads") {
			if (args[i+1] == "default") omp_threads_ = omp_get_max_threads();
			else omp_threads_ = std::stoi(args[i+1]);
			++i;
		}
		if (args[i] == "--input") input_ = args[++i];
		if (args[i] == "--output") output_ = args[++i];
		if (args[i] == "--generator") generator_ = std::stoi(args[++i]);
	}
}
