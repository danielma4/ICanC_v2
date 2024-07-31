#include <ros/ros.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <std_msgs/Float64.h>
#include <chrono>

class DetectedObjectsVisualizer
{
public:
    DetectedObjectsVisualizer()
    {
        //also throwing in latency calculation in here
        marker_pub = nh.advertise<visualization_msgs::MarkerArray>("detected_objects_markers", 10);
        sub = nh.subscribe("/danger_autoware", 10, &DetectedObjectsVisualizer::detectedObjectsCallback, this);
        node_timer = nh.createTimer(ros::Duration(0.2), std::bind(&DetectedObjectsVisualizer::clearMarkers, this, std::placeholders::_1), false);
        sub = nh.subscribe("/start", 10, &DetectedObjectsVisualizer::pubLatency, this);
        pub_latency = nh.advertise<std_msgs::Float64>("latency", 10);
    }

private:
    ros::NodeHandle nh;
    ros::Publisher marker_pub;
    ros::Subscriber sub;
    ros::Timer node_timer;
    std::vector<visualization_msgs::Marker> previous_markers;
    ros::Subscriber sub_start;
    ros::Publisher pub_latency;

    void clearMarkers(const ros::TimerEvent&)
    {
        visualization_msgs::MarkerArray marker_array;

        // Add delete markers for previous markers
        for (auto& marker : previous_markers) {
            marker.action = visualization_msgs::Marker::DELETE;
            marker_array.markers.push_back(marker);
        }

        // Clear the previous markers vector
        previous_markers.clear();

        marker_pub.publish(marker_array);
    }

    void detectedObjectsCallback(const autoware_msgs::DetectedObjectArray::ConstPtr& msg)
    {
        visualization_msgs::MarkerArray marker_array;

        for (size_t i = 0; i < msg->objects.size(); ++i)
        {
            visualization_msgs::Marker marker;
            marker.header.frame_id = msg->header.frame_id;
            marker.header.stamp = ros::Time::now();
            marker.ns = "detected_objects";
            marker.id = i;
            marker.type = visualization_msgs::Marker::CUBE;
            marker.action = visualization_msgs::Marker::ADD;

            marker.pose = msg->objects[i].pose;
            marker.scale.x = msg->objects[i].dimensions.x;
            marker.scale.y = msg->objects[i].dimensions.y;
            marker.scale.z = msg->objects[i].dimensions.z;

            marker.color.a = 0.8; // Semi-transparent
            marker.color.r = 1.0; // Full red
            marker.color.g = 0.0;
            marker.color.b = 0.0;

            marker_array.markers.push_back(marker);

            // Store the marker in the previous_markers vector
            previous_markers.push_back(marker);
        }

        marker_pub.publish(marker_array);
    }

    void pubLatency(const std_msgs::Float64::ConstPtr& msg) {
        const auto end = std::chrono::steady_clock::now();
        double end_time = std::chrono::duration<double>(end.time_since_epoch()).count();

        std_msgs::Float64 latency;

        latency.data = end_time - msg->data;

        pub_latency.publish(latency);
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "detected_objects_visualizer");

    DetectedObjectsVisualizer visualizer;

    ros::spin();
    return 0;
}
