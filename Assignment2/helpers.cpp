/*
helpers.cpp
Joyce Huang sh2393

March 16, 2019
code from https://gist.github.com/thirdwing/da4621eb163a886a03c5
*/


#include <iostream>
#include <fstream>
#include <unistd.h>

void reportMemory()
{
    double vm_usage     = 0.0;
    double resident_set = 0.0;

    unsigned long vsize;
    long rss;
    {
        std::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> vsize >> rss;
    }

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; 
    vm_usage = vsize / 1024.0;
    resident_set = rss * page_size_kb;
    printf("virtual memory usage: %f\n", vm_usage);
}