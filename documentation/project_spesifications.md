Bism Ellah Elrahman Elraheem

Project objective: Implement basic ray tracing

Why doing this project: Implement any mathematica or physics formula

https://docs.google.com/document/d/1ZUn8sJV5SKje-yurw1b1dVOwP1tbiKDsGnjxgKc2JNM/edit?usp=sharing

Description: using ray-tracing protocol generate image based on scene, with specific angle, position, lighting, geomitry

Allowed functions:
Math library
Minilibx Library
libft
open
close
read
write
printf
malloc
free
exit
perror
strerror


Questions:
What is ray tracing?
What are the formula of ray tracing?
what are ambient and diffused light?

## Specifications:
---------------
1-Use Minilibx

2-Smooth window managment, minimizing, and maximizing, change to another window...

3-Mandatory needed objects:
	
	a)Plane
	b)sphere
	c_Cylinder

4-Handle correctly possible intersections at inside the object (if applicable)

5-Handle resizing object unique property (ex: Diameter of sphere, width and height of cylinder)

6-Apply translation and rotation transformation to objects:
	
	a)Lights
	b)Cameras
(Except for the sphere and the light that cannot be rotated)

7-Light management:
	
	a)spotlight brightness
	b)hard shadow
	c)Ambient lighting(objects are never completly in the dark)
	d)implement ambient and diffused lighting

8-Program display the image in a window and respect the following rules:
	
	a)ESC or x on the upper left of the window close the window and clean memory
	b)Use of Minilibx Image

9)Executable as follows:
	./minirt scene_description.rt

10)Scene decription file:
	
	a)each type of element separated by one or more line breakers
	b)Type of info of an element separated by one or more space
	C)Each type set in any order in a function
	D)Elements with capital letter declared once in the scene
		-First information type identifier(one or two chars)
		-Followed by specific information in a strict order

ex:
		  >Ambient lightning:

		A 0.2 255,255,255
		*Identifier A
		*ratio in range [0.0, 0.1] :0.2
		*R,G,B[0-255]: 255, 255, 255
	
	  >Camera:
			C -50.0,0,20	0,0,1	70
		*Identifier C
		*x, y, z coordinate view point: 0.0, 0.0, 20.6
		∗3d normalized orientation vector. In range [-1,1] for each x,y,z axis 0.0,0.0,1.0
		∗FOV : Horizontal field of view in degrees in range [0,180]
	
	  >Light:
			L   -40.0,50.0,0.0 0.6	10,0,255
			∗identifier: L
			∗x,y,z coordinates of the light point: 0.0,0.0,20.6
			∗the light brightness ratio in range [0.0,1.0]: 0.6
			∗(unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
		  >◦Sphere:
				sp  0.0,0.0,20.6 12.6  10,0,255
			∗identifier: sp
			∗x,y,z coordinates of the sphere center: 0.0,0.0,20.6
			∗the sphere diameter: 12.6
			∗R,G,B colors in range [0-255]: 10, 0, 255

		  >Plane:
				pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
			∗identifier: pl
			∗x,y,z coordinates: 0.0,0.0,-10.0
			∗3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
			0.0,0.0,1.0
			∗R,G,B colors in range [0-255]: 0, 0, 255
		  >Cylinder:
				cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42  10,0,255
			∗identifier: cy
			∗x,y,z coordinates: 50.0,0.0,20.6
			∗3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
			∗the cylinder diameter: 14.2
			∗the cylinder height: 21.42
			∗R,G,B colors in range [0,255]: 10, 0, 255
			7

Example of .rt scene:

11)"Erro\n" with message in case of anny error

12)Create defence scenes in advance







Study notes:
Colors are treated as vecotr
(100, 0, 30) you can operate vectors operations on it
However: max is 255 and min is0

Abstracted code for the project 

	Place the eye and the frame as desired
	For each square on the canvas
    	Determine which square on the grid corresponds to this square on the canvas
    	Determine the color seen through that grid square
    	Paint the sq`uare with that color