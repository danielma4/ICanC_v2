// Generated by gencpp from file autoware_map_msgs/LaneChangeRelationArray.msg
// DO NOT EDIT!


#ifndef AUTOWARE_MAP_MSGS_MESSAGE_LANECHANGERELATIONARRAY_H
#define AUTOWARE_MAP_MSGS_MESSAGE_LANECHANGERELATIONARRAY_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <autoware_map_msgs/LaneChangeRelation.h>

namespace autoware_map_msgs
{
template <class ContainerAllocator>
struct LaneChangeRelationArray_
{
  typedef LaneChangeRelationArray_<ContainerAllocator> Type;

  LaneChangeRelationArray_()
    : header()
    , data()  {
    }
  LaneChangeRelationArray_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , data(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector< ::autoware_map_msgs::LaneChangeRelation_<ContainerAllocator> , typename std::allocator_traits<ContainerAllocator>::template rebind_alloc< ::autoware_map_msgs::LaneChangeRelation_<ContainerAllocator> >> _data_type;
  _data_type data;





  typedef boost::shared_ptr< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> const> ConstPtr;

}; // struct LaneChangeRelationArray_

typedef ::autoware_map_msgs::LaneChangeRelationArray_<std::allocator<void> > LaneChangeRelationArray;

typedef boost::shared_ptr< ::autoware_map_msgs::LaneChangeRelationArray > LaneChangeRelationArrayPtr;
typedef boost::shared_ptr< ::autoware_map_msgs::LaneChangeRelationArray const> LaneChangeRelationArrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator1> & lhs, const ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.data == rhs.data;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator1> & lhs, const ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace autoware_map_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "329b4e9aa6f696f62fd90636a3f80778";
  }

  static const char* value(const ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x329b4e9aa6f696f6ULL;
  static const uint64_t static_value2 = 0x2fd90636a3f80778ULL;
};

template<class ContainerAllocator>
struct DataType< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autoware_map_msgs/LaneChangeRelationArray";
  }

  static const char* value(const ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# This consists of multiple LaneChangeRelation objects in a map. \n"
"\n"
"Header header\n"
"LaneChangeRelation[] data\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: autoware_map_msgs/LaneChangeRelation\n"
"# This represents lanes that are next to each other.\n"
"# This relation object is only made if the lane change is available. \n"
"\n"
"# BlinkerType\n"
"uint8 None = 0\n"
"uint8 Left = 1\n"
"uint8 Right = 2\n"
"\n"
"# Id of refering lane\n"
"int32 lane_id\n"
"\n"
"# Id of lane that is next to the refering lane. \n"
"int32 next_lane_id\n"
"\n"
"# Represents blinker that must be lit when doing this lane change.\n"
"# value of \"blinker\" must be one of \"Blinker Type\"\n"
"# e.g. if next_lane_id is left of lane_id, then blinker = LEFT\n"
"int32 blinker\n"
;
  }

  static const char* value(const ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LaneChangeRelationArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autoware_map_msgs::LaneChangeRelationArray_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "data[]" << std::endl;
    for (size_t i = 0; i < v.data.size(); ++i)
    {
      s << indent << "  data[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::autoware_map_msgs::LaneChangeRelation_<ContainerAllocator> >::stream(s, indent + "    ", v.data[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTOWARE_MAP_MSGS_MESSAGE_LANECHANGERELATIONARRAY_H
