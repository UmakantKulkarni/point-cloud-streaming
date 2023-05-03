#!/usr/bin/env python3

import open3d as o3d
from pyntcloud import PyntCloud

def ply_2_pcd(input_file = "", output_file = ""):
    # Load the PLY file
    pcd = o3d.io.read_point_cloud(input_file)

    # Save the PCD file
    o3d.io.write_point_cloud(output_file, pcd)


def pcd_2_ply(input_file = "", output_file = ""):
    # Load the PCD file
    cloud = PyntCloud.from_file(input_file)

    # Save the PLY file
    cloud.to_file(output_file)



if __name__ == '__main__':
    print("Utils Module")
    #pcd_2_ply(input_file = "", output_file = "")
    #ply_2_pcd(input_file = "", output_file = "")
