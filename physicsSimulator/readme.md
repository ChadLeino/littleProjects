# What is this?
## A physics simulator written in C++

# How will it work?
### main file
- This is where the functions are ran
### object oriented objects
- each new object is a class object
### while loop operation
- runs every 1/1000 of a second
### collision detection
- detection of position, and radius (radius implemented later, for now seen as points with radius of detection)
### gravity
- all objects are drawn down at a constant accel


# rewrite
## overall structure

### Objects
- Each object has its values, as well as its type
- Movable or unmovable
- Circle or square
- To add is charges positive or negative

### collisions
- Detect if in bounded box
- if square, hit
- if one is a circle, find if they actually hit
    - for both, we use the centerline method and the overlap
    - slighlty different calculation with each