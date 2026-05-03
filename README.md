# meb-robot
Retrospective documentation of a Maze Solver robot made for MEB ROBO 2025 &amp; 2026

This is a compact, autonomous maze solver robot. Made with a 3d printed chassis and IR sensors; was designed and iterated over the span of 2 years to optimize turning and wall following ability.

 * Microcontroller: Arduino Nano
 * Sensors: 3x MR 45-5V Diffuse Sensors
 * Custom 3D printed PETG
 * Logic: Wall following (Left side)

# Engineering Decisions
Optimized sensor array for navigation:
 * used 3 point diffuse sensor array (45 degree angle to each side)
 * the 45 degree angle allows the sensors to detect the wall earlier allowing for smoother velocity transitions and preventing stuttering in logic

Finish detection:
 * used a compact QTR type IR sensor that faces the ground with a small mounting point in an accessible location in the middle of the chassis
 * this allows for a digital output signal showing whether the color of the ground is reflective or not (Effectively black/white) and thus allows me to find the differently colored finish grid

Inverted motor mount:
 * I mounted the motors on the top side of the chassis plate rather than the bottom
 * This lowers the entire chassis to the ground, lower CoM reduces the moment of inertia in high speed turns, massively decreasing the force that tips the robot/prevents it from losing traction

# 2025-2026 Iteration Comparison

In the 2025 version, the motors were at the bottom of the plate which not only meant the robot would be really high off the ground compared to other robots but also meant that because the caster wheel was shorter than the height of the chassis plate from the ground, it made the entire robot stand on a 15 degree angle which ruined the sensors' output becasue the sensors were effectively looking at the ground instead of forward
