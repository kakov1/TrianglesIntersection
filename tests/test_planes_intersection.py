from sympy import Point
from sympy.geometry import Segment, Plane
from sympy.sets import EmptySet
from random import uniform, randint

segment1 = Segment(Point(-5.84383, 5.51216, 6.36387),Point(-5.65325, 5.68873, 6.63786))
segment2 = Segment(Point(-7.77751, 3.7206, 3.58375), Point(-6.11926, 5.25698, 5.96788))

print(segment1.intersect(segment2))