#include "spaceFilter.h"

void spaceFilter(std::string& input) {

    for(std::size_t i = 0; i < input.length()-1; i++) {

        if(input[i] == ' ' && input[i+1] == ' ') {
            input.erase(i,1);
            i--;
        }

    }
}
