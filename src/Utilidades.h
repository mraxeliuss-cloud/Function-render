#include <cmath>

namespace Matematicas{
    bool floatIguales(float i, float j){
        if(std::abs(i - j) < 1e-6){
            return true;
        }else{
            return false;
        }
    }
};