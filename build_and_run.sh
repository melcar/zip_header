BUILD_DIRECTORY="build";
echo "building to: $BUILD_DIRECTORY";
if [ ! -d "$BUILD_DIRECTORY" ]; then
  mkdir "$BUILD_DIRECTORY";
fi
cmake -B"$BUILD_DIRECTORY" -Szip_getter;
cd "$BUILD_DIRECTORY";
make;
mv "zip_header_getter" "../"
cd ../
./zip_header_getter