#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <iostream>

using namespace std;

int main (int argc, char** argv)
{
    // Create a TCP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        cerr << "Error creating socket" << endl;
        return 1;
    }

    // Set up the server address and port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(8000);

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        cerr << "Error connecting to server" << endl;
        return 1;
    }

    // Receive the point cloud data
    uint32_t num_points;
    if (recv(sock, &num_points, sizeof(num_points), 0) < 0)
    {
        cerr << "Error receiving point cloud header" << endl;
        return 1;
    }

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    cloud->width = num_points;
    cloud->height = 1;
    cloud->is_dense = false;
    cloud->points.resize(cloud->width * cloud->height);

    uint32_t bytes_to_receive = num_points * sizeof(pcl::PointXYZ);
    char* buffer = reinterpret_cast<char*>(&cloud->points[0]);
    uint32_t total_bytes_received = 0;
    while (total_bytes_received < bytes_to_receive)
    {
        int bytes_received = recv(sock, buffer + total_bytes_received, bytes_to_receive - total_bytes_received, 0);
        if (bytes_received < 0)
        {
            cerr << "Error receiving point cloud data" << endl;
            return 1;
        }
        total_bytes_received += bytes_received;
    }

    // Close the socket
    close(sock);

    // Visualize the point cloud
    pcl::visualization::CloudViewer viewer("Point Cloud Viewer");
    viewer.showCloud(cloud);
    while (!viewer.wasStopped())
    {
        // Do nothing until the window is closed
    }

    return 0;
}

