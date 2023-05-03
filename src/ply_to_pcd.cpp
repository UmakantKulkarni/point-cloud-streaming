#include <pcl/io/ply_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

int main(int argc, char** argv)
{
  // Load PLY file
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::io::loadPLYFile(argv[1], *cloud);

  // Convert to PCD file
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_pcd(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::copyPointCloud(*cloud, *cloud_pcd);

  // Save PCD file
  pcl::io::savePCDFileBinary(argv[2], *cloud_pcd);

  return 0;
}

