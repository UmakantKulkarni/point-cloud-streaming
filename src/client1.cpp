#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/boost.h>
#include <pcl/point_types.h>
#include <pcl/common/time.h>

int main(int argc, char **argv) {
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query("localhost", "8000");
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    cloud->width = 5;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);

    boost::asio::ip::tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);

    std::vector<char> buf(cloud->points.size() * sizeof(cloud->points[0]));
    boost::asio::read(socket, boost::asio::buffer(buf));

    memcpy(cloud->points.data(), buf.data(), buf.size());

    pcl::io::savePCDFileASCII("pointcloud.pcd", *cloud);
    std::cout << "Point cloud saved to pointcloud.pcd" << std::endl;

    return 0;
}
