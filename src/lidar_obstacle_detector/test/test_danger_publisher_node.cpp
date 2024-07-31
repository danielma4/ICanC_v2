#include <gtest/gtest.h>
#include <ros/ros.h>
#include <ros/console.h>
#include <jsk_recognition_msgs/BoundingBox.h>
#include <jsk_recognition_msgs/BoundingBoxArray.h>
#include <autoware_msgs/DetectedObject.h>
#include "../src/danger_publisher_node.cpp"
#include <boost/shared_ptr.hpp>  // Include for shared_ptr
#include <boost/make_shared.hpp> // Include for make_shared

using namespace danger_publisher; 

// Test fixture for DangerPublisherNode tests
class DangerPublisherNodeTest : public ::testing::Test {
protected:
  ros::NodeHandle nh;

  // Set up before each test
  void SetUp() override {
    // Initialize ROS node handle if necessary
    nh = ros::NodeHandle("~");
  }

  // Clean up after each test
  void TearDown() override {
    // Perform any necessary clean-up
  }
};

// Test fixture for specific function tests
class DangerPublisherNodeFunctionTest : public DangerPublisherNodeTest {
  // No additional setup or teardown needed
};


// Tests for getClosestPoint function
TEST_F(DangerPublisherNodeFunctionTest, GetClosestPointTest) {
  DangerPublisherNode node;

  jsk_recognition_msgs::BoundingBox box1;
  box1.pose.position.x = 2.0;
  box1.pose.position.y = 2.0;
  box1.pose.position.z = .99;
  box1.dimensions.x = 4.0;
  box1.dimensions.y = 6.0;
  box1.dimensions.z = 2.0;

  jsk_recognition_msgs::BoundingBox box2;
  box2.pose.position.x = -6.0;
  box2.pose.position.y = 3.3;
  box2.pose.position.z = 0.0;
  box2.dimensions.x = 1.4;
  box2.dimensions.y = 6.0;
  box2.dimensions.z = 2.0;

  std::vector<double> closest_point2 = node.getClosestPoint(box2);
  
//x and y error
  EXPECT_FLOAT_EQ(closest_point2[0], -5.3000002);
  EXPECT_FLOAT_EQ(closest_point2[1], 0.3);
  EXPECT_FLOAT_EQ(closest_point2[2], 0.0);

  std::vector<double> closest_point = node.getClosestPoint(box1);

  EXPECT_FLOAT_EQ(closest_point[0], 0.0);
  EXPECT_FLOAT_EQ(closest_point[1], 0.0);
  EXPECT_FLOAT_EQ(closest_point[2], 0.0);

  //closest_point.clear();
  //std::vector<double> closest_point2 = node.getClosestPoint(box2);

//x and y error
  EXPECT_FLOAT_EQ(closest_point2[0], -5.3000002);
  EXPECT_FLOAT_EQ(closest_point2[1], 0.3);
  EXPECT_FLOAT_EQ(closest_point2[2], 0.0);
}

// Tests for l2Norm function
TEST_F(DangerPublisherNodeFunctionTest, L2NormTest) {
  DangerPublisherNode node;
  std::vector<double> point1 = {3.0, 4.0, 0.0};
  std::vector<double> point2 = {1.0, 5.0, -2.0};
  std::vector<double> point3 = {1.1, 2.2, 3.3, 4.4};
  std::vector<double> point4 = {0.1};

  EXPECT_FLOAT_EQ(node.l2Norm(point1), 5.0);
  EXPECT_FLOAT_EQ(node.l2Norm(point2), 5.4772258);
  EXPECT_FLOAT_EQ(node.l2Norm(point3), 6.0249486);
  EXPECT_FLOAT_EQ(node.l2Norm(point4), 0.1);
}

