cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(libglesgae)

# Compile Options
option(USE_SDL2 "Use SDL2 Bindings" ON)
option(USE_OGL "Use OpenGL Bindings" OFF)
option(USE_D3D "Use D3D Bindings" OFF)
option(USE_GLES1 "Use GLES1 Bindings" OFF)
option(USE_GLES2 "Use GLES2 Bindings" OFF)
option(USE_SDL "Use SDL1 Bindings" OFF)
option(USE_SDLGL "Use SDL1 with platform GL" OFF)
option(USE_SDL2GL "Use SDL2 with platform GL" OFF)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

# Default, platform agnostic code
set(GLESGAE_BASE
	GAE_Types.c
	Events/Event.c
	Events/EventSystem.c
	External/jsmn/jsmn.c
	Input/Controller.c
	Maths/Matrix.c
	Maths/Vector.c
	States/StateStack.c
	Time/Timer.c
	Utils/Array.c
	Utils/HashString.c
	Utils/List.c
	Utils/Logger.c
	Utils/Map.c
	Utils/Tiled/TiledJsonLoader.c)

# SDL2 specifics
if (USE_SDL2)
	set(GLESGAE_RENDERER
		Events/SDL2/SDL2Events.c
		Events/SDL2/SDL2EventSystem.c
		Graphics/Context/SDL2/SDL2RenderContext.c
		Graphics/Renderer/SDL2/SDL2Renderer.c
		Graphics/System/SDL2/SDL2GraphicsSystem.c
		Graphics/Sprite/SDL2/Sprite.c
		Graphics/Target/Texture/SDL2/TextureRenderTarget.c
		Graphics/Texture/SDL2/SDL2Texture.c
		Graphics/Window/SDL2/SDL2RenderWindow.c
		Input/SDL2/SDL2InputSystem.c
		Platform/SDL2/SDL2Platform.c
		Utils/Tiled/SDL2/SDL2TiledJsonLoader.c)
	add_definitions(-DSDL2)
	include_directories(../SDL2/prebuilt/include)
	link_directories(../SDL2/prebuilt/lib)
endif (USE_SDL2)

# OGL specifics
if (USE_OGL)
	if (UNIX)
		set(GLESGAE_RENDERER
			Events/X11/X11EventSystem.c
			External/SOIL/image_DXT.c
			External/SOIL/image_helper.c
			External/SOIL/SOIL.c
			External/SOIL/stb_image_aug.c
			Graphics/VertexBuffer.c
			Graphics/Shader.c
			Graphics/Mesh.c
			Graphics/Material.c
			Graphics/IndexBuffer.c
			Graphics/Camera.c
			Graphics/Context/GLX/GLee.c
			Graphics/Context/GLXRenderContext.c
			Graphics/Renderer/GLES20/ShaderGLVboRenderer.c
			Graphics/Sprite/3D/Sprite.c
			Graphics/State/GLES2/GLES2State.c
			Graphics/Target/Buffer/OGL/BufferRenderTarget.c
			Graphics/Target/Screen/OGL/ScreenRenderTarget.c
			Graphics/Target/Texture/OGL/TextureRenderTarget.c
			Graphics/Texture/GL/GLTexture.c
			Graphics/Window/X11/X11RenderWindow.c
			Input/Linux/LinuxInputSystem.c
			Platform/Linux/LinuxPlatform.c)
		add_definitions(-DGLX)
	elseif (WIN32)
		set(GLESGAE_RENDERER )
	elseif (APPLE)
		set(GLESGAE_RENDERER )
	endif (UNIX)
endif (USE_OGL)

# D3D Specifics
if (USE_D3D)
	set(GLESGAE_RENDERER )
endif (USE_D3D)

# GLES 1 Specifics
if (USE_GLES1)
	set(GLESGAE_RENDERER )
endif (USE_GLES1)

# GLES 2 Specifics
if (USE_GLES2)
	set(GLESGAE_RENDERER )
endif (USE_GLES2)

# SDL Specifics
if (USE_SDL)
	set(GLESGAE_RENDERER )
endif (USE_SDL)

# SDL with GL Specifics
if (USE_SDLGL)
	set(GLESGAE_RENDERER )
endif (USE_SDLGL)

# SDL2 with GL Specifics
if (USE_SDL2GL)
	set(GLESGAE_RENDERER )
endif (USE_SDL2GL)

# Platform specifics
if (UNIX)
	set(GLESGAE_PLATFORM
		File/Linux/File.c
		Time/Linux/Clock.c)
	add_definitions(-DLINUX)
elseif (WIN32)
	set(GLESGAE_PLATFORM
		File/Win32/File.c
		Time/Win32/Clock.c)
	add_definitions(-DWIN32)
elseif (APPLE)
endif (UNIX)

add_library(glesgae STATIC
	${GLESGAE_BASE}
	${GLESGAE_RENDERER}
	${GLESGAE_PLATFORM}
	)

# deal with link dependencies now
if (USE_SDL2)
	target_link_libraries(glesgae SDL2 SDL2main SDL2_image SDL2_net SDL2_ttf SDL2_mixer)
endif (USE_SDL2)
