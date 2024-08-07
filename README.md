# ICanC: Improving Camera-based Object Detection and Energy Conservation in Low-Illumination Environments (UD REU Project)

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Dependencies](#dependencies)
- [Environment](#environment)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [License](#license)
- [Contact](#contact)

## Introduction
This project introduces ICanC (I Can See), a novel system utilizing sensor fusion to optimize camera object detection and energy consumption in autonomous vehicle headlights.
The paper explains the system in-depth and can be found [here](https://github.com/danielma4/ICanC_v2/).

## Features
Key features include:
- LiDAR and camera object detection: [LiDAR](https://github.com/SS47816/lidar_obstacle_detector) is forked and expanded upon, [YOLOv3 ROS](https://github.com/leggedrobotics/darknet_ros) is utilized for camera object detection.
- Object attribute calculation: A [Kalman filter](https://github.com/hmartiro/kalman-cpp) is implemented to accurately calculate and estimate key states such as position, velocity, and orientation between frames.
- Danger labeling: Logic implemented to determine the danger of each detected object
- Light controlling: Logic implemented to determine when headlights can be turned off to optimize headlight usage at night.
- Parameter adjustment: Dynamic reconfiguration employed in obstacle detecting node, as well as adjustable parameters for various calculations in launch files.

## Dependencies
- [ROS](http://wiki.ros.org/melodic)
- [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)
- [OpenCV](https://opencv.org/)
- [Boost](https://www.boost.org/)
- jsk-recognition-msgs

## Environment
- Ubuntu 18.04
- ROS Melodic
- Ran on Nvidia GeForce RTX 2080 (compute capability 7.5)

## Installation
   ```bash
   # clone the repo
    mkdir ~/catkin_ws
    cd ~/catkin_ws
    git clone --recursive https://github.com/danielma4/ICanC_v2.git

    # install dependencies & build
    rosdep install --from-paths src --ignore-src -r -y
    catkin_make # or catkin_make -DPYTHON_EXECUTABLE=/usr/bin/python3
    source devel/setup.bash
```

## Usage
Bagfiles recorded for testing can be found [here](https://drive.google.com/drive/u/0/folders/1mb5daV7iy4aq_AqgWtrdmSJ1GrRKI0bv).
```bash
# Run rosbags with the system:
rosbag play <bagfile_name.bag>
```
```bash
# System launch:
roslaunch lidar_obstacle_detector system.launch
```
The parameters were adjusted to work with the Zebra, a general-purpose indoor autonomous vehicle, and its topics. Adjust topic names in launch file as needed.

```bash
# To visualize dangerous objects in rviz:
rosrun lidar_obstacle_detector visualize_danger_node
```
The system was also run in [CARLA](https://carla.org//) with the [CARLA ROS bridge](https://github.com/carla-simulator/ros-bridge).

## Testing
Various unit tests were written with GTest. To run, a few things need to be done:
- Comment out main in lidar_obstacle_detector/src nodes
- Change specifiers from private/protected to public

Then:
```bash
cd ~/catkin_ws
catkin_make run_tests
```

Furthermore, a Monte Carlo simulation was created. To run, change queue sizes of publishers and subscribers to a suitable size (i.e. 1000).
```bash
rosrun lidar_obstacle_detector simulation_test_node
# In a new terminal
rostopic echo /monte_carlo
# In a new terminal
rostopic pub /service_topic std_msgs/Int32 "data: <num_boxes>"
```

## License
I don't know what to put here yet.

## Contact
[CAR LAB](https://www.thecarlab.org/home)

Feel free to reach me at ma.dan[at]northeastern[dot]edu.
  
