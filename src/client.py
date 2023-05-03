#!/usr/bin/env python3

import pyvista as pv
import socket
import struct
import numpy as np
from pyvista.utilities import xvfb
xvfb.start_xvfb()


# Define the host and port for the TCP server
host = 'localhost'
port = 8000

# Connect to the TCP server and receive the point cloud data
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((host, port))

# Receive the size of the point cloud data
size_bytes = client_socket.recv(4)
size = struct.unpack('i', size_bytes)[0]

# Receive the point cloud data and create a PyVista mesh
data = client_socket.recv(size)
n_points = len(data) // 12  # assuming 3 floats (12 bytes) per point
if len(data) % 12 != 0:
    print("Warning: Received data size is not a multiple of 12")
    data = data[:-(len(data) % 12)]  # truncate data to be a multiple of 12
cloud = pv.PolyData()
cloud.points = np.frombuffer(data, dtype=np.float32).reshape(-1, 3)
cloud.save("uk1.ply")

# Visualize the point cloud data using PyVista
#p = pv.Plotter()
#p.add_points(cloud.points, color='orange', point_size=2)
#p.show()

# Close the socket
client_socket.close()