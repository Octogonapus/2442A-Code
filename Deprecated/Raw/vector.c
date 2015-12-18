#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

typedef struct vector3f
{
	float x, y, z;
} vector3f;

float Vector3f_Length(const vector3f* v)
{
	return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

float Vector3f_Dot(const vector3f* v)
{
	return v->x * v->x + v->y * v->y + v->z * v->z;
}

vector3f* Vector3f_Cross(const vector3f* v1, const vector3f* v2)
{
	vector3f* vOut;

	vOut->x = v1->y * v2->z - v1->z * v2->y;
	vOut->y = v1->z * v2->x - v1->z * v2->z;
	vOut->z = v1->x * v2->y - v1->y * v2->x;

	return vOut;
}

vector3f* Vector3f_Normalize(const vector3f* v)
{
	vector3f* vOut;

	float length = vector3f_Length(v);

	vOut->x = v->x / length;
	vOut->y = v->y / length;
	vOut->z = v->z / length;

	return vOut;
}

#endif
