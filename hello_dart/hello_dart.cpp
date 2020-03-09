#include <dart/dart.hpp>
#include <dart/gui/osg/osg.hpp>

using namespace dart;

int main()
{
  // Create a Viewer
  auto viewer = dart::gui::osg::Viewer();

//Lesson 1 Get familiar with the DART Viewer
  //...

  
// Lesson 2 Create a world and a WorldNode
  //...


// Lesson 3 Create a box-shaped rigid body 
  //...


  viewer.addInstructionText("Welcome to the hello_dart tutorial!");
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
