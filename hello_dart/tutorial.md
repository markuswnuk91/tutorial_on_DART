# DART Tutorial (hello_dart)

In this tutorial you will learn some basics about DART and create you own little simulation world.

## Lesson 1 Get familiar with the DART Viewer
To visualize the scene dart uses a class `Viewer`.
Have a look at the program to see how a viewer is initialized. 
Also, have a look at [API documentation](https://dartsim.github.io/dart/) to get to know the several options you can set with the viewer.
Note that DART includes [OpenSceneGraph (OSG)](http://public.vrac.iastate.edu/vancegroup/docs/OpenSceneGraphReferenceDocs-3.0/index.html) as external library.

Run the program to see an empty simulation window...

## Lesson 2 Create a world node
To simulate a world in DART you need the class `World`.
Have a look at this class in DART's API documentation to see its various functionalities.
To creat a world you need:
```cpp
    auto world = simulation::World::create();
```

In order to visualize a wolrd in OpenSceneGraph we need to wrap our world in a `WorldNode`.
You can do this with:
```cpp
    osg::ref_ptr<gui::osg::RealTimeWorldNode> node
      = new gui::osg::RealTimeWorldNode(world);
``` 
We can then pass our world to the Viewer with:
```cpp    
    viewer.addWorldNode(node);
``` 
Create a world and pass it to the viewer.
Run the program to see an empty simulation window again...

## Lesson 3 Create an object and run the simulation
DART is a multibody simulation framework. Mutlibody objects in DART are represented as `Skeletons`.
A Skeleton is a structure that consists of `BodyNodes` (bodies) which are connected by `Joints`. 
Every Joint has a child BodyNode, and every BodyNode has a parent Joint. 
Even the root BodyNode has a Joint that attaches it to the World. 
To create a Skeleton we can use 

```cpp  
    auto skeleton = dynamics::Skeleton::create();
```
which gives us a `SkeltonPtr` to an emty Skeleton.

To create joint in our Skeleton we can use the function `createJointAndBodyNodePair<JointType>()`
```cpp
    auto jointAndBody = skeleton->createJointAndBodyNodePair<dynamics::FreeJoint>();
```
which gives us a pair of pointers, where the first pointer points to the Joint, and the second pointer points to the body.
```cpp
    auto body = jointAndBody.second;
```
Note that our body is only a BodyNode up to now with no physical parameters yet. 
In order to set physical parameters such as mass or the geometrical shape of the body DART offers a 'Shape' class.
```cpp
    auto shape = std::make_shared<dynamics::BoxShape>(Eigen::Vector3d(0.3, 0.3, 0.3));
```
To append a Shape to our body node we can create a 'ShapeNode' with invoking `createShapeNodeWith<ShapeType>()` on our BodyNode.
```cpp 
    body->createShapeNodeWith<
      dynamics::VisualAspect,
      dynamics::CollisionAspect,
      dynamics::DynamicsAspect>(shape);
```
Remeber to add the scelton we created to our world.
```cpp
    world->addSkeleton(skeleton);
```
Now you can give it a try!