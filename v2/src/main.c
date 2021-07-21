#include <te.h>

int main()
{
	if(te_init("HALLO", 1366, 768, 0)!=TE_OKAY)
	{
		printf("error while initialization\n");
	}

	te_start_renderer(TE_SOFTWARE_RENDERER);

}