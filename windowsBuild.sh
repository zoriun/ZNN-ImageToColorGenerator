rm ./WindowsBuild.zip

x86_64-w64-mingw32-g++ main.cpp -o ZnnITCG.exe \
  -std=c++17 \
  -ICrossPlatformBinaries/SDL3_Win/include \
  -ICrossPlatformBinaries/SDL3_Image_Win/include \
  -LCrossPlatformBinaries/SDL3_Win/lib \
  -LCrossPlatformBinaries/SDL3_Image_Win/lib \
  -lSDL3 -lSDL3_image -mwindows \
  -static-libgcc -static-libstdc++

mkdir winBuild
cp ./ZnnITCG.exe winBuild/
cp ./CrossPlatformBinaries/SDL3_Win/bin/SDL3.dll winBuild/
cp ./CrossPlatformBinaries/SDL3_Image_Win/bin/SDL3_image.dll winBuild/
cp ./LICENSE.txt winBuild/
cp -r ./Textures winBuild/
zip -r WindowsBuild ./winBuild
rm -f ./ZnnITCG.exe
rm -rf winBuild/