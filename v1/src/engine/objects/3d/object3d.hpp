#pragma once
#include <te.hpp>

#define TE_OBJECT3D_NONE 0
#define TE_OBJECT3D_EXTERN_VERTICES 1
#define TE_OBJECT3D_QUAD 2
#define TE_OBJECT3D_CUBE 3

namespace t3v
{
	class object3d
	{
	private:
		t3v::vertex *m_vertices=NULL;
		uint32_t m_num_vertices;
		t3v::texture *m_texture=NULL;
		glm::mat4 m_current_rotation;
		glm::vec3 m_pos={0,0,0};
		glm::vec3 m_scale={1,1,1}; //starts with no scaling

		int m_data_type=TE_OBJECT3D_NONE; //necessary for destructor

	public:
		object3d();
		~object3d();

		void use_vertices(t3v::vertex *vertices_in, const int num_vertices);
		void use_texture(t3v::texture *texture_in);
		void rotate(glm::vec3 axis, float rotation_degrees);
		void position(glm::vec3 position);
		void scale(float scale);
		void scale(glm::vec3 scale);
		void render();

		//meshes
		void make_quad(float width, float height); //creating quad primitive
		void make_cube(float size); //create simple cube
	};
}