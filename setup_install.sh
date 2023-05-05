mydir=/home/kulkarnu
cd $mydir
#sudo apt-get -y install libboost-all-dev libeigen3-dev  libflann-dev python3-vtk7 qhull-bin openni-utils freeglut3-dev libusb-1.0-0-dev  freeglut3-dev pkg-config 
sudo apt-get -y install libpcl-dev python3-pcl pcl-tools cmake libgl1-mesa-glx xvfb libtbb-dev

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
wget https://www.vtk.org/files/release/9.2/VTK-9.2.6.tar.gz
tar -zxvf VTK-9.2.6.tar.gz 
cd VTK-9.2.6/
mkdir VTK-build
cd VTK-build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)
sudo make install

cd $mydir
git clone https://github.com/UmakantKulkarni/point-cloud-streaming
cd point-cloud-streaming
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
wget https://mpeg-pcc.org/Downloads/8i/single%20frame/longdress_viewdep_vox12.zip
unzip longdress_viewdep_vox12.zip
