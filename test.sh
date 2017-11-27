sudo ../octtool -b
cd build;
sudo make install
sudo make -j8 test ARGS=-j8
