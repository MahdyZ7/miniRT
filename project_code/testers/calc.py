import numpy as np 

#testing cross product 
vec1 = np.array([1, 2, 3])
vec2 = np.array([4, 5, 6])

result = np.cross(vec1, vec2)
print("cross product is", result);

#testing dot product
result = np.dot(vec1, vec2)
print("dot product is", result);