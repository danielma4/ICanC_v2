// Generated by gencpp from file autoware_msgs/ProjectionMatrix.msg
// DO NOT EDIT!


#ifndef AUTOWARE_MSGS_MESSAGE_PROJECTIONMATRIX_H
#define AUTOWARE_MSGS_MESSAGE_PROJECTIONMATRIX_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace autoware_msgs
{
template <class ContainerAllocator>
struct ProjectionMatrix_
{
  typedef ProjectionMatrix_<ContainerAllocator> Type;

  ProjectionMatrix_()
    : header()
    , projection_matrix()  {
      projection_matrix.assign(0.0);
  }
  ProjectionMatrix_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , projection_matrix()  {
  (void)_alloc;
      projection_matrix.assign(0.0);
  }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef boost::array<double, 16>  _projection_matrix_type;
  _projection_matrix_type projection_matrix;





  typedef boost::shared_ptr< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> const> ConstPtr;

}; // struct ProjectionMatrix_

typedef ::autoware_msgs::ProjectionMatrix_<std::allocator<void> > ProjectionMatrix;

typedef boost::shared_ptr< ::autoware_msgs::ProjectionMatrix > ProjectionMatrixPtr;
typedef boost::shared_ptr< ::autoware_msgs::ProjectionMatrix const> ProjectionMatrixConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::autoware_msgs::ProjectionMatrix_<ContainerAllocator1> & lhs, const ::autoware_msgs::ProjectionMatrix_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.projection_matrix == rhs.projection_matrix;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::autoware_msgs::ProjectionMatrix_<ContainerAllocator1> & lhs, const ::autoware_msgs::ProjectionMatrix_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace autoware_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> >
{
  static const char* value()
  {
    return "383fdce8566145c0d8ee5731cf4d6531";
  }

  static const char* value(const ::autoware_msgs::ProjectionMatrix_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x383fdce8566145c0ULL;
  static const uint64_t static_value2 = 0xd8ee5731cf4d6531ULL;
};

template<class ContainerAllocator>
struct DataType< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autoware_msgs/ProjectionMatrix";
  }

  static const char* value(const ::autoware_msgs::ProjectionMatrix_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"float64[16] projection_matrix\n"
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
;
  }

  static const char* value(const ::autoware_msgs::ProjectionMatrix_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.projection_matrix);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ProjectionMatrix_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autoware_msgs::ProjectionMatrix_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autoware_msgs::ProjectionMatrix_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "projection_matrix[]" << std::endl;
    for (size_t i = 0; i < v.projection_matrix.size(); ++i)
    {
      s << indent << "  projection_matrix[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.projection_matrix[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTOWARE_MSGS_MESSAGE_PROJECTIONMATRIX_H