// Tests for getSection function
TEST_F(DangerPublisherNodeFunctionTest, GetSectionTest) {
  DangerPublisherNode node;
  //frontal_fov for this test = 3.0
  std::vector<double> point = {1.0, -2.0, 0.0};
  EXPECT_EQ(node.getSection(point), 1);

  point = {1000.0, 3.0, 0.0};
  EXPECT_EQ(node.getSection(point), 3);

  point = {1000.0, 0.1, 0.0};
  EXPECT_EQ(node.getSection(point), 2);

  point = {2.0, 7.0, 0.0};
  EXPECT_EQ(node.getSection(point), 3);

  point = {5.0, -19.0, 1000.1};
  EXPECT_EQ(node.getSection(point), 1);

  point = {.1, -.5, -299.5};
  EXPECT_EQ(node.getSection(point), 2);

  point = {0.0, -.6, 0.0};
  EXPECT_EQ(node.getSection(point), 1);
}


//Tests for getSpeed
TEST_F(DangerPublisherNodeFunctionTest, GetSpeedTest) {
  DangerPublisherNode node;
  autoware_msgs::DetectedObject box1, box2, box3;

  box1.velocity.linear.x = 3.0;
  box1.velocity.linear.y = 4.0;
  box1.velocity.linear.z = 5.0;
  box1.score = 2.0;

  EXPECT_DOUBLE_EQ(node.getSpeed(box1), 3.5355);

  box2.velocity.linear.x = -3.0;
  box2.velocity.linear.y = -4.0;
  box2.velocity.linear.z = 5.0;
  box2.score = 2.0;

  EXPECT_DOUBLE_EQ(node.getSpeed(box2), 3.5355);

  box3.velocity.linear.x = 2.0;
  box3.velocity.linear.y = 6.0;
  box3.velocity.linear.z = -2.0;
  box3.score = 0.5;

  EXPECT_DOUBLE_EQ(node.getSpeed(box3), 13.266);
}


//Tests for isFacingMeAutoware
TEST_F(DangerPublisherNodeFunctionTest, IsFacingMeAutoware) {
  DangerPublisherNode node;
  autoware_msgs::DetectedObject box1, box2, box3, box4, box5, box6, box7, box8, box9;
  constexpr double pi = 3.14159;

  box1.velocity.angular.z = 0.0;
  box2.velocity.angular.z = pi / 2.0;
  box3.velocity.angular.z = pi;
  box4.velocity.angular.z = -pi / 2.0;
  box5.velocity.angular.z = pi / 6;
  box6.velocity.angular.z = -pi / 4;
  box7.velocity.angular.z = pi / 12;
  box8.velocity.angular.z = pi / 13;
  box9.velocity.angular.z = -pi / 12;

  EXPECT_FALSE(node.isFacingMeAutoware(box1, 1));
  EXPECT_FALSE(node.isFacingMeAutoware(box1, 2));
  EXPECT_FALSE(node.isFacingMeAutoware(box1, 3));

  EXPECT_TRUE(node.isFacingMeAutoware(box2, 1)); 
  EXPECT_FALSE(node.isFacingMeAutoware(box2, 2));
  EXPECT_FALSE(node.isFacingMeAutoware(box2, 3));

  EXPECT_FALSE(node.isFacingMeAutoware(box3, 1));
  EXPECT_TRUE(node.isFacingMeAutoware(box3, 2));
  EXPECT_FALSE(node.isFacingMeAutoware(box3, 3)); 

  EXPECT_FALSE(node.isFacingMeAutoware(box4, 1));
  EXPECT_FALSE(node.isFacingMeAutoware(box4, 2));
  EXPECT_TRUE(node.isFacingMeAutoware(box4, 3));

  EXPECT_TRUE(node.isFacingMeAutoware(box5, 1));
  EXPECT_FALSE(node.isFacingMeAutoware(box5, 2));
  EXPECT_FALSE(node.isFacingMeAutoware(box5, 3));

  EXPECT_FALSE(node.isFacingMeAutoware(box6, 1));
  EXPECT_FALSE(node.isFacingMeAutoware(box6, 2));
  EXPECT_TRUE(node.isFacingMeAutoware(box6, 3));

  EXPECT_TRUE(node.isFacingMeAutoware(box7, 1));
  EXPECT_FALSE(node.isFacingMeAutoware(box7, 2));
  EXPECT_FALSE(node.isFacingMeAutoware(box7, 3));

  EXPECT_FALSE(node.isFacingMeAutoware(box8, 1));
  EXPECT_FALSE(node.isFacingMeAutoware(box8, 2));
  EXPECT_FALSE(node.isFacingMeAutoware(box8, 3));

  EXPECT_FALSE(node.isFacingMeAutoware(box9, 1));
  EXPECT_FALSE(node.isFacingMeAutoware(box9, 2));
  EXPECT_TRUE(node.isFacingMeAutoware(box9, 3));
}

