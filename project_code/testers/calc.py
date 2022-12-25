import numpy as np 

# #testing cross product 
# vec1 = np.array([1, 2, 3])
# vec2 = np.array([4, 5, 6])

# result = np.cross(vec1, vec2)
# print("cross product is", result);

# #testing dot product
# result = np.dot(vec1, vec2)
# #test adding
# print("addition is", result);
# result = np.add(vec1, vec2)
# print("add is", result);
# #test subtraction
# result = np.subtract(vec1, vec2)
# print("subtraction is", result);
# #test vec scalar multiplicaiton
# result = vec1 * 5
# print("vector scalar mult is", result);


for i in range(10):
	roots = np.roots([i, i * i , i ])
	print(roots)