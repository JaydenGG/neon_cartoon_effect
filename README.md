# neon_cartoon_effect
Cartoon effect with the arm compute library

1.Download arm compute library\
git clone https://github.com/ARM-software/ComputeLibrary

2.compile arm compute library\
Hint:\
(The compute library must currently be built with both neon and opencl enabled - neon=1 and opencl=1)\

scons Werror=1 -j4 debug=0 asserts=1 neon=1 opencl=1 embed_kernels=1 os=linux arch=arm64-v8a examples=1\
You guys should check how many processors on your device by the command: \
cat /proc/cpuinfo\
and then modify -j4 by -jn.

3.run example:\
LD_LIBRARY_PATH=build/ ./build/examples/neon_convolution \
(If everything is working properly, the example should return "Test passed".)

4.install arm-linux-gnueabihf-g++\
apt install g++-arm-linux-gnueabihf

5.download this examples\
and copy the neon_cartoon_effect to ComputeLibrary/build/examples\
cp neon_cartoon_effect ComputeLibrary/examples/ 

6.run the examples\
aarch64-linux-gnu-g++ examples/neon_cartoon_effect.cpp utils/Utils.cpp -I. -Iinclude -std=c++11 -L./build -larm_compute -o build/neon_cartoon_effect
