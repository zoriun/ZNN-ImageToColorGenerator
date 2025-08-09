export CPLUS_INCLUDE_PATH=$HOME/libs/SDL3_image/include
export LIBRARY_PATH=$HOME/libs/SDL3_image/lib
export LD_LIBRARY_PATH=$HOME/libs/SDL3_image/lib

g++ main.cpp -o ZNNColorMatcher \
  -I/usr/local/include/SDL3 -D_REENTRANT \
  -L/usr/local/lib -lSDL3 -lSDL3_image

./ZNNColorMatcher