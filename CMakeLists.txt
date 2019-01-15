cmake_minimum_required(VERSION 3.7)
cmake_policy(SET CMP0015 NEW)

project(libglesgae)

set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic -Wno-variadic-macros -Wcast-align -Wredundant-decls -Wextra -pedantic-errors")

# Compile Options
option(USE_SDL2 "Use SDL2 Bindings" OFF)
option(USE_OGL "Use OpenGL Bindings" OFF)
option(USE_SDL2GL "Use SDL2 with platform GL" OFF)
option(USE_EMSCRIPTEN "Use Emscripten" OFF)

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
	Graphics/Sprite/Frame.c
	Graphics/Sprite/Sprite.c
	Input/Controller.c
	Maths/Matrix.c
	Maths/Point.c
	Maths/Rect.c
	Maths/Vector.c
	States/State.c
	States/StateStack.c
	Time/Timer.c
	Utils/Array.c
	Utils/ArrayList.c
	Utils/Group.c
	Utils/Heap.c
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
		Graphics/Texture.c
		Graphics/Context/SDL2/SDL2RenderContext.c
		Graphics/Renderer/SDL2/SDL2Renderer.c
		Graphics/System/SDL2/SDL2GraphicsSystem.c
		Graphics/Target/Texture/SDL2/TextureRenderTarget.c
		Graphics/Texture/SDL2/SDL2Texture.c
		Graphics/Window/SDL2/SDL2RenderWindow.c
		Input/SDL2/SDL2InputSystem.c
		Platform/SDL2/SDL2Platform.c
		Utils/Tiled/SDL2/SDL2TiledJsonLoader.c)
	add_definitions(-DSDL2)
	find_package(SDL2 REQUIRED)
	include_directories(${SDL2_INCLUDE_DIRS})
endif (USE_SDL2)

# Emscripten specifics
if (USE_EMSCRIPTEN)
	set(GLESGAE_RENDERER
		Events/SDL2/SDL2Events.c
		Events/SDL2/SDL2EventSystem.c
		Graphics/Texture.c
		Graphics/Context/SDL2/SDL2RenderContext.c
		Graphics/Renderer/SDL2/SDL2Renderer.c
		Graphics/System/SDL2/SDL2GraphicsSystem.c
		Graphics/Target/Texture/SDL2/TextureRenderTarget.c
		Graphics/Texture/SDL2/SDL2Texture.c
		Graphics/Window/SDL2/SDL2RenderWindow.c
		Input/SDL2/SDL2InputSystem.c
		Platform/SDL2/SDL2Platform.c
		Utils/Tiled/SDL2/SDL2TiledJsonLoader.c)
	add_definitions(-DSDL2)
	add_definitions(-s USE_SDL=2)
endif (USE_EMSCRIPTEN)

# OGL specifics
if (USE_OGL)
	remove_definitions(-DSDL2)
	if (UNIX)
		set(GLESGAE_RENDERER
			Events/X11/X11EventSystem.c
			Graphics/VertexBuffer.c
			Graphics/Shader.c
			Graphics/Mesh.c
			Graphics/Material.c
			Graphics/IndexBuffer.c
			Graphics/Camera.c
			Graphics/Texture.c
			Graphics/Context/GLX/GLee.c
			Graphics/Context/GLX/GLXRenderContext.c
			Graphics/Renderer/GLES20/ShaderGLVboRenderer.c
			Graphics/State/GLES2/GLES2State.c
			Graphics/System/X11/X11GraphicsSystem.c
			Graphics/Target/Buffer/OGL/BufferRenderTarget.c
			Graphics/Target/Screen/OGL/ScreenRenderTarget.c
			Graphics/Target/Texture/OGL/TextureRenderTarget.c
			Graphics/Texture/GL/GLTexture.c
			Graphics/Window/X11/X11RenderWindow.c
			Input/Linux/LinuxInputSystem.c
			Platform/Linux/LinuxPlatform.c
			Utils/Tiled/OGL/GLTiledJsonLoader.c)
		add_definitions(-DGLX)
	elseif (WIN32)
		set(GLESGAE_RENDERER )
	elseif (APPLE)
		set(GLESGAE_RENDERER )
	endif (UNIX)
endif (USE_OGL)

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

add_custom_command(TARGET glesgae POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glesgae> ../lib/$<TARGET_FILE_NAME:glesgae>)

# deal with link dependencies now
if (USE_SDL2)
	target_link_libraries(glesgae ${SDL2_LIBRARIES})
endif (USE_SDL2)