/*
boost::shared_ptr<const jsk_recognition_msgs::BoundingBox> waitForMessage(const std::string& topic, const ros::Duration& timeout) {
    // Use boost::shared_ptr and boost::const_pointer_cast to handle conversion
    boost::shared_ptr<const jsk_recognition_msgs::BoundingBox> msg;
    jsk_recognition_msgs::BoundingBox::ConstPtr raw_msg = ros::topic::waitForMessage<jsk_recognition_msgs::BoundingBox>(topic, timeout);
    
    if (raw_msg) {
        msg = boost::const_pointer_cast<const jsk_recognition_msgs::BoundingBox>(raw_msg);
    } else {
        throw std::runtime_error("Timeout waiting for message on topic: " + topic);
    }
    
    return msg;
}

// jsk_callback tests
TEST_F(DangerPublisherNodeTest, JSKCallbackTest) {
  // Publisher to simulate incoming bounding boxes
  ros::Publisher pub = nh.advertise<jsk_recognition_msgs::BoundingBoxArray>("jsk_bboxes_topic", 1);

  DangerPublisherNode node;

  jsk_recognition_msgs::BoundingBoxArray bbox_array;
  jsk_recognition_msgs::BoundingBox section1_toward_far, section1_away_close, section12_border_away_close, 
  section2_toward_close, section2_away_far, section23_border_towards_far, section3_away_far, section3_toward_close;
  //0 = no danger, 1 = danger
  //0, 0, 1, 1, 0, 0, 0, 1

  //section 1: x < y
  //section 2: x < -y
  //keep dimensions at 2, we aren't testing this and no need to overcomplicate 

  //note: danger_threshold currently 5 for sections 1, 3 and 10 for section 2 but this will be tweaked
  //so tests may fail because of that
  //as long as preliminary tests pass for now, its fine

  //boxes
  section1_toward_far.pose.position.x = 10.0;
  section1_toward_far.pose.position.y = 12.0;
  section1_toward_far.pose.position.z = 10.0;
  section1_toward_far.dimensions.x = 2.0;
  section1_toward_far.dimensions.y = 2.0;
  section1_toward_far.dimensions.z = 2.0;
  section1_toward_far.pose.orientation.x = 0.0;
  section1_toward_far.pose.orientation.y = 0.0;
  section1_toward_far.pose.orientation.z = .2587;
  section1_toward_far.pose.orientation.w = .9659;

  section1_away_close.pose.position.x = 2.0;
  section1_away_close.pose.position.y = 3.0;
  section1_away_close.pose.position.z = 2.0;
  section1_away_close.dimensions.x = 2.0;
  section1_away_close.dimensions.y = 2.0;
  section1_away_close.dimensions.z = 2.0;
  section1_away_close.pose.orientation.x = 0.0;
  section1_away_close.pose.orientation.y = 0.0;
  section1_away_close.pose.orientation.z = .9913;
  section1_away_close.pose.orientation.w = .1309;

  section12_border_away_close.pose.position.x = 3.0;
  section12_border_away_close.pose.position.y = 3.0;
  section12_border_away_close.pose.position.z = 0.0;
  section12_border_away_close.dimensions.x = 2.0;
  section12_border_away_close.dimensions.y = 2.0;
  section12_border_away_close.dimensions.z = 2.0;
  section12_border_away_close.pose.orientation.x = 0.0;
  section12_border_away_close.pose.orientation.y = 0.0;
  section12_border_away_close.pose.orientation.z = .9659;
  section12_border_away_close.pose.orientation.w = -.2587;

  section2_toward_close.pose.position.x = 2.0;
  section2_toward_close.pose.position.y = 1.5;
  section2_toward_close.pose.position.z = .1;
  section2_toward_close.dimensions.x = 2.0;
  section2_toward_close.dimensions.y = 2.0;
  section2_toward_close.dimensions.z = 2.0;
  section2_toward_close.pose.orientation.x = 0.0;
  section2_toward_close.pose.orientation.y = 0.0;
  section2_toward_close.pose.orientation.z = 1.0;
  section2_toward_close.pose.orientation.w = 0.0;

  section2_away_far.pose.position.x = 10.0;
  section2_away_far.pose.position.y = -12.0;
  section2_away_far.pose.position.z = 5.0;
  section2_away_far.dimensions.x = 2.0;
  section2_away_far.dimensions.y = 2.0;
  section2_away_far.dimensions.z = 2.0;
  section2_away_far.pose.orientation.x = 0.0;
  section2_away_far.pose.orientation.y = 0.0;
  section2_away_far.pose.orientation.z = 0.0;
  section2_away_far.pose.orientation.w = 1.0;

  section23_border_towards_far.pose.position.x = 11.0;
  section23_border_towards_far.pose.position.y = -11.0;
  section23_border_towards_far.pose.position.z = 6.0;
  section23_border_towards_far.dimensions.x = 2.0;
  section23_border_towards_far.dimensions.y = 2.0;
  section23_border_towards_far.dimensions.z = 2.0;
  section23_border_towards_far.pose.orientation.x = 0.0;
  section23_border_towards_far.pose.orientation.y = 0.0;
  section23_border_towards_far.pose.orientation.z = .3830;
  section23_border_towards_far.pose.orientation.w = -.9237;

  section3_away_far.pose.position.x = 4.0;
  section3_away_far.pose.position.y = -6.0;
  section3_away_far.pose.position.z = 1.0;
  section3_away_far.dimensions.x = 2.0;
  section3_away_far.dimensions.y = 2.0;
  section3_away_far.dimensions.z = 2.0;
  section3_away_far.pose.orientation.x = 0.0;
  section3_away_far.pose.orientation.y = 0.0;
  section3_away_far.pose.orientation.z = .7068;
  section3_away_far.pose.orientation.w = .7073;

  section3_toward_close.pose.position.x = 2.0;
  section3_toward_close.pose.position.y = -2.5;
  section3_toward_close.pose.position.z = 0.0;
  section3_toward_close.dimensions.x = 2.0;
  section3_toward_close.dimensions.y = 2.0;
  section3_toward_close.dimensions.z = 2.0;
  section3_toward_close.pose.orientation.x = 0.0;
  section3_toward_close.pose.orientation.y = 0.0;
  section3_toward_close.pose.orientation.z = .7072;
  section3_toward_close.pose.orientation.w = -.7069;


  bbox_array.boxes = {section1_toward_far, section1_away_close, section12_border_away_close, section2_away_far,
  section2_toward_close, section23_border_towards_far, section3_away_far, section3_toward_close};

  jsk_recognition_msgs::BoundingBoxArray::Ptr bboxArrayPtr = boost::make_shared<jsk_recognition_msgs::BoundingBoxArray>(bbox_array);
  jsk_recognition_msgs::BoundingBoxArray::ConstPtr constBboxArrayPtr = boost::const_pointer_cast<const jsk_recognition_msgs::BoundingBoxArray>(bboxArrayPtr);

  // call function, see if it publishes
  node.jsk_callback(constBboxArrayPtr);

  std::vector<jsk_recognition_msgs::BoundingBox> msg_array;

  //already deemed that 3 boxes will be dangerous
  for (int i = 0; i < 3; i++) {
    // Wait for the danger message to be published
    jsk_recognition_msgs::BoundingBox received_msg = waitForMessage<jsk_recognition_msgs::BoundingBox>("danger_topic", ros::Duration(5.0));
    msg_array.push_back(received_msg);
  }

  // Check that the received message matches the expected output
  EXPECT_EQ(msg_array[0], bbox_array.boxes[2]);
  EXPECT_EQ(msg_array[1], bbox_array.boxes[3]);
  EXPECT_EQ(msg_array[2], bbox_array.boxes[7]);
}

*/


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "danger_publisher_node_test");
    return RUN_ALL_TESTS();
}

//TODO: fix errors
//main redefined? seems like program is taking the main from danger pub as well
//turn data types into constptrs with make shared and make const ptr 
