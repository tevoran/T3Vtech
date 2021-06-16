#include <te.hpp>


namespace t3v
{
	class object3d
	{
	private:
		t3v::vertex *m_vertices=NULL;
		uint32_t m_num_vertices;
		t3v::texture *m_texture=NULL;
		glm::mat4 m_current_rotation;

	public:
		glm::vec3 pos={0,0,0};

	public:
		object3d();
		~object3d();

		void use_vertices(t3v::vertex *vertices_in, const int num_vertices);
		void use_texture(t3v::texture *texture_in);
		void rotate(glm::vec3 axis, float rotation_degrees);
		void position();
		void render();
	};
}