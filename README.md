# STL parser
A command line utility for converting between ASCII and binary STL files, getting the closed
volume, number of vertices and surface area and calculating a rough price estimate of a 3D
printed model.

## Algorithm for price calculation
Due to the structure of the STL file, it is not possible to calculate the exact price of a 3D
printed model since it only contains a mesh made up of triangles and a normal vector for each
of those triangles. Popular slicers like Cura or Slic3r make a good job of calculating the price of a 3D
model by generating the associated gcode, acquiring information such as the feed path or print
time.<br>
However, calculating the price merely from an STL file is a lot simpler and faster than slicing
(and less accurate at the same time).<br>
Pseudocode for price calculation:
```
  function calculate_price:
    area = surface area of mesh
    volume = volume of mesh
    outer_shell_volume = area * wall_width 
    inner_infill_volume = volume - outer_shell_volume
    return outer_shell_voluem * filament_density + inner_infill_volume * filament_density * wall_width
```
The above function calculates the weight of the outer shell (the outermost part of the model
that is printed with 100% infill and has a width of `wall_width`, given as input) and the
weight of the inner part that has a given percentage of infill, given as input.<br>
Note that the volume of the STL file is naively calculated as the sum of the tetrahedrons with
one of the vertices being an arbitrary point in the mesh. Therefore, it returns an overcounted
result for non-closed solids but it is fairly accurate for simpler, closed forms.

## Usage
```
Usage: stla [-c=asc|bin | -i | -p <infill> <fprice> <wall-width> <material>] <filename>
-c=asc|bin: convert to ASCII or binary STL
-i: info about STL file (closed volume, number of vertices, surface area)
-p <infill> <fprice>: calculates the price of an FDM 3D-printed model
<infill>: amount of infill used by the printer in percentage (default is 20)
<fprice>: price of 1 gramm of filament used to print the model in dollars (default is 0.08)
<wall-width>: width of the outer, solid wall in millimeters (default is 1.2)
<material>: type of materail used for printing, exactly one of:
PLA, ABS, PETG, TPU, WOOD
```
