// Generated by gencpp from file autoware_map_msgs/AreaArray.msg
// DO NOT EDIT!


#ifndef AUTOWARE_MAP_MSGS_MESSAGE_AREAARRAY_H
#define AUTOWARE_MAP_MSGS_MESSAGE_AREAARRAY_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <autoware_map_msgs/Area.h>

namespace autoware_map_msgs
{
template <class ContainerAllocator>
struct AreaArray_
{
  typedef AreaArray_<ContainerAllocator> Type;

  AreaArray_()
    : header()
    , data()  {
    }
  AreaArray_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , data(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector< ::autoware_map_msgs::Area_<ContainerAllocator> , typename std::allocator_traits<ContainerAllocator>::template rebind_alloc< ::autoware_map_msgs::Area_<ContainerAllocator> >> _data_type;
  _data_type data;





  typedef boost::shared_ptr< ::autoware_map_msgs::AreaArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autoware_map_msgs::AreaArray_<ContainerAllocator> const> ConstPtr;

}; // struct AreaArray_

typedef ::autoware_map_msgs::AreaArray_<std::allocator<void> > AreaArray;

typedef boost::shared_ptr< ::autoware_map_msgs::AreaArray > AreaArrayPtr;
typedef boost::shared_ptr< ::autoware_map_msgs::AreaArray const> AreaArrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autoware_map_msgs::AreaArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autoware_map_msgs::AreaArray_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::autoware_map_msgs::AreaArray_<ContainerAllocator1> & lhs, const ::autoware_map_msgs::AreaArray_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.data == rhs.data;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::autoware_map_msgs::AreaArray_<ContainerAllocator1> & lhs, const ::autoware_map_msgs::AreaArray_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace autoware_map_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::autoware_map_msgs::AreaArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autoware_map_msgs::AreaArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autoware_map_msgs::AreaArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autoware_map_msgs::AreaArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autoware_map_msgs::AreaArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autoware_map_msgs::AreaArray_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autoware_map_msgs::AreaArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d4bab306f39b4bc6e4047b8f77a2e221";
  }

  static const char* value(const ::autoware_map_msgs::AreaArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd4bab306f39b4bc6ULL;
  static const uint64_t static_value2 = 0xe4047b8f77a2e221ULL;
};

template<class ContainerAllocator>
struct DataType< ::autoware_map_msgs::AreaArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autoware_map_msgs/AreaArray";
  }

  static const char* value(const ::autoware_map_msgs::AreaArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autoware_map_msgs::AreaArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# This consists of multiple areas in a map with reference coordinate frame. \n"
"\n"
"Header header\n"
"Area[] data\n"
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
"MSG: autoware_map_msgs/Area\n"
"# This represents a general purpose area obejct in map\n"
"\n"
"# Id of this Area object. Must be unique within all area objects.\n"
"int32 area_id\n"
"\n"
"# Vertices that describes this area. Must be in clockwise order.\n"
"int32[] point_ids\n"
;
  }

  static const char* value(const ::autoware_map_msgs::AreaArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autoware_map_msgs::AreaArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct AreaArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autoware_map_msgs::AreaArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autoware_map_msgs::AreaArray_<ContainerAllocator>& v)
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
      Printer< ::autoware_map_msgs::Area_<ContainerAllocator> >::stream(s, indent + "    ", v.data[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTOWARE_MAP_MSGS_MESSAGE_AREAARRAY_H