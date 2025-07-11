#include <rclcpp/rclcpp.hpp>
#include <image_transport/image_transport.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>

class ImageSubscriberNode : public rclcpp::Node
{
public:
    ImageSubscriberNode()
        : Node("camera_subscriber_node")
    {
        RCLCPP_INFO(this->get_logger(), "Nodo inicializado");
    }

    void initialize()
    {
        auto node_ptr = std::dynamic_pointer_cast<rclcpp::Node>(shared_from_this());
        image_transport::ImageTransport it(node_ptr);
        sub_ = it.subscribe("/image_raw", 10,
            std::bind(&ImageSubscriberNode::imageCallback, this, std::placeholders::_1));
        
        pub_ = it.advertise("/video_source/raw", 10);
        RCLCPP_INFO(this->get_logger(), "Suscrito a /image_raw y republicando en /video_source/raw");
    }

private:
    void imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr &msg)
    {
        try {
            cv::Mat img = cv_bridge::toCvShare(msg, "bgr8")->image;

            pub_.publish(msg);
        } catch (cv_bridge::Exception &e) {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        }
    }

    image_transport::Subscriber sub_;
    image_transport::Publisher pub_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ImageSubscriberNode>();
    node->initialize();  // Initialize after construction
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}