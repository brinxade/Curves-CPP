# Curves-CPP

Curves-CPP is Visual Studio project containing an interactive OpenGL program to play around with splines (mathematical term for curves). The code currently has header files for the following splines:
- **Catmull-Rom Spline**


## Purpose
Many curious programmers (specifically graphics enthusiasts) may be trying to incorporate curves into their application somehow (like me!). Curves-CPP provides them with a playground to implement their own splines or tweak the existing ones. Concise code and separate header file for each curve allows easy experiments. 

Here are some use cases for each curve in the repository,
- **Catmull-Rom Spline**
Catmull-Rom spline is a curve that is guaranteed to pass through all the control points. It is useful in creating animations. For eg. in a computer game, path finding algorithm can generate points from an enemy to its target, and a curve can be drawn through those points. The enemy can then walk through the curve to the player giving the whole process a much more realistic feel that just snapping through those points (without the curve).

##  Dependencies
The dependencies are only required for the visualization program to run. The code for curves can be used standalone.
 - **OpenGL** - Required for visualization
 - **GLFW** - A lightweight API for window creation, required for visualization

## Bug fixes and contribution
To contribute to this repo, please make a pull request. For pointing out bugs, please raise an issue. For any other queries you may contact me on *brinxade@gmail.com*. I'm always up for working on interesting projects!
