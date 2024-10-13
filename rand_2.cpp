#include "rand_2.h"

void NoOmpRun_MT(const Args& args) {
    int threads = 1;
    int iter_count;

    auto range = get_axis_range();
    float cube_volume =
        (range[1] - range[0]) * (range[3] - range[2]) * (range[5] - range[4]);

    std::ifstream input_file(args.GetInput());
    if (input_file.is_open()) {
        std::string line;
        std::getline(input_file, line);
        iter_count = std::stoi(line);
        input_file.close();
    } else
        throw std::runtime_error("Не удалось открыть файл");

	std::mt19937 seed(omp_get_wtime());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    long long all_hits = 0;
    auto start_time = omp_get_wtime();
    for (int i = 0; i < iter_count; ++i) {
        float x = range[0] + dist(seed) * (range[1] - range[0]);
        float y = range[2] + dist(seed) * (range[3] - range[2]);
        float z = range[4] + dist(seed) * (range[5] - range[4]);
        all_hits += hit_test(x, y, z);
    }
    auto end_time = omp_get_wtime();
    auto time = (end_time - start_time) * 1000;
    std::cout << "Time (0 thread(s)): " << time << " ms\n";

    float volume = cube_volume * (static_cast<float>(all_hits) /
                                  static_cast<float>(iter_count));

    std::ofstream output_file(args.GetOutput());
    if (output_file.is_open()) {
        output_file << volume << "\n";
        output_file.close();
    }
}

void OmpRun_MT(const Args& args) {
    int threads = args.GetThreads();
    int iter_count;
    auto range = get_axis_range();
    float cube_volume =
        (range[1] - range[0]) * (range[3] - range[2]) * (range[5] - range[4]);

    std::ifstream input_file(args.GetInput());
    if (input_file.is_open()) {
        std::string line;
        std::getline(input_file, line);
        iter_count = std::stoi(line);
        input_file.close();
    } else
        throw std::runtime_error("Не удалось открыть файл");

    omp_set_num_threads(threads);
    long long all_hits = 0;
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    auto start_time = omp_get_wtime();
#pragma omp parallel
    {
        std::mt19937 seed((omp_get_thread_num() + 1) * omp_get_wtime());
        uint64_t temp_hits = 0;

#pragma omp for schedule(static)
        for (int i = 0; i < iter_count; ++i) {
            int thread_ind = omp_get_thread_num();
            float x = range[0] + dist(seed) * (range[1] - range[0]);
            float y = range[2] + dist(seed) * (range[3] - range[2]);
            float z = range[4] + dist(seed) * (range[5] - range[4]);
            temp_hits += hit_test(x, y, z);
        }
#pragma omp atomic
        all_hits += temp_hits;
    }
    auto end_time = omp_get_wtime();
    auto time = (end_time - start_time) * 1000;
    std::cout << "Time (" << threads << " thread(s)): " << time << " ms\n";

    float volume = cube_volume * (static_cast<float>(all_hits) /
                                  static_cast<float>(iter_count));

    std::ofstream output_file(args.GetOutput());
    if (output_file.is_open()) {
        output_file << volume << "\n";
        output_file.close();
    }
}