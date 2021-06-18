#pragma once

/*

Esto es una solucion de momento muy muy cutre La idea es tener una especie 
de unorderer_map mas adelanta y que la clase shader pueda acceder a ella, 
seria interesante que desde la interfaz puedieran anyadirse elementos 
a la libreria, aun no se muy bien como, pero con vectores,
sabiendo el tamanyo podria hacerse una reserva de memoria
o cualquier otra solucion mas eficiente que esta porqueria

*/

static struct Shad
{
	/* MATERIALS */
	struct Mat
	{
		const char* vertex   = "../assets/shaders/perspectiveShaders/MaterialShader/vertex.vs";
		const char* fragment = "../assets/shaders/perspectiveShaders/MaterialShader/fragment.fs";
	};
	struct Tex
	{
		const char* vertex   = "../assets/shaders/perspectiveShaders/TextureShader/vertex.vs";
		const char* fragment = "../assets/shaders/perspectiveShaders/TextureShader/fragment.fs";
	};	
};

static struct Text
{
	/* TEXTURES */
	const char* textBricks = "../assets/textures/bricks_albedo.png";
	const char* textBlueBlocks = "../assets/textures/blue_blocks.jpg";
	const char* textAlphaTree = "../assets/textures/tree.png";
};