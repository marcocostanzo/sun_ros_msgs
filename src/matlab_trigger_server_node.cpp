#include "ros/ros.h"
#include "std_srvs/Trigger.h"
#include "sun_ros_msgs/Trigger.h" 

ros::ServiceClient cli;

bool service_cb(sun_ros_msgs::Trigger::Request& request, sun_ros_msgs::Trigger::Response& response)
{
    std_srvs::Trigger::Request req;
    std_srvs::Trigger::Response res;
    bool ret = cli.call(req,res);
    response.success = res.success;
    response.message = res.message;
    return ret;
}


int main(int argc, char *argv[])
{
    ros::init(argc,argv,"trigger_buffer_server");  

    ros::NodeHandle nh_public;
    ros::NodeHandle nh_private("~");

    std::string service_in_str, service_out_str;

    nh_private.getParam("service_in", service_in_str);
    nh_private.getParam("service_out", service_out_str);

    cli = nh_public.serviceClient<std_srvs::Trigger>(service_out_str);

    ros::ServiceServer srv = nh_public.advertiseService(service_in_str, service_cb);

    ros::spin();

    return 0;
}
