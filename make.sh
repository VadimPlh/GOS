rm -rf server/build
rm -rf client/build

mkdir server/build
cd server/build
cmake ..
make server -j 10

cd ../..

mkdir client/build
cd client/build
cmake ..
make client -j 10