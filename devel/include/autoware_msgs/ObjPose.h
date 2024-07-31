// Generated by gencpp from file autoware_msgs/ObjPose.msg
// DO NOT EDIT!


#ifndef AUTOWARE_MSGS_MESSAGE_OBJPOSE_H
#define AUTOWARE_MSGS_MESSAGE_OBJPOSE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <geometry_msgs/PoseArray.h>

namespace autoware_msgs
{
template <class ContainerAllocator>
struct ObjPose_
{
  typedef ObjPose_<ContainerAllocator> Type;

  ObjPose_()
    : header()
    , type()
    , obj_id()
    , obj()  {
    }
  ObjPose_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , type(_alloc)
    , obj_id(_alloc)
    , obj(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _type_type;
  _type_type type;

   typedef std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> _obj_id_type;
  _obj_id_type obj_id;

   typedef std::vector< ::geometry_msgs::PoseArray_<ContainerAllocator> , typename std::allocator_traits<ContainerAllocator>::template rebind_alloc< ::geometry_msgs::PoseArray_<ContainerAllocator> >> _obj_type;
  _obj_type obj;





  typedef boost::shared_ptr< ::autoware_msgs::ObjPose_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autoware_msgs::ObjPose_<ContainerAllocator> const> ConstPtr;

}; // struct ObjPose_

typedef ::autoware_msgs::ObjPose_<std::allocator<void> > ObjPose;

typedef boost::shared_ptr< ::autoware_msgs::ObjPose > ObjPosePtr;
typedef boost::shared_ptr< ::autoware_msgs::ObjPose const> ObjPoseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autoware_msgs::ObjPose_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autoware_msgs::ObjPose_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::autoware_msgs::ObjPose_<ContainerAllocator1> & lhs, const ::autoware_msgs::ObjPose_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.type == rhs.type &&
    lhs.obj_id == rhs.obj_id &&
    lhs.obj == rhs.obj;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::autoware_msgs::ObjPose_<ContainerAllocator1> & lhs, const ::autoware_msgs::ObjPose_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace autoware_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::autoware_msgs::ObjPose_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autoware_msgs::ObjPose_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autoware_msgs::ObjPose_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autoware_msgs::ObjPose_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autoware_msgs::ObjPose_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autoware_msgs::ObjPose_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autoware_msgs::ObjPose_<ContainerAllocator> >
{
  static const char* value()
  {
    return "54a63c36291a0587bc8b4eba25a10459";
  }

  static const char* value(const ::autoware_msgs::ObjPose_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x54a63c36291a0587ULL;
  static const uint64_t static_value2 = 0xbc8b4eba25a10459ULL;
};

template<class ContainerAllocator>
struct DataType< ::autoware_msgs::ObjPose_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autoware_msgs/ObjPose";
  }

  static const char* value(const ::autoware_msgs::ObjPose_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autoware_msgs::ObjPose_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"string type\n"
"int32[] obj_id\n"
"geometry_msgs/PoseArray[] obj\n"
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
"MSG: geometry_msgs/PoseArray\n"
"# An array of poses with a header for global reference.\n"
"\n"
"Header header\n"
"\n"
"Pose[] poses\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
;
  }

  static const char* value(const ::autoware_msgs::ObjPose_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autoware_msgs::ObjPose_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.type);
      stream.next(m.obj_id);
      stream.next(m.obj);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ObjPose_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autoware_msgs::ObjPose_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autoware_msgs::ObjPose_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "type: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.type);
    s << indent << "obj_id[]" << std::endl;
    for (size_t i = 0; i < v.obj_id.size(); ++i)
    {
      s << indent << "  obj_id[" << i << "]: ";
      Printer<int32_t>::stream(s, indent + "  ", v.obj_id[i]);
    }
    s << indent << "obj[]" << std::endl;
    for (size_t i = 0; i < v.obj.size(); ++i)
    {
      s << indent << "  obj[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::geometry_msgs::PoseArray_<ContainerAllocator> >::stream(s, indent + "    ", v.obj[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTOWARE_MSGS_MESSAGE_OBJPOSE_H
