/* box.hpp

 * Copyright (C) 2021 SS47816

 * Implementation of the Box and BoxQ class

**/

#pragma once

#include <Eigen/Geometry>
#include <chrono>
#include "lidar_obstacle_detector/kalman-cpp/kalman.hpp"

struct Box {
 public:
  int id;
  Eigen::Vector3f position;
  Eigen::Vector3f dimension;
  Eigen::Quaternionf quaternion;
  std::chrono::time_point<std::chrono::system_clock> timestamp;
  KalmanFilter kf;

  Box() {}

  Box(int id, Eigen::Vector3f position, Eigen::Vector3f dimension)
      : id(id),
        position(position),
        dimension(dimension),
        quaternion(Eigen::Quaternionf(1, 0, 0, 0)),
        timestamp(std::chrono::system_clock::now()) {}

  Box(int id, Eigen::Vector3f position, Eigen::Vector3f dimension,
      Eigen::Quaternionf quaternion)
      : id(id),
        position(position),
        dimension(dimension),
        quaternion(quaternion),
        timestamp(std::chrono::system_clock::now()) {}

  void initKalman(double t0, const Eigen::VectorXd& x0) {
    double dt = 0.1;  // Example time step

    //state vector is as follows
    //[posx, posy, posz, velx, vely, velz]

    Eigen::MatrixXd A(6, 6);
    Eigen::MatrixXd C(3, 6);
    Eigen::MatrixXd Q(6, 6);
    Eigen::MatrixXd R(3, 3);
    Eigen::MatrixXd P(6, 6);

    A << 1, 0, 0, dt, 0, 0,
         0, 1, 0, 0, dt, 0,
         0, 0, 1, 0, 0, dt,
         0, 0, 0, 1, 0, 0,
         0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 0, 1;

    C << 1, 0, 0, 0, 0, 0,
         0, 1, 0, 0, 0, 0,
         0, 0, 1, 0, 0, 0;

    Q << 0.1, 0, 0, 0, 0, 0,
         0, 0.1, 0, 0, 0, 0,
         0, 0, 0.1, 0, 0, 0,
         0, 0, 0, 0.2, 0, 0,
         0, 0, 0, 0, 0.2, 0,
         0, 0, 0, 0, 0, 0.2;

    R << 0.1, 0, 0,
         0, 0.1, 0,
         0, 0, 0.1;

    P << 1, 0, 0, 0, 0, 0,
         0, 1, 0, 0, 0, 0,
         0, 0, 1, 0, 0, 0,
         0, 0, 0, 1, 0, 0,
         0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 0, 1;

    this->kf = KalmanFilter(dt, A, C, Q, R, P);
    kf.init(t0, x0);
  }

  Eigen::VectorXd filter(const Eigen::VectorXd& y, double dt) {
    Eigen::MatrixXd A(6, 6);
    A << 1, 0, 0, dt, 0, 0,
         0, 1, 0, 0, dt, 0,
         0, 0, 1, 0, 0, dt,
         0, 0, 0, 1, 0, 0,
         0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 0, 1;

    kf.update(y, dt, A);

    return kf.state();
  }

  void copyKalman(const KalmanFilter& other) {
    KalmanFilter kf(other);
  }

  bool isSame(const Box& that) {
    return position.isApprox(that.position)
    && dimension.isApprox(that.dimension)
    && quaternion.isApprox(that.quaternion);
  }

  
};
