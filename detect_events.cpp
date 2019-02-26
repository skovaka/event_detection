/* sigalign.cpp 
 * align oxford nanopore event-level signals directly to the reference without
 * basecalling */

#include <iostream>
#include <iomanip>
#include <string>
#include <getopt.h>

#include "event_detector.hpp"

int main(int argc, char** argv) {
    static struct option long_opts[] = {
        {"win-len1",    required_argument,0,0},
        {"win-len2",    required_argument,0,0},
        {"thresh1",     required_argument,0,0},
        {"thresh2",     required_argument,0,0},
        {"peak-height", required_argument,0,0},
        {"min-mean",    required_argument,0,0},
        {"max-mean",    required_argument,0,0},
        {"raw-start",    required_argument,0,0},
        {"raw-len",    required_argument,0,0},
        {0,0,0,0}
    };

    EventParams params = event_detection_defaults;

    u32 raw_start = 0, raw_len = 0;

    while (1) {
        int opt_i;
        int c = getopt_long(argc, argv, "", long_opts, &opt_i);

        if (c == -1) break;
        else if (c != 0) {
            return 1;
        }

        std::string opt(long_opts[opt_i].name), val(optarg);

        if (opt == "win-len1") params.window_length1 = std::atoi(optarg);
        if (opt == "win-len2") params.window_length2 = std::atoi(optarg);
        if (opt == "thresh1") params.threshold1 = std::atof(optarg);
        if (opt == "thresh2") params.threshold2 = std::atof(optarg);
        if (opt == "peak-height") params.peak_height = std::atof(optarg);
        if (opt == "min-mean") params.min_mean = std::atof(optarg);
        if (opt == "max-mean") params.max_mean = std::atof(optarg);
        if (opt == "raw-start") raw_start = std::atoi(optarg);
        if (opt == "raw-len") raw_len = std::atoi(optarg);
    }

    if (optind == argc) {
        std::cerr << "Error: must include fast5 filename\n";
        return 1;
    }  

    std::string filename(argv[optind]);

    EventDetector ed(params);

    if (!fast5::File::is_valid_file(filename)) {
        std::cerr << "Error: '" << filename << "' is not a valid file \n";
    }

    try {
        fast5::File file;
        file.open(filename);
        
        if (!file.is_open()) {  
            std::cerr << "Error: unable to open '" 
                      << filename << "'\n";
        }

        std::vector<float> raw = file.get_raw_samples();

        if (raw_len == 0) raw_len = raw.size();

        for (u32 i = raw_start; i < raw_start+raw_len; i++) {
            if (ed.add_sample(raw[i])) {
                Event e = ed.get();
                std::cout << e.mean << "\t" 
                          << e.stdv << "\t"
                          << e.length << "\t"
                          << (raw_start+e.start)  << "\n"; 
            }
        }

    } catch (hdf5_tools::Exception& e) {
        std::cerr << "Error: hdf5 exception '" << e.what() << "'\n";
    }
}

