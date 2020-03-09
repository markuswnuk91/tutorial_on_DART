#include <dart/dart.hpp>
#include <dart/gui/osg/osg.hpp>

using namespace dart;

int main()
{
  auto shape
      = std::make_shared<dynamics::BoxShape>(Eigen::Vector3d(0.3, 0.3, 0.3));

  // Create a box-shaped rigid body
  auto skeleton = dynamics::Skeleton::create();
  auto jointAndBody
      = skeleton->createJointAndBodyNodePair<dynamics::FreeJoint>();
  auto body = jointAndBody.second;
  body->createShapeNodeWith<
      dynamics::VisualAspect,
      dynamics::CollisionAspect,
      dynamics::DynamicsAspect>(shape);

  // Create a world and add the rigid body
  auto world = simulation::World::create();
  world->addSkeleton(skeleton);

  // Wrap a WorldNode around it
  ::osg::ref_ptr<gui::osg::RealTimeWorldNode> node
      = new gui::osg::RealTimeWorldNode(world);

  // Create a Viewer and set it up with the WorldNode
  auto viewer = gui::osg::Viewer();
  viewer.addWorldNode(node);

  viewer.addInstructionText("Press space to start free falling the box.\n");
  std::cout << viewer.getInstructions() << std::endl;

  // Set up the window to be 640x480
  viewer.setUpViewInWindow(0, 0, 640, 480);

  // Adjust the viewpoint of the Viewer
  viewer.getCameraManipulator()->setHomePosition(
      ::osg::Vec3(2.57f, 3.14f, 1.64f),
      ::osg::Vec3(0.00f, 0.00f, 0.00f),
      ::osg::Vec3(-0.24f, -0.25f, 0.94f));

  // We need to re-dirty the CameraManipulator by passing it into the viewer
  // again, so that the viewer knows to update its HomePosition setting
  viewer.setCameraManipulator(viewer.getCameraManipulator());

  // Begin running the application loop
  viewer.run();

  return 0;
}
