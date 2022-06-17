#include <iostream>
#include <TRandom.h>

int main(){
TRandom rndm;

for(unsigned int i = 0 ; i < 10 ; i++){
double val = rndm.Uniform(10.,20.);
std::cout << "Random Val : " << val << std::endl;

}
return 0;
}
