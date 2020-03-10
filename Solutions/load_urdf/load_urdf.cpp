/*
 * Copyright (c) 2011-2019, The DART development contributors
 * All rights reserved.
 *
 * The list of contributors can be found at:
 *   https://github.com/dartsim/dart/blob/master/LICENSE
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */
#include <dart/dart.hpp>
#include <dart/gui/gui.hpp>
#include <dart/utils/urdf/urdf.hpp>

using namespace dart::common;
using namespace dart::dynamics;
using namespace dart::simulation;
using namespace dart::math;

class MyWindow : public dart::gui::glut::SimWindow
{
public:
  MyWindow(const WorldPtr& world)
  {
    setWorld(world);
    mFloor = world->getSkeleton("floor");
  }

protected:
  /// Floor of the scene
  SkeletonPtr mFloor;
};

SkeletonPtr createFloor()
{
  SkeletonPtr floor = Skeleton::create("floor");

  // Give the floor a body
  BodyNodePtr body
      = floor->createJointAndBodyNodePair<WeldJoint>(nullptr).second;

  // Give the body a shape
  double floor_width = 3.0;
  double floor_height = 0.1;
  std::shared_ptr<BoxShape> box(
      new BoxShape(Eigen::Vector3d(floor_width, floor_width, floor_height)));
  auto shapeNode = body->createShapeNodeWith<
      VisualAspect,
      CollisionAspect,
      DynamicsAspect>(box);
  shapeNode->getVisualAspect()->setColor(dart::Color::Blue());

  // Put the body into position
  Eigen::Isometry3d tf(Eigen::Isometry3d::Identity());
  tf.translation() = Eigen::Vector3d(0.0, 0.0, -floor_height / 2.0);
  body->getParentJoint()->setTransformFromParentBodyNode(tf);

  return floor;
}
std::string convertPathRelativeToExe(const std::string &relativePart) {
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  const auto abspath = std::string(result, (count > 0) ? count : 0);

  return dart::common::Uri::getRelativeUri(abspath, relativePart);
}
SkeletonPtr createManipulator()
{
  std::string urdfLocation = "package://franka_description/panda_arm_hand.urdf";
  // Load the Skeleton from a file
  dart::utils::DartLoader loader;
  auto dataPath = convertPathRelativeToExe("../panda/");
  std::cout << "URDF Path was determined as: " << dataPath << std ::endl;
  loader.addPackageDirectory("franka_description", dataPath);
  SkeletonPtr manipulator
      = loader.parseSkeleton(urdfLocation);
  manipulator->setName("manipulator");

  // Position its base in a reasonable way
  Eigen::Isometry3d tf = Eigen::Isometry3d::Identity();
  tf.translation() = Eigen::Vector3d(0.0, 0.0, 0.0);
  manipulator->getJoint(0)->setTransformFromParentBodyNode(tf);

  // Get it into a useful configuration
  manipulator->getDof(0)->setPosition(0 * M_PI / 180.0);
  manipulator->getDof(1)->setPosition(0 * M_PI / 180.0);
  manipulator->getDof(2)->setPosition(0 * M_PI / 180.0);
  manipulator->getDof(3)->setPosition(270 * M_PI / 180.0);
  manipulator->getDof(5)->setPosition(90 * M_PI / 180.0);

  return manipulator;
}

int main(int argc, char* argv[])
{
  SkeletonPtr floor = createFloor();
  SkeletonPtr manipulator = createManipulator();

  WorldPtr world = std::make_shared<World>();
  world->addSkeleton(floor);
  world->addSkeleton(manipulator);

  MyWindow window(world);

  glutInit(&argc, argv);
  window.initWindow(1200, 1600, "load_urdf");
  glutMainLoop();
}
