#include <te.hpp>

glm::mat4 t3v::rotation_quaternion(glm::mat4& rotation_mat_in, glm::vec3& rotation_axis, float rotation_degrees)
{
	float rot_value=rotation_degrees*2*PI/360;
	rot_value=rot_value/2; //necessary due to the use of quaternions

	//quaternion
	glm::vec4 rot=glm::vec4(
		rotation_axis.x*sin(rot_value),
		rotation_axis.y*sin(rot_value),
		rotation_axis.z*sin(rot_value),
		cos(rot_value));

	rot=glm::normalize(rot);

	glm::mat4 mat_tmp=glm::mat4(1.0f); //quaternion rotation matrix
	mat_tmp[0].x=1-2*(rot.y*rot.y + rot.z*rot.z);
	mat_tmp[0].y=2*(rot.x*rot.y + rot.z*rot.w);
	mat_tmp[0].z=2*(rot.x*rot.z - rot.y*rot.w);

	mat_tmp[1].x=2*(rot.x*rot.y - rot.z*rot.w);
	mat_tmp[1].y=1-2*(rot.x*rot.x + rot.z*rot.z);
	mat_tmp[1].z=2*(rot.y*rot.z + rot.x*rot.w);

	mat_tmp[2].x=2*(rot.x*rot.z + rot.y*rot.w);
	mat_tmp[2].y=2*(rot.y*rot.z - rot.x*rot.w);
	mat_tmp[2].z=1-2*(rot.x*rot.x + rot.y*rot.y);


	return rotation_mat_in * mat_tmp;
}