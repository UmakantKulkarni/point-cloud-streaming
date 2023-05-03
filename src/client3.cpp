#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#define PORT 8000

int main(int argc, char const *argv[])
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    // Set server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Receive and save point cloud data
    while (1)
    {
        uint32_t cloud_size;
        if (recv(sock, &cloud_size, sizeof(cloud_size), 0) != sizeof(cloud_size))
        {
            printf("1 Failed to receive point cloud size\n");
            break;
        }
        std::vector<pcl::PointXYZ> buffer(cloud_size);
        // if (recv(sock, buffer.data(), sizeof(pcl::PointXYZ) * cloud_size, 0) != sizeof(pcl::PointXYZ) * cloud_size) {
        //     printf("2 Failed to receive point cloud data\n");
        //    break;
        //}
        cloud->width = cloud_size;
        cloud->height = 1;
        cloud->is_dense = true;
        cloud->points.resize(cloud->width * cloud->height);
        for (int i = 0; i < cloud->points.size(); ++i)
        {
            cloud->points[i].x = buffer[i].x;
            cloud->points[i].y = buffer[i].y;
            cloud->points[i].z = buffer[i].z;
        }
        pcl::io::savePCDFileASCII("pointcloud.pcd", *cloud);
        std::cerr << "Saved " << cloud->size() << " data points to test_pcd.pcd." << std::endl;
    }

    return 0;
}
