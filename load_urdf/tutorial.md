# DART Tutorial (load_urdf)

In this tutorial you will learn how to import a robot as URDF file.

## Lesson 1 Create a floor for the scene
First create a floor for the scene.
The floor is a `Skeleton`,which is attached to the wordl by a `<WeldJoint>`. Give it a width of 3.0, a height of 0.1, a `VisualAspect`,`CollisionAspect`, `DynamicsAspect`.
To give the floor a color of your choice use

```cpp
    shapeNode->getVisualAspect()->setColor(dart::Color::Blue());
```
Then position the floor to have its surface aligned with the x-y plane.
```cpp
  Eigen::Isometry3d tf(Eigen::Isometry3d::Identity());
  tf.translation() = Eigen::Vector3d(0.0, 0.0, -floor_height / 2.0);
  body->getParentJoint()->setTransformFromParentBodyNode(tf);
```
## Lesson 2 
Have a look at the `createManipulator()` function of the tutorial.
Here we want to load a robot. 
Dart offers the `DartLoader` utility for this purpose.
```cpp
  dart::utils::DartLoader loader;
```
Note that many URDF files use ROS’s `package:` scheme to specify the locations of the `urdf` resources that need to be loaded. You can use the function `DartLoader::addPackageDirectory` to specify the locations of these packages.
Fist we want to load a robot model that comes with the installation of DART.
```cpp
  SkeletonPtr manipulator
      = loader.parseSkeleton("dart://sample/urdf/KR5/KR5 sixx R650.urdf");
```
We should give our manipulator a name:
```cpp
  manipulator->setName("manipulator");
```
Now we’ll want to initialize the location and configuration of the manipulator. 
```cpp
  // Position its base in a reasonable way
  Eigen::Isometry3d tf = Eigen::Isometry3d::Identity();
  tf.translation() = Eigen::Vector3d(-0.65, 0.0, 0.0);
  manipulator->getJoint(0)->setTransformFromParentBodyNode(tf);

  // Get it into a useful configuration
  manipulator->getDof(1)->setPosition(toRadian(140.0));
  manipulator->getDof(2)->setPosition(toRadian(-140.0));
```
From here you can run the program to see the manipulator in the scene. Be aware that it will pitifully collapse onto the floor.

## Lesson 3 Load our own Panda robot model
Replace the content of the `createManipulator()` function such that the Panda model is loaded into the simulation environment.

Give the path to the resource folder `/panda` relative to the build executable of the program.
Note that `DartLoader::addPackageDirectory` requires an absolute path. Use the function `convertPathRelativeToExe` in order to obtain an absolute path from a relative path from the executable to the urdf resources. 
```cpp
    std::string convertPathRelativeToExe(const std::string &relativePart) {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    const auto abspath = std::string(result, (count > 0) ? count : 0);

    return dart::common::Uri::getRelativeUri(abspath, relativePart);
    }
```