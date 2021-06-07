#pragma once
/* Enable Platform, Debub and Log System */
#define MH_ENGINE  "MHelmet Engine {}"
#define MH_VERSION "Alpha Version 0.1"

/* OpenGl eith GLFW option*/
#define MH_ENABLE_CORE true

#define MH_PLATFORM_WIN 1
#define MH_DEBUG 1
#define MH_LOG_SYSTEM 1

/* Default window Props  */
#define MH_TITLE	"MHelmet"
#define MH_WIDTH	1280
#define MH_HEIGHT	720
#define MH_FULL_SRC	false
#define MH_VSYNC	true

#if MH_LOG_SYSTEM	
	#define MH_ENABLE_VERIFY
	#if MH_DEBUG
		#define MH_ASSERT_SYSTEM		
	#endif
#endif

/* some necessary things, for now I leave here */
#define STB_IMAGE_IMPLEMENTATION /* stbi.h image implementation */