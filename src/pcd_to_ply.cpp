#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>

int main(int argc, char** argv)
{
  // Load the PCD file
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_pcd(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::io::loadPCDFile(argv[1], *cloud_pcd);

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::copyPointCloud(*cloud_pcd, *cloud);

  // Save the PLY file
  pcl::io::savePLYFileASCII(argv[2], *cloud);

  return 0;
}