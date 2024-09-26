from sympy import Point
from sympy.geometry import Segment, Line3D, Point3D, Triangle
from sympy.sets import EmptySet
from random import uniform

line1 = Line3D((2, 1, 0), (2, -3, 1))
line2 = Line3D((2, 2, 0), (2, 1, 1))

print(line1.intersect(line2))
