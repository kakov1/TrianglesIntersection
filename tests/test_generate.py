from sympy import Point
from sympy.geometry import Segment, Line3D,  Triangle, Point
from sympy.sets import EmptySet
from random import uniform, randint

Line3D()
def generate_point():
    return Point(randint(-10, 10), randint(-10, 10))

def generates_points():
    return generate_point(), generate_point()

def is_real_triangle(a, b, c):
   return a.distance(b) + b.distance(c) > a.distance(c) and\
          a.distance(b) + a.distance(c) > b.distance(c) and\
          a.distance(b) + a.distance(c) > b.distance(c)

a, b, c = generates_points()

print(a, b, c)

while not is_real_triangle(a, b, c):
    a, b, c = generates_points()
    
print(a, b, c)
    
triangle = Triangle(a, b, c)

print(triangle)
