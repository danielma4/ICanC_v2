#include <autoware_msgs/DetectedObjectArray.h>
#include <autoware_msgs/DetectedObject.h>
#include <geometry_msgs/PoseStamped.h>
#include <jsk_recognition_msgs/BoundingBox.h>
#include <jsk_recognition_msgs/BoundingBoxArray.h>
#include <ros/console.h>
#include <ros/ros.h>
#include <chrono>
#include "std_msgs/String.h"
#include <cstdlib>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <boost/shared_ptr.hpp>  // Include for shared_ptr
#include <boost/make_shared.hpp> // Include for make_shared
#include <tf/transform_datatypes.h>
#include <geometry_msgs/Quaternion.h>
#include "std_msgs/String.h"
#include <sstream>


namespace danger_publisher {

class DangerPublisherNode {
public:
  DangerPublisherNode() {
  ros::NodeHandle private_nh("~");

  std::string autoware_objects_topic;

  ROS_ASSERT(private_nh.getParam("autoware_objects_topic", autoware_objects_topic));
  ROS_ASSERT(private_nh.getParam("frontal_fov", frontal_fov));

  //set queue size to 1000 for monte carlo simulation
  sub_autoware = nh.subscribe(autoware_objects_topic, 10, &DangerPublisherNode::autoware_callback, this);

  pub_autoware_danger = nh.advertise<autoware_msgs::DetectedObjectArray>("danger_autoware", 10);
  pub_object_distance = nh.advertise<std_msgs::String>("info_topic", 10);
  }

protected:
  ros::NodeHandle nh;
  ros::Publisher pub_autoware_danger;
  ros::Publisher pub_object_distance; //for debugging purposes
  ros::Subscriber sub_autoware;
  double frontal_fov;


template <typename BoxType>
//extracts the 3D vector from box closes to coordinates [0, 0, 0]
  std::vector<double> getClosestPoint(const BoxType& box) {
    double xPosn, yPosn, zPosn;
    std::vector<double> closest_point;

    //if overlap ie min <= 0 <= max, choose 0
    if (box.pose.position.x - (box.dimensions.x / 2) <= 0 
    && 0 <= box.pose.position.x + (box.dimensions.x / 2)) {
      xPosn = 0.0;
    } else if (abs(box.pose.position.x - (box.dimensions.x / 2)) <= abs(box.pose.position.x + (box.dimensions.x / 2))) {
      //else we take the point closest to zero from the endpoints
      xPosn = box.pose.position.x - (box.dimensions.x / 2);
    } else if (abs(box.pose.position.x - (box.dimensions.x / 2)) > abs(box.pose.position.x + (box.dimensions.x / 2))) {
      xPosn = box.pose.position.x + (box.dimensions.x / 2);
    }

    if (box.pose.position.y - (box.dimensions.y / 2) <= 0 
    && 0 <= box.pose.position.y + (box.dimensions.y / 2)) {
      yPosn = 0.0;
    } else if (abs(box.pose.position.y - (box.dimensions.y / 2)) <= abs(box.pose.position.y + (box.dimensions.y / 2))) {
      yPosn = box.pose.position.y - (box.dimensions.y / 2);
    } else if (abs(box.pose.position.y - (box.dimensions.y / 2)) > abs(box.pose.position.y + (box.dimensions.y / 2))) {
      yPosn = box.pose.position.y + (box.dimensions.y / 2);
    }

    if (box.pose.position.z - (box.dimensions.z / 2) <= 0 
    && 0 <= box.pose.position.z + (box.dimensions.z / 2)) {
      zPosn = 0.0;
    } else if (abs(box.pose.position.z - (box.dimensions.z / 2)) <= abs(box.pose.position.z + (box.dimensions.z / 2))) {
      zPosn = box.pose.position.z - (box.dimensions.z / 2);
    } else if (abs(box.pose.position.z - (box.dimensions.z / 2)) > abs(box.pose.position.z + (box.dimensions.z / 2))) {
      zPosn = box.pose.position.z + (box.dimensions.z / 2);
    }

    closest_point.push_back(xPosn);
    closest_point.push_back(yPosn);
    closest_point.push_back(zPosn);
    return closest_point;
  }

//calculates the L2 norm or euclidean distance from origin
  double l2Norm(std::vector<double> point) {
    double dist = 0;

    for (auto coord : point) {
      dist += pow(coord, 2);
    }

    return sqrt(dist);
  }

//determines which section the object falls into
  int getSection(std::vector<double> point_on_box) {
    //axes are as follows:
    //positive x directly ahead
    //positive y left
    if (point_on_box[1] < -frontal_fov) {
      //section 1: y < -frontal_fov
      //object to the right
      return 1;
    } else if (point_on_box[1] > frontal_fov) {
      //section 3: y > frontal_fov
      //object to the left
      return 3;
    } else if (point_on_box[1] >= -frontal_fov && point_on_box[1] <= frontal_fov) {
      //section 2: x >= y and x >= -y
      return 2;
    } else {
      throw std::invalid_argument("invalid section");
    }
  }


//autoware based on personal velocity calculations
  void autoware_callback(const autoware_msgs::DetectedObjectArray::ConstPtr& msg) {
    // Process the incoming detected objects
    ros::NodeHandle private_nh("~");
    autoware_msgs::DetectedObjectArray dangerous_objects;
    dangerous_objects.header.frame_id = msg->header.frame_id;

    for (const auto& box : msg->objects) {
      double reaction_time_allowed;
      ROS_ASSERT(private_nh.getParam("reaction_time_allowed", reaction_time_allowed));

      //find the closest on bbox to sensor
      std::vector<double> closest_point = DangerPublisherNode::getClosestPoint(box);
      //find distance of said point to sensor
      double closest_point_distance = DangerPublisherNode::l2Norm(closest_point);
      //determine section which object is in
      int section = DangerPublisherNode::getSection(closest_point);
      //determine overall speed of the object
      double speed = getSpeed(box);

      //determine the distance which is deemed dangerous wrt speed of object
      //allow for "reaction_time_allowed" seconds to react
      double danger_threshold_distance = speed * reaction_time_allowed;


      if (closest_point_distance <= danger_threshold_distance
      && DangerPublisherNode::isFacingMeAutoware(box, section)) {
        dangerous_objects.objects.push_back(box);

        std_msgs::String msg;
        std::ostringstream oss;
        double degree = box.velocity.angular.z / 3.14 * 180.0;

        oss << "id: " << box.id
        << "; distance: " << closest_point_distance << "m"
        << "; speed: " << speed << "m/s"
        << "; section: " << section
        << "; orientation: " << degree
        << "; closest point: " << closest_point[0] << ", "
        << closest_point[1] << ", " << closest_point[2];

        msg.data = oss.str();
        pub_object_distance.publish(msg);
      }
    }

    if (!dangerous_objects.objects.empty()) {
      autoware_msgs::DetectedObjectArray::Ptr bboxPtr = boost::make_shared<autoware_msgs::DetectedObjectArray>(dangerous_objects);
      autoware_msgs::DetectedObjectArray::ConstPtr constBboxPtr = boost::const_pointer_cast<const autoware_msgs::DetectedObjectArray>(bboxPtr);
      pub_autoware_danger.publish(std::move(bboxPtr));
    }

    ROS_INFO("Received DetectedObjectArray message with %lu objects, published array with %lu objects", msg->objects.size(), dangerous_objects.objects.size());
  }
  //determines the velocity of box
  double getSpeed(const autoware_msgs::DetectedObject& box) {
    std::vector<double> linear = {box.velocity.linear.x, box.velocity.linear.y, box.velocity.linear.z};
    double distance = l2Norm(linear);
    //we placed time elapsed in score field
    return distance / box.score;
  }

  //determines if a detected object is moving towards the sensor
  bool isFacingMeAutoware(const autoware_msgs::DetectedObject& box, int section) {
    constexpr double pi = 3.14159;
    bool facing;
    switch(section) {
      case 1:
        //object to the right
        facing = box.velocity.angular.z >= (pi / 12) && box.velocity.angular.z <= (11 * pi / 12);
        break;

      case 2:
        //object in front
         facing = (box.velocity.angular.z >= 7 * pi / 12 && box.velocity.angular.z <= pi)
         || (box.velocity.angular.z <= -7 * pi / 12 && box.velocity.angular.z >= -pi);
        //facing = true;
        break;

      case 3:
        //object to the left
        facing = box.velocity.angular.z <= (-pi / 12) && box.velocity.angular.z >= (-11 * pi / 12);
        break;

      default:
        facing = true;
        break;
    }
    return facing;
  }

}; //DangerPublisherNode class

} //danger_publisher namespace


int main(int argc, char **argv) {
  ros::init(argc, argv, "danger_publisher_node");
  danger_publisher::DangerPublisherNode danger_publisher_node;
  ros::spin();
  return 0;
}
