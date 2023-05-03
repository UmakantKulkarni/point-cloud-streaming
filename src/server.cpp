#include <pcl/io/pcd_io.h>
#include <pcl/io/io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

typedef pcl::PointXYZRGB PointT;
typedef pcl::PointCloud<PointT> PointCloud;

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [pcd/ply file] [x y z]" << std::endl;
        return -1;
    }

    std::string filename = argv[1];
    //float x = std::stof(argv[2]);
    //float y = std::stof(argv[3]);
    //float z = std::stof(argv[4]);

    PointCloud::Ptr cloud(new PointCloud);
    if (pcl::io::loadPLYFile(filename, *cloud) == -1) {
        std::cerr << "Failed to load file " << filename << std::endl;
        return -1;
    }

    pcl::VoxelGrid<PointT> sor;
    sor.setInputCloud(cloud);
    sor.setLeafSize(0.01f, 0.01f, 0.01f);
    sor.filter(*cloud);

    boost::asio::io_service io_service;

    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8000));
    tcp::socket socket(io_service);
    acceptor.accept(socket);

    std::cout << "Sending point cloud data..." << std::endl;
    std::vector<char> buf(cloud->points.size() * sizeof(PointT));
    for (size_t i = 0; i < cloud->points.size(); ++i) {
        PointT& point = cloud->points[i];
        //if (point.x == x && point.y == y && point.z == z) {
        //    memcpy(buf.data() + i * sizeof(PointT), &point, sizeof(PointT));
        //}
        memcpy(buf.data() + i * sizeof(PointT), &point, sizeof(PointT));
    }
    boost::asio::write(socket, boost::asio::buffer(buf));

    std::cout << "Done." << std::endl;

    return 0;
}