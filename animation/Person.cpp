#include "Person.h"

Vector3 JOINT_COLOUR = Vector3(0.2f, 0.2f, 0.6f);
Vector3 ARM_LEG_CHEST_COLOUR = Vector3(0.4f, 0.4f, 0.8f);
Vector3 FOOT_COLOUR = Vector3(0.2f, 0.1f, 0.0);
Vector3 PELVIS_COLOUR = Vector3(0.2f, 0.2f, 0.6f);

Person::Person(SurfaceFactory* surfaceFactory) : Skeleton(NULL)
{
    rootBone = createBones(surfaceFactory);
}

Person::~Person()
{
    // Delete all surfaces generated for the person bones
    for (std::vector<Surface*>::iterator it = surfaces.begin();
        (it != surfaces.end()); it++)
    {
        delete (*it);
    }
    // Also be sure to delete actual bones themselves
    // Done here but not in Skeleton because the bones
    // were actually generated INSIDE this class, unlike
    // Surface where they're passed into it
    delete rootBone;
}

Bone* Person::getRootBone()
{
    return rootBone;
}

Bone* Person::createBones(SurfaceFactory* surfaceFactory)
{
    // Create required surfaces
    Surface* headSurface = surfaceFactory->createSphere(0.9f, 32, 32);
    headSurface->setTextureID("face"); // apply texture to head!
    Surface* neckSurface = surfaceFactory->createCylinder(0.3f, 0.5f, 32);
    neckSurface->setColour(JOINT_COLOUR);        
    Surface* pelvisSurface = surfaceFactory->createBox(2.0f, 1.8f, 1.1f);
    pelvisSurface->setColour(PELVIS_COLOUR);    
    Surface* chestSurface = surfaceFactory->createBox(2.0f, 2.2f, 1.1f);
    chestSurface->setColour(ARM_LEG_CHEST_COLOUR);

    // Define animation for root of person.
    KeyFrameList rootKeyframes;
    rootKeyframes.push_back( KeyFrame(0, Vector3(0, 0, 0), Vector3(0, 90, 0)) );
    rootKeyframes.push_back( KeyFrame(200, Vector3(0, 0, 0), Vector3(0, 450, 0)) );    
    // Create root of person (there just to make the person move in a circle)
    Bone* root = new Bone(NULL, rootKeyframes);
    // Create person's body
    Bone* pelvisBone = new Bone(pelvisSurface, Vector3(0, 0, 10.0f), Vector3(0, 90.0f, 0));
    root->addChild(pelvisBone);
    Bone* chestBone = new Bone(chestSurface, Vector3(0.0f, 1.8f, 0.0f));
    pelvisBone->addChild(chestBone);
    // Create person's head (and neck)
    Bone* neckBone = new Bone(neckSurface, Vector3(1.0f, 2.2f, 0.5f), Vector3(90.0f, 0.0f, 0.0f));
    chestBone->addChild(neckBone);
    Bone* headBone = new Bone(headSurface, Vector3(0.0f, 0.0f, -0.7f), Vector3(0, 90, 90));
    neckBone->addChild(headBone);
    // Create person's left and right arms
    Bone* leftArm = createArm(surfaceFactory,
        Vector3(-0.2f, 1.9f, 0.55f), Vector3(0.0f, 0.0f, 0.0f), true);
    Bone* rightArm = createArm(surfaceFactory,
        Vector3(2.2f, 1.9f, 0.55f), Vector3(0.0f, 0.0f, 0.0f), false);
    chestBone->addChild(leftArm);        
    chestBone->addChild(rightArm);
    // Create person's left and right legs
    Bone* leftLeg = createLeg(surfaceFactory,
        Vector3(0.5f, 0.0f, 0.55f), Vector3(90.0f, 0.0f, 0.0f), true); // 90 deg rotation to legs point downwards
    Bone* rightLeg = createLeg(surfaceFactory,
        Vector3(1.5f, 0.0f, 0.55f), Vector3(90.0f, 0.0f, 0.0f), false);    
    pelvisBone->addChild(leftLeg);
    pelvisBone->addChild(rightLeg);
    
    return root;
}

