mydir=/home/kulkarnu
cd $mydir
#sudo apt-get -y install libboost-all-dev libeigen3-dev  libflann-dev python3-vtk7 qhull-bin openni-utils freeglut3-dev libusb-1.0-0-dev libudev-dev python3-pcl pcl-tools cmake freeglut3-dev pkg-config
sudo apt-get -y install libpcl-dev python3-pcl pcl-tools cmake

pip3 install -U open3d PyntCloud pyvista

cd $mydir
mkdir vs
cd vs
wget https://github.com/PointCloudLibrary/pcl/archive/refs/tags/pcl-1.12.0.tar.gz
tar xvzf pcl-1.12.0.tar.gz 
cd pcl-pcl-1.12.0
mkdir build
cd build
cmake -DBUILD_apps=ON -DBUILD_examples=ON -DCMAKE_BUILD_TYPE=Debug ..
make -j2
sudo make -j2 install

cd $mydir
git clone https://github.com/UmakantKulkarni/point-cloud-streaming
cd point-cloud-streaming
mkdir build
cd build
cmake ..
make