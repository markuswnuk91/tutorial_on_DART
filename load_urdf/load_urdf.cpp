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
/*
SkeletonPtr createFloor()
{
  //Lesson 1

  return floor;
}
*/

SkeletonPtr createManipulator()
{
  //Lesson 2

  return manipulator;
}

int main(int argc, char* argv[])
{
 // SkeletonPtr floor = createFloor();
  SkeletonPtr manipulator = createManipulator();

  WorldPtr world = std::make_shared<World>();
  //world->addSkeleton(floor);
  world->addSkeleton(manipulator);

  MyWindow window(world);

  glutInit(&argc, argv);
  window.initWindow(1200, 1600, "load_urdf");
  glutMainLoop();
}
