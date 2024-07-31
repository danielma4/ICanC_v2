// Generated by gencpp from file vector_map_msgs/Signal.msg
// DO NOT EDIT!


#ifndef VECTOR_MAP_MSGS_MESSAGE_SIGNAL_H
#define VECTOR_MAP_MSGS_MESSAGE_SIGNAL_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace vector_map_msgs
{
template <class ContainerAllocator>
struct Signal_
{
  typedef Signal_<ContainerAllocator> Type;

  Signal_()
    : id(0)
    , vid(0)
    , plid(0)
    , type(0)
    , linkid(0)  {
    }
  Signal_(const ContainerAllocator& _alloc)
    : id(0)
    , vid(0)
    , plid(0)
    , type(0)
    , linkid(0)  {
  (void)_alloc;
    }



   typedef int32_t _id_type;
  _id_type id;

   typedef int32_t _vid_type;
  _vid_type vid;

   typedef int32_t _plid_type;
  _plid_type plid;

   typedef int32_t _type_type;
  _type_type type;

   typedef int32_t _linkid_type;
  _linkid_type linkid;



// reducing the odds to have name collisions with Windows.h 
#if defined(_WIN32) && defined(RED)
  #undef RED
#endif
#if defined(_WIN32) && defined(BLUE)
  #undef BLUE
#endif
#if defined(_WIN32) && defined(YELLOW)
  #undef YELLOW
#endif
#if defined(_WIN32) && defined(PEDESTRIAN_RED)
  #undef PEDESTRIAN_RED
#endif
#if defined(_WIN32) && defined(PEDESTRIAN_BLUE)
  #undef PEDESTRIAN_BLUE
#endif
#if defined(_WIN32) && defined(OTHER)
  #undef OTHER
#endif
#if defined(_WIN32) && defined(RED_LEFT)
  #undef RED_LEFT
#endif
#if defined(_WIN32) && defined(BLUE_LEFT)
  #undef BLUE_LEFT
#endif
#if defined(_WIN32) && defined(YELLOW_LEFT)
  #undef YELLOW_LEFT
#endif

  enum {
    RED = 1u,
    BLUE = 2u,
    YELLOW = 3u,
    PEDESTRIAN_RED = 4u,
    PEDESTRIAN_BLUE = 5u,
    OTHER = 9u,
    RED_LEFT = 21u,
    BLUE_LEFT = 22u,
    YELLOW_LEFT = 23u,
  };


  typedef boost::shared_ptr< ::vector_map_msgs::Signal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::vector_map_msgs::Signal_<ContainerAllocator> const> ConstPtr;

}; // struct Signal_

typedef ::vector_map_msgs::Signal_<std::allocator<void> > Signal;

typedef boost::shared_ptr< ::vector_map_msgs::Signal > SignalPtr;
typedef boost::shared_ptr< ::vector_map_msgs::Signal const> SignalConstPtr;

// constants requiring out of line definition

   

   

   

   

   

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::vector_map_msgs::Signal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::vector_map_msgs::Signal_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::vector_map_msgs::Signal_<ContainerAllocator1> & lhs, const ::vector_map_msgs::Signal_<ContainerAllocator2> & rhs)
{
  return lhs.id == rhs.id &&
    lhs.vid == rhs.vid &&
    lhs.plid == rhs.plid &&
    lhs.type == rhs.type &&
    lhs.linkid == rhs.linkid;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::vector_map_msgs::Signal_<ContainerAllocator1> & lhs, const ::vector_map_msgs::Signal_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace vector_map_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::vector_map_msgs::Signal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::vector_map_msgs::Signal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::vector_map_msgs::Signal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::vector_map_msgs::Signal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::vector_map_msgs::Signal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::vector_map_msgs::Signal_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::vector_map_msgs::Signal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a72afe3a758f79b5870ccafe3272b39c";
  }

  static const char* value(const ::vector_map_msgs::Signal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa72afe3a758f79b5ULL;
  static const uint64_t static_value2 = 0x870ccafe3272b39cULL;
};

template<class ContainerAllocator>
struct DataType< ::vector_map_msgs::Signal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "vector_map_msgs/Signal";
  }

  static const char* value(const ::vector_map_msgs::Signal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::vector_map_msgs::Signal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# type\n"
"uint8 RED=1\n"
"uint8 BLUE=2 #Green (outside Japan)\n"
"uint8 YELLOW=3\n"
"uint8 PEDESTRIAN_RED=4\n"
"uint8 PEDESTRIAN_BLUE=5\n"
"uint8 OTHER=9\n"
"\n"
"# Ver 1.00\n"
"int32 id\n"
"int32 vid\n"
"int32 plid\n"
"int32 type\n"
"int32 linkid\n"
"\n"
"# left turn\n"
"uint8 RED_LEFT=21\n"
"uint8 BLUE_LEFT=22 #Green (outside Japan)\n"
"uint8 YELLOW_LEFT=23\n"
;
  }

  static const char* value(const ::vector_map_msgs::Signal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::vector_map_msgs::Signal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.id);
      stream.next(m.vid);
      stream.next(m.plid);
      stream.next(m.type);
      stream.next(m.linkid);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Signal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::vector_map_msgs::Signal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::vector_map_msgs::Signal_<ContainerAllocator>& v)
  {
    s << indent << "id: ";
    Printer<int32_t>::stream(s, indent + "  ", v.id);
    s << indent << "vid: ";
    Printer<int32_t>::stream(s, indent + "  ", v.vid);
    s << indent << "plid: ";
    Printer<int32_t>::stream(s, indent + "  ", v.plid);
    s << indent << "type: ";
    Printer<int32_t>::stream(s, indent + "  ", v.type);
    s << indent << "linkid: ";
    Printer<int32_t>::stream(s, indent + "  ", v.linkid);
  }
};

} // namespace message_operations
} // namespace ros

#endif // VECTOR_MAP_MSGS_MESSAGE_SIGNAL_H
