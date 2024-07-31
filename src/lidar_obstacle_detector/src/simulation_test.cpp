#include <autoware_msgs/DetectedObjectArray.h>
#include <autoware_msgs/DetectedObject.h>
#include <std_msgs/Int32.h>
#include <ros/console.h>
#include <ros/ros.h>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <ctime>
#include <string>
#include <chrono>
#include <iostream>
#include <sstream>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>

namespace simulation_test {

    class SimulationTestNode {
    public:
        SimulationTestNode() {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            srand(seed);
            ros::NodeHandle private_nh("~");

            std::string autoware_objects_topic;
            std::string danger_topic;
            ROS_ASSERT(private_nh.getParam("autoware_objects_topic", autoware_objects_topic));
            ROS_ASSERT(private_nh.getParam("danger_topic", danger_topic));
            ROS_ASSERT(private_nh.getParam("num_avgs", num_avgs));

            pub_boxes = nh.advertise<autoware_msgs::DetectedObjectArray>(autoware_objects_topic, 1000);
            pub_ratios = nh.advertise<std_msgs::String>("/monte_carlo", 1000);
            sub_danger = nh.subscribe(danger_topic, 1000, &SimulationTestNode::getDistribution, this);
            sub_service = nh.subscribe("/service_topic", 1, &SimulationTestNode::serviceCallback, this);

            ROS_INFO("SimulationTestNode initialized successfully");
        }

    private:
        ros::Publisher pub_boxes;
        ros::Publisher pub_ratios;
        ros::Subscriber sub_danger;
        ros::Subscriber sub_service;
        ros::NodeHandle nh;
        int currN;
        int num_avgs;
        //represents multiple averages for number of objects labeled dangerous
        //with multiple values to allow for averaging
        std::vector<double> averages;

        //receives message, runs monte carlo simulation with n boxes
        void serviceCallback(const std_msgs::Int32::ConstPtr& n) {
            ROS_INFO("Service callback triggered with n = %d", n->data);
            averages.clear();

            publishRandomObjects(n->data);
        }

        //formulates random data and publishes it to the system topics
        void publishRandomObjects(int n) {
            ros::NodeHandle private_nh("~");
            ros::Rate rate(0.2);

            currN = n;

            for (int i = 0; i < num_avgs; i++) {
                autoware_msgs::DetectedObjectArray bboxes;
                bboxes.objects = formulateBboxes(n);

                pub_boxes.publish(std::move(bboxes));
                ROS_INFO("Published %d objects", (int)bboxes.objects.size());
            }
        }

        //adds data to distribution
        void getDistribution(const autoware_msgs::DetectedObjectArray::ConstPtr& boxes) {
            ROS_INFO("getDistribution callback triggered with %d boxes", (int)boxes->objects.size());
            //#danger/total published = %danger
            double avg = (double(boxes->objects.size())) / currN;
            ROS_INFO("avg being pushed: %f", avg);

            averages.push_back(avg);

            publish_ratios();
        }

        //formulates n random bounding boxes
        std::vector<autoware_msgs::DetectedObject> formulateBboxes(int n) {
            std::vector<autoware_msgs::DetectedObject> bboxes;
            double radian;
            int angle, speed, x_squared1, y_squared1, x_squared2, y_squared2, dist;

            for (int i = 0; i < n; i += 1) {
                autoware_msgs::DetectedObject bbox;
                geometry_msgs::Pose pose;
                geometry_msgs::Twist twist;

                dist = rand() % 60 + 1;

                x_squared1 = rand() % ((int)(pow(dist, 2) + 1));
                y_squared1 = pow(dist, 2) - x_squared1;
                
                pose.position.x = sqrt(x_squared1);
                pose.position.y = rand() % 2 ? sqrt(y_squared1) : -sqrt(y_squared1);
                pose.position.z = 0;

                angle = rand() % 181;
                radian = ((double)angle) * 3.14159 / 180.0;

                twist.angular.z = rand() % 2 ? radian : -radian;

                //should note, this translation will not match orientation calculation
                speed = rand() % 60 + 1;

                x_squared2 = rand() % ((int)(pow(speed, 2) + 1));
                y_squared2 = pow(speed, 2) - x_squared2;

                twist.linear.x = sqrt(x_squared2);
                twist.linear.y = sqrt(y_squared2);
                twist.linear.z = 0.0; 

                bbox.dimensions.x = bbox.dimensions.y = bbox.dimensions.z = 0.0;
                bbox.score = 1.0;
                bbox.pose = pose;
                bbox.velocity = twist;
                bboxes.emplace_back(bbox);
            }

            return bboxes;
        }

        void publish_ratios() {
            double total_average = accumulate(averages.begin(), averages.end(), 0.0) / num_avgs; 
            ROS_INFO("num_avgs: %d, size of array: %d", num_avgs, averages.size());

            std_msgs::String msg;
            std::ostringstream percents;

            percents << currN << " average pct danger detected: " << total_average;

            msg.data = percents.str();
            pub_ratios.publish(msg);
            ROS_INFO("Published ratios");
        }

    };

} //namespace

int main(int argc, char **argv) {
  ros::init(argc, argv, "simulation_test_node");
  simulation_test::SimulationTestNode simulation_test_node;
  ros::spin();
  return 0;
}
