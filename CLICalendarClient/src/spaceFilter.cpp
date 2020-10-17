#include "spaceFilter.h"

void spaceFilter(std::string& input) {

    for(int i = 0; i < input.length()-1; i++) {

        if(input[i] == ' ' && input[i+1] == ' ') {
            input.erase(i,1);
            i--;
        }

    }
}
