from sympy import Point
from sympy.geometry import Segment, Line3D
sg1 = Line3D((1, 2, 3),(2,1,0))
sg2 = Line3D((1,0,2),(2,3,0))
print(sg1.intersect(sg2))