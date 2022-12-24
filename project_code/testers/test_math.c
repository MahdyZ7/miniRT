#include "../miniRT.h"

void	test_vec_cross(void)
{
	t_vec	vec1;
	t_vec	vec2;
	t_vec	result;

	printf("\n\ntesting vectors cross product\n\n");
	fill_single_vector(&vec1, 1, 2, 3);
	fill_single_vector(&vec2, 4, 5, 6);
	result = vec_cross(vec1, vec2);
	printf("v1 X v2 = ");
	vis_vector(vec1);
	printf(" X ");
	vis_vector(vec2);
	printf(" = ");
	vis_vector(result);
	printf("\n");
}

void	test_vec_dot(void)
{
	t_vec	vec1;
	t_vec	vec2;
	float	result;

	printf("\n\ntesting vectors Dot product\n\n");
	fill_single_vector(&vec1, 1, 2, 3);
	fill_single_vector(&vec2, 4, 5, 6);
	result = vec_dot(&vec1, &vec2);
	printf("v1 X v2 = ");
	vis_vector(vec1);
	printf(" X ");
	vis_vector(vec2);
	printf(" = ");
	printf("%3.2f\n", result);
}
