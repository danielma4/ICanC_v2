#include <gtest/gtest.h>
#include <ros/ros.h>
#include <ros/console.h>
#include "../src/obstacle_detector_node.cpp"
#include "../include/lidar_obstacle_detector/obstacle_detector.hpp"
#include "../include/lidar_obstacle_detector/box.hpp"

namespace lidar_obstacle_detector {

class ObstacleDetectorNodeTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // Setup code, if needed
  }

  virtual void TearDown() {
    // Cleanup code, if needed
  }

  ObstacleDetectorNode node;
};

TEST_F(ObstacleDetectorNodeTest, GetTimeDifference) {
  Box prev;
  Box curr;
  
  prev.timestamp = std::chrono::system_clock::time_point(std::chrono::seconds(10));
  curr.timestamp = std::chrono::system_clock::time_point(std::chrono::seconds(15));

  EXPECT_DOUBLE_EQ(node.getTimeDifference(prev, curr), 5.0);

  prev.timestamp = std::chrono::system_clock::time_point(std::chrono::seconds(10)) + std::chrono::milliseconds(500);
  curr.timestamp = std::chrono::system_clock::time_point(std::chrono::seconds(15)) + std::chrono::milliseconds(700);

  EXPECT_DOUBLE_EQ(node.getTimeDifference(prev, curr), 5.2);

  prev.timestamp = std::chrono::system_clock::time_point(std::chrono::milliseconds(100));
  curr.timestamp = std::chrono::system_clock::time_point(std::chrono::milliseconds(700));

  EXPECT_DOUBLE_EQ(node.getTimeDifference(prev, curr), .6);

  prev.timestamp = std::chrono::system_clock::time_point(std::chrono::microseconds(20000));
  curr.timestamp = std::chrono::system_clock::time_point(std::chrono::microseconds(700000));

  EXPECT_DOUBLE_EQ(node.getTimeDifference(prev, curr), .68);
}

TEST_F(ObstacleDetectorNodeTest, GetTwist) {
  constexpr double pi = 3.1415926535897932;

  Box prev;
  Box curr;

  //x is forward
  //y is to the left

  // pi / 4
  prev.position = Eigen::Vector3f(1.0, 2.0, 3.0);
  curr.position = Eigen::Vector3f(2.0, 3.0, 4.0);

  geometry_msgs::Twist twist = node.getTwist(prev, curr);

  EXPECT_DOUBLE_EQ(twist.linear.x, 1.0);
  EXPECT_DOUBLE_EQ(twist.linear.y, 1.0);
  EXPECT_DOUBLE_EQ(twist.linear.z, 1.0);
  EXPECT_DOUBLE_EQ(twist.angular.z, pi / 4);
  
  //-pi/4

  prev.position = Eigen::Vector3f(2.0, 3.0, 3.0);
  curr.position = Eigen::Vector3f(1.0, 2.0, 4.0);

  twist = node.getTwist(prev, curr);

  EXPECT_DOUBLE_EQ(twist.angular.z, -3 * pi / 4);

  //0
  prev.position = {-5.0, -5.0, 1000.0};
  curr.position = {5.0, -5.0, 0.0};

  twist = node.getTwist(prev, curr);

  EXPECT_DOUBLE_EQ(twist.linear.x, 10.0);
  EXPECT_DOUBLE_EQ(twist.linear.y, 0.0);
  EXPECT_DOUBLE_EQ(twist.linear.z, -1000.0);
  EXPECT_DOUBLE_EQ(twist.angular.z, 0.0);

  //pi / 2
  prev.position = {1.2, 1.5, 1.0};
  curr.position = {1.2, 3.0, 0.0};

  twist = node.getTwist(prev, curr);

  EXPECT_DOUBLE_EQ(twist.linear.x, 0.0);
  EXPECT_DOUBLE_EQ(twist.linear.y, 1.5);
  EXPECT_DOUBLE_EQ(twist.linear.z, -1.0);
  EXPECT_DOUBLE_EQ(twist.angular.z, pi / 2);

  //pi
  prev.position = {5.0, -5.0, 0.0};
  curr.position = {-5.0, -5.0, 1000.0};

  twist = node.getTwist(prev, curr);

  EXPECT_DOUBLE_EQ(twist.linear.x, -10.0);
  EXPECT_DOUBLE_EQ(twist.linear.y, 0.0);
  EXPECT_DOUBLE_EQ(twist.linear.z, 1000.0);
  EXPECT_DOUBLE_EQ(twist.angular.z, pi);

  //-pi/2
  prev.position = {1.7, 2.0, 0.0};
  curr.position = {1.7, -5.0, 10.0};

  twist = node.getTwist(prev, curr);

  EXPECT_DOUBLE_EQ(twist.linear.x, 0.0);
  EXPECT_DOUBLE_EQ(twist.linear.y, -7.0);
  EXPECT_DOUBLE_EQ(twist.linear.z, 10.0);
  EXPECT_DOUBLE_EQ(twist.angular.z, -pi / 2);
}

// TEST_F(ObstacleDetectorNodeTest, FindSameIDBox) {
//   std::vector<Box> prev_boxes_ = {
//       Box(3, Eigen::Vector3f(1.0, 2.0, 3.0), Eigen::Vector3f(2.0, 2.0, 2.0)),
//       Box(6, Eigen::Vector3f(4.0, 5.0, 6.0), Eigen::Vector3f(2.0, 2.0, 2.0)),
//       Box(5, Eigen::Vector3f(7.0, 8.0, 9.0), Eigen::Vector3f(2.0, 2.0, 2.0)),
//       Box(1, Eigen::Vector3f(7.0, 8.0, 9.0), Eigen::Vector3f(2.0, 2.0, 2.0)),
//       Box(2, Eigen::Vector3f(7.0, 8.0, 9.0), Eigen::Vector3f(2.0, 2.0, 2.0)),
//       Box(4, Eigen::Vector3f(7.0, 8.0, 9.0), Eigen::Vector3f(2.0, 2.0, 2.0)) };

//   std::sort(prev_boxes_.begin(), prev_boxes_.end(), [](Box b1, Box b2) -> bool {
//     return b1.id < b2.id;
//   });

//   EXPECT_EQ(prev_boxes_[0].id, 1);
//   EXPECT_EQ(prev_boxes_[1].id, 2);
//   EXPECT_EQ(prev_boxes_[2].id, 3);
//   EXPECT_EQ(prev_boxes_[3].id, 4);
//   EXPECT_EQ(prev_boxes_[4].id, 5);
//   EXPECT_EQ(prev_boxes_[5].id, 6);

//   Box curr_box(2, Eigen::Vector3f(10.0, 11.0, 12.0), Eigen::Vector3f(2.0, 2.0, 2.0));
//   node.setPrevBoxes(prev_boxes_);

//   Box found_box = node.findSameIDBox(curr_box);

//   EXPECT_EQ(found_box.id, prev_boxes_[1].id);

//   curr_box.id = 1;
//   found_box = node.findSameIDBox(curr_box);

//   EXPECT_EQ(found_box.id, prev_boxes_[0].id);

//   curr_box.id = 6;
//   found_box = node.findSameIDBox(curr_box);

//   EXPECT_EQ(found_box.id, prev_boxes_[5].id);

//   curr_box.id = 10;
//   found_box = node.findSameIDBox(curr_box);
  
//   EXPECT_EQ(found_box.id, curr_box.id);
// }

}  // namespace lidar_obstacle_detector

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "obstacle_detector_node_test");
  return RUN_ALL_TESTS();
}