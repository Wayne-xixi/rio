// This file is part of RIO - Radar Inertial Odometry and Radar ego velocity estimation.
// Copyright (C) 2021  Christopher Doer <christopher.doer@kit.edu>
// (Institute of Control Systems, Karlsruhe Institute of Technology)

// RIO is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

// RIO is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with RIO.  If not, see <https://www.gnu.org/licenses/>.

#include <ros/ros.h>

#include <radar_ego_velocity_estimation/radar_body_velocity_estimator_ros.h>

using namespace rio;

const std::string kNodeName = "radar_body_velocity_estimator";
const std::string kPrefix   = "[" + kNodeName + "]: ";

int main(int argc, char** argv)
{
  ros::init(argc, argv, kNodeName);
  ros::NodeHandle nh("~");

  RadarBodyVelocityEstimatorRos estimator_ros(nh);

  double bag_start = -1.0;
  getRosParameter(nh, kPrefix, RosParameterType::Optional, "bag_start", bag_start);

  double bag_duration = 1.0e6;
  getRosParameter(nh, kPrefix, RosParameterType::Optional, "bag_duration", bag_duration);
  if (bag_duration <= 0)
    bag_duration = 1.0e6;

  double sleep_ms = -1.0;
  getRosParameter(nh, kPrefix, RosParameterType::Optional, "sleep_ms", sleep_ms);

  std::string rosbag_path = "";
  if (getRosParameter(nh, kPrefix, RosParameterType::Required, "rosbag_path", rosbag_path))
    estimator_ros.runFromRosbag(rosbag_path, bag_start, bag_duration, sleep_ms);

  return 0;
}
