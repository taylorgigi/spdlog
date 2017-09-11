//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#include <atomic>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include "spdlog/spdlog.h"

using namespace std;

int main(int argc, char* argv[])
{

    using namespace std::chrono;
    using clock=steady_clock;
    namespace spd = spdlog;

    int howmany = 1000000;

    spd::set_async_mode(1048576);
    auto logger = spdlog::create<spd::sinks::hourly_file_sink_st>("file_logger", "logs/spd-hourly-bench-st", 10*1024*1024);
    logger->set_pattern("[%Y-%b-%d %T.%e]: %v");


    std::atomic<int > msg_counter {0};
    auto start = clock::now();
    for (int t = 0; t < howmany; ++t, ++msg_counter)
    {
            logger->info("spdlog message #{}: This is some text for your pleasure xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", msg_counter);
    }
    duration<float> delta = clock::now() - start;
    float deltaf = delta.count();
    auto rate = howmany/deltaf;

    cout << "Total: " << howmany << std::endl;
    std::cout << "Delta = " << deltaf << " seconds" << std::endl;
    std::cout << "Rate = " << rate << "/sec" << std::endl;

    spdlog::drop_all();

    return 0;
}

