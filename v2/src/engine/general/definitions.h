#ifndef TE_DEFINITIONS_H
#define TE_DEFINITIONS_H


//the struct is ordered bgra because of SDL's window surface's structure
struct te_color {
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
} typedef te_color;

struct te_vertex {
	float x;
	float y;
	float z;

	te_color color;
} typedef te_vertex;

#define TE_OKAY 0
#define TE_ERROR 1 

//configurations
#define TE_NO_RENDERER 0
#define TE_SOFTWARE_RENDERER 1

#endif