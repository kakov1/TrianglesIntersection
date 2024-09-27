from sympy import Point
from sympy.geometry import Segment, Plane
from sympy.sets import EmptySet
from random import uniform, randint

segment1 = Segment(Point(-143.472, 179.316, 486.538),Point(-276.165, 40.4917, 509.594))
segment2 = Segment(Point(-272.371, 44.4615, 508.934), Point(-409.868, -99.389, 532.824))

print(segment1.intersect(segment2))