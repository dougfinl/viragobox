#include "ViragoBox.h"
#include <iostream>
#include <boost/program_options.hpp>


namespace po = boost::program_options;
using namespace virago;

extern const char *__progname;

static void checkResolutionOption(const std::vector<unsigned int> &res) {
    if (res.size() != 2) {
        throw new po::validation_error(
                po::validation_error::invalid_option_value,
                "resolution",
                std::to_string(res.size())
                );
    }
}

int main(int argc, char** argv) {
    ViragoBoxOptions vbOptions;

    try {
        po::options_description desc("Options");
        desc.add_options()
            ("help,h",
                "Print this message and exit")
            ("debug,d",
                po::value<bool>()->zero_tokens(), "Show debug messages")
            ("address,a",
                po::value<unsigned int>()->default_value(1), "Start address")
            ("resolution,r",
                po::value<std::vector<unsigned int>>()->multitoken()->notifier(&checkResolutionOption), "Resolution of the render window")
            ("fullscreen,f",
                po::value<bool>()->zero_tokens(), "Render to the entire display");

        po::variables_map vm;

        po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);

        if (vm.count("help")) {
            std::cout << "Usage " << __progname << " [options]" << std::endl;
            std::cout << desc << std::endl;

            return(EXIT_FAILURE);
        }

        if (vm.count("address")) {
            vbOptions.address = vm["address"].as <unsigned int>();
        }

        if (!vm["resolution"].empty()) {
            std::vector<unsigned int> res = vm["resolution"].as<std::vector<unsigned int>>();
            vbOptions.resX = res.at(0);
            vbOptions.resY = res.at(1);
        }

        if (vm.count("fullscreen")) {
            vbOptions.fullscreen = true;
        }

        if (vm.count("debug")) {
            vbOptions.debug = true;
        }
    } catch(po::error& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;

        return EXIT_FAILURE;
    }

    ViragoBox vb(vbOptions);
    vb.run();

    return EXIT_SUCCESS;
}

