# STL parser
A command line utility for converting between ASCII and binary STL files, getting the
volume, number of vertices & surface area and calculating a rough price estimate of a 3D
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
weight of the inner part that has a certain percentage of infill, also given as input.<br>
The volume is calculated as the sum of the signed volumes of the tetrahedrons from a given
point in space, thus it returns a correct value for STL files with an arbitrary complexity.
There may be certain edge cases when a few triangles overlap or the STL does determine a closed
form in space. This time an incorrect result may be produced as a result since there is no
error checking on triangles.

## Usage
```
Usage: stlp <filename> [-c=asc|bin | -i | -p <infill> <fprice> <wall-width> <material>]
  -c=asc|bin: convert to ASCII or binary STL, output file is 'output.stl' created in the current directory
  -i: info about STL file (closed volume, number of vertices, surface area, number of triangles)
  -h: prints usage
  -p <infill> <fprice> <wall-width> <material>: calculates the price of an FDM 3D-printed model
    <infill>: amount of infill used by the printer in percentage (default is 20)
    <fprice>: price of 1 gramm of filament used to print the model in dollars (default is 0.08)
    <wall-width>: width of the outer, solid wall in millimeters (default is 1.2)
    <material>: type of materail used for printing, exactly one of:
      PLA, ABS, PETG, TPU, WOOD
  If only <filename> is given as argument then it's the same as executing stlp <filename> -i
```
<b>Note:</b> `surface area` is returned in cm<sup>2</sup> and `volume` is returned in
cm<sup>3</sup>
