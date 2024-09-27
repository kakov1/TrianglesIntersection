from sympy import Point
from sympy.geometry import Segment, Line3D,  Triangle, Point
from sympy.sets import EmptySet
from random import uniform, randint


def generate_point():
    return Point(randint(-2, 2), randint(-2, 2), randint(-2, 2))

tests_file = open("tests_segments_int.txt","w")
answers_file = open("answers_segments_int.txt", "w")
for i in range(20):
    points = []
    for j in range(4):
        points.append(generate_point())
    a, b = Segment(*points[0:2]), Segment(*points[2:4])
    points = " ".join([" ".join(i) for i in list(map(lambda x: map(str, x), map(list, points)))])
    tests_file.write(f"{points}\n")
    print(a.intersection(b))
    answers_file.write(f"{str(a.intersection(b))}")
