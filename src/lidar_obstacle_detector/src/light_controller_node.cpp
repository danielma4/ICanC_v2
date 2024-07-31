#include <autoware_msgs/DetectedObjectArray.h>
#include <jsk_recognition_msgs/BoundingBox.h>
#include <jsk_recognition_msgs/BoundingBoxArray.h>
#include <ros/console.h>
#include <ros/ros.h>
#include <cstdlib>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>

namespace light_controller {

    class LightControllerNode {
    public:
        LightControllerNode() {
            ros::NodeHandle private_nh("~");

            std::string autoware_danger_topic;

            ROS_ASSERT(private_nh.getParam("autoware_danger_topic", autoware_danger_topic));
            ROS_ASSERT(private_nh.getParam("light_on_time", light_on_time));

            sub_autoware_danger = nh.subscribe(autoware_danger_topic, 10, &LightControllerNode::autoware_callback, this);
            pub_light = nh.advertise<std_msgs::Int32>("light_topic", 10);
            time_pub = nh.advertise<std_msgs::Int32>("countdown", 10);
            pub_start = nh.advertise<std_msgs::Float64>("start", 10);

            // timer calls timerCallback every second
            nodeTimer = nh.createTimer(ros::Duration(1.0), std::bind(&LightControllerNode::timerCallback, this, std::placeholders::_1), false);
        }

    private:
        ros::NodeHandle nh;
        ros::Subscriber sub_autoware_danger;
        ros::Publisher pub_light;
        ros::Publisher time_pub;
        ros::Publisher pub_start;
        int light_on = 0;
        int light_on_time;
        int timer = 0;
        ros::Timer nodeTimer;

        // called everytime receives message from autoware danger topic
        void autoware_callback(const autoware_msgs::DetectedObjectArray::ConstPtr &object)
        {
            // case 1: light off
            if (!light_on) {
                // turn on light, set timer
                light_on = 1;
                timer = light_on_time;
                LightControllerNode::pubLight();
            }
            else if (light_on && timer <= 1) {
                // case 2: light on, timer \le 1 => theres still danger, reset timer
                timer = light_on_time;
            }
            // case 3: light on, timer > 1 -> do nothing

            std_msgs::Float64 msg;
            msg.data = object->objects[0].variance.x;
            pub_start.publish(msg);
        }

        // Timer callback function
        void timerCallback(const ros::TimerEvent&) {
            if (timer > 0) {
                std_msgs::Int32 msg;
                msg.data = timer;
                time_pub.publish(msg);
                timer--;
            }
            else {
                light_on = 0;
            }
            LightControllerNode::pubLight();
        }

        void pubLight() {
            std_msgs::Int32 msg;
            msg.data = light_on;
            pub_light.publish(msg);
        }
    };

} // namespace light_controller

int main(int argc, char **argv) {
    ros::init(argc, argv, "light_controller_node");
    light_controller::LightControllerNode light_controller_node;
    ros::spin();
    return 0;
}