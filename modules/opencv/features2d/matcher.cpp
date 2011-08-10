#include <ecto/ecto.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

using ecto::tendrils;

typedef std::vector<cv::KeyPoint> kpts_t;
typedef std::vector<cv::DMatch> matches_t;
struct Matcher
{
  static void
  declare_params(tendrils& p)
  {
  }
  static void
  declare_io(const tendrils& p, tendrils& inputs, tendrils& outputs)
  {
    inputs.declare<cv::Mat>("train", "An input image.");
    inputs.declare<cv::Mat>("test", "An mask, same size as image.");
    outputs.declare<matches_t>("matches", "The descriptor matches.");
  }
  int
  process(const tendrils& inputs, const tendrils& outputs)
  {
    cv::Mat train,test;
    inputs["train"] >> train;
    inputs["test"] >> test;
    cv::BruteForceMatcher<cv::Hamming> matcher;
    std::vector<cv::DMatch> matches;
    matcher.match(test,train,matches);
    outputs["matches"] << matches;
    return ecto::OK;
  }
};

ECTO_CELL(features2d, Matcher, "Matcher", "A feature descriptor matcher.");

