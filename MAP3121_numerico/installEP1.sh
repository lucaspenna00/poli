git clone https://github.com/lucaspenna00/MNISTDigitClassifier
cd ~/Numerical_Methods/build
cmake .
make
ulimit -s unlimited
./ep1 -j4