Bone* Person::createLeg(SurfaceFactory* surfaceFactory, Vector3 rootPosition, Vector3 rootOrientation, bool reverseDirection)
{
    // Create surfaces to give to bones
    Surface* joint = surfaceFactory->createSphere(0.4f, 32, 32);
    joint->setColour(JOINT_COLOUR);
    Surface* legComponent = surfaceFactory->createCylinder(1.6f, 0.3f, 32);
    legComponent->setColour(ARM_LEG_CHEST_COLOUR);        
    Surface* footSurface = surfaceFactory->createBox(0.7f, 1.1f, 0.5f);
    footSurface->setColour(FOOT_COLOUR);    
    surfaces.push_back(joint);
    surfaces.push_back(legComponent);
    surfaces.push_back(footSurface);         
    
    // Generate keyframes for the whole leg
    float legKFMultiplier = (reverseDirection) ? -1.0f : 1.0f;    
    KeyFrameList legKeyframes;    
    legKeyframes.push_back( KeyFrame(0, rootPosition,
        Vector3(rootOrientation.x + (60.0f * legKFMultiplier), rootOrientation.y, rootOrientation.z)) );
    legKeyframes.push_back( KeyFrame(25, rootPosition,
        Vector3(rootOrientation.x - (60.0f * legKFMultiplier), rootOrientation.y, rootOrientation.z)) );
    legKeyframes.push_back( KeyFrame(50, rootPosition,
        Vector3(rootOrientation.x + (60.0f * legKFMultiplier), rootOrientation.y, rootOrientation.z)) );
    
    Bone* leg = new Bone(joint, legKeyframes);
    Bone* thigh = new Bone(legComponent, Vector3(0.0f, 0.0f, 1.0f));
    leg->addChild(thigh);
    Bone* knee = new Bone(joint, Vector3(0, 0, 1.0f));
    thigh->addChild(knee);
    Bone* shin = new Bone(legComponent, Vector3(0.0f, 0.0f, 1.0f));
    knee->addChild(shin);    
    Bone* foot = new Bone(footSurface, Vector3(-0.35f, -0.35f, 0.8f));
    shin->addChild(foot);
    
    return leg;
}

Bone* Person::createArm(SurfaceFactory* surfaceFactory, Vector3 rootPosition, Vector3 rootOrientation, bool reverseDirection)
{
    // Create surfaces to give to bones
    Surface* shoulderJoint = surfaceFactory->createSphere(0.4f, 32, 32);
    shoulderJoint->setColour(JOINT_COLOUR);
    Surface* upperArmComponent = surfaceFactory->createCylinder(2.0f, 0.25f, 32);
    upperArmComponent->setColour(ARM_LEG_CHEST_COLOUR);
    Surface* elbowJoint = surfaceFactory->createSphere(0.3f, 32, 32);
    elbowJoint->setColour(JOINT_COLOUR);    
    Surface* lowerArmComponent = surfaceFactory->createCylinder(1.4f, 0.25f, 32);    
    lowerArmComponent->setColour(ARM_LEG_CHEST_COLOUR);
    surfaces.push_back(shoulderJoint);
    surfaces.push_back(upperArmComponent);
    surfaces.push_back(elbowJoint);
    surfaces.push_back(lowerArmComponent);    

    // Depending on which arm this is for (left or right), the
    // bone transformations differ
    float armDirection = 10.0f;
    Vector3 upperArmPosition(0.15f, -0.7f, 0.0f);
    Vector3 lowerArmPosition(-0.14f, 0.0f, 0.8f);
    if (reverseDirection)
    {
        armDirection = -armDirection;
        upperArmPosition.x = -upperArmPosition.x;
        lowerArmPosition.x = -lowerArmPosition.x;
    }
    // Define shoulder and elbow animations
    KeyFrameList shoulderKeyframes;
    // Which direction a shoulder is initially in depends on which shoulder it is
    float shKFMultiplier = (reverseDirection) ? -1.0f : 1.0f;    
    shoulderKeyframes.push_back( KeyFrame(0, rootPosition,
        Vector3(rootOrientation.x + (60.0f * shKFMultiplier), rootOrientation.y, rootOrientation.z)) );
    shoulderKeyframes.push_back( KeyFrame(25, rootPosition,
        Vector3(rootOrientation.x - (60.0f * shKFMultiplier), rootOrientation.y, rootOrientation.z)) );
    shoulderKeyframes.push_back( KeyFrame(50, rootPosition,
        Vector3(rootOrientation.x + (60.0f * shKFMultiplier), rootOrientation.y, rootOrientation.z)) );
        
    Vector3 elbowPosition = Vector3(0.0f, 0.0f, 1.1f);
    Vector3 elbowOrientation = Vector3(0, 0, 0) + Vector3(-45.0f, 0, 0);
    KeyFrameList elbowKeyframes;
    elbowKeyframes.push_back( KeyFrame(0, elbowPosition, elbowOrientation) );    

    Bone* shoulder = new Bone(shoulderJoint, shoulderKeyframes);
    Bone* upperArm = new Bone(upperArmComponent, upperArmPosition, Vector3(90.0f, armDirection, 0.0f));
    shoulder->addChild(upperArm);
    Bone* elbow = new Bone(elbowJoint, elbowKeyframes);
    upperArm->addChild(elbow);    
    Bone* lowerArm = new Bone(lowerArmComponent, lowerArmPosition, Vector3(0, -armDirection, 0));
    elbow->addChild(lowerArm);
    Bone* hand = new Bone(elbowJoint, Vector3(0, 0, 0.9f), Vector3(0, 0, 0));
    lowerArm->addChild(hand);


    return shoulder;
}
