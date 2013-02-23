cmake_minimum_required( VERSION 2.6 )
#set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvmgcc42")
if (DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel")
else()
	message(STATUS "No build type selected, default to Debug")
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel")
endif()

project( ten )

add_subdirectory( vectorstorm )

set(SOURCES
	Games/Ten/Modes/TEN_ModeCredits.cpp
	Games/Ten/Modes/TEN_ModeInGame.cpp
	Games/Ten/Modes/TEN_ModeTitle.cpp
	Games/Ten/TEN_Fader.cpp
	Games/Ten/TEN_Camera.cpp
	Games/Ten/TEN_Game.cpp
	Games/Ten/TEN_Starfield.cpp
	Games/Ten/TEN_Whale.cpp
	main.cpp
	)


include_directories( SYSTEM
	${OPENGL_INCLUDE_DIR}
	${SDL_INCLUDE_DIR} 
	${SDL_MIXER_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
	${BOX2D_INCLUDE_DIR}
	)

include_directories( . vectorstorm vectorstorm/VS )

set(PLATFORM_SOURCES)
set(PLATFORM_LIBRARIES)

if(UNIX)
	if(APPLE)
		set(GUI_TYPE MACOSX_BUNDLE)
		find_library(OPENGL_LIBRARY OpenGL)
		find_library(COCOA_LIBRARY Cocoa)
		mark_as_advanced(BOX2D_LIBRARY SDL_LIBRARY SDL_MIXER_LIBRARY SDL_IMAGE_LIBRARY PNG_LIBRARY GLEW_LIBRARY)
		set(PLATFORM_SOURCES SDLMain.m )	
		set(PLATFORM_LIBRARIES ${COCOA_LIBRARY})
		set(CMAKE_OSX_DEPLOYMENT_TARGET "10.7")
	endif()
	add_definitions("-D UNIX")
else () # Windows?
	set(PLATFORM_LIBRARIES 		
		OpenGL32
		WSock32
		)
endif ()

# find . -type d
include_directories(
	Games
	Games/Ten
	Games/Preferences
	)


add_executable(
	ten
	MACOSX_BUNDLE
	${SOURCES}
	${PLATFORM_SOURCES}
	)

# Prefix files
if (UNIX)
	set(CMAKE_CXX_FLAGS_DEBUG "-include VS_VectorStorm_Debug.h ${CMAKE_CXX_FLAGS_DEBUG}")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-include VS_VectorStorm_Debug.h ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
	set(CMAKE_CXX_FLAGS_RELEASE "-include VS_VectorStorm.h ${CMAKE_CXX_FLAGS_RELEASE}")
	set(CMAKE_CXX_FLAGS_MINSIZEREL "-include VS_VectorStorm.h ${CMAKE_CXX_FLAGS_MINSIZEREL}")
else ()
	set(CMAKE_CXX_FLAGS_DEBUG "/FI VS_VectorStorm_Debug.h ${CMAKE_CXX_FLAGS_DEBUG}")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/FI VS_VectorStorm_Debug.h ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
	set(CMAKE_CXX_FLAGS_RELEASE "/FI VS_VectorStorm.h ${CMAKE_CXX_FLAGS_RELEASE}")
	set(CMAKE_CXX_FLAGS_MINSIZEREL "/FI VS_VectorStorm.h ${CMAKE_CXX_FLAGS_MINSIZEREL}")
endif()

# Build source groups, for IDEs.
foreach( pathSourceFile ${SOURCES} )

	get_filename_component( pathSourceGroup ${pathSourceFile} PATH )

	if( NOT ${pathSourceGroup} STREQUAL ${CMAKE_SOURCE_DIR} )

		# Make the path relative to the base source path
		string( REPLACE ${CMAKE_SOURCE_DIR} "" pathSourceGroup
			${pathSourceGroup} )

		# Remove starting / and \
		string( SUBSTRING ${pathSourceGroup} 0 1 firstChar )
		if( firstChar STREQUAL "/" OR
				firstChar STREQUAL "\\" )

			string( LENGTH ${pathSourceGroup} strLen )
			math( EXPR strLen "${strLen} - 1" )
			string( SUBSTRING ${pathSourceGroup} 1 ${strLen}
				pathSourceGroup )
		endif()

		# Replace / with \ so the source groups work correctly in MSVC
		string( REPLACE "/" "\\" pathSourceGroup ${pathSourceGroup} )

		# Add file to the source group
		get_filename_component( fileExtension ${pathSourceFile} EXT )
		if( ${fileExtension} MATCHES ".c" OR
				${fileExtension} MATCHES ".cpp" OR 
				${fileExtension} MATCHES ".h" OR
				${fileExtension} MATCHES ".hpp" )
			SOURCE_GROUP( "${pathSourceGroup}" FILES
				${pathSourceFile} )
		else()
			message( SEND_ERROR "Source grouping failed on file
			${pathSourceFile}" )
		endif()

	endif()

endforeach()

set(LIBRARIES 		
	${GLEW_LIBRARY}
	${OPENGL_LIBRARY} 
	${SDL_LIBRARY} 
	${SDL_MIXER_LIBRARY}
	${SDL_IMAGE_LIBRARY}
	${PNG_LIBRARY}
	${BOX2D_LIBRARY}
	)

target_link_libraries( ten
	vectorstorm
	${LIBRARIES}
	${PLATFORM_LIBRARIES} 
	)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS ten
	BUNDLE DESTINATION bin
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)

if(APPLE)
	set_target_properties(ten PROPERTIES XCODE_ATTRIBUTE_FRAMEWORK_SEARCH_PATHS "/Library/Frameworks/")	# Working around bug in XCode 4.3.3
	set(CMAKE_INSTALL_NAME_DIR @executable_path)
	set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
	set_target_properties(ten PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist")

	set_target_properties(ten
		PROPERTIES
		INSTALL_RPATH "@executable_path/../Frameworks"
		INSTALL_RPATH_USER_LINK_PATH TRUE
		LINK_FLAGS -Wl,-rpath,@executable_path/../Frameworks/
		XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym"
		XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "YES"
		#XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH_DEBUG "YES"
		#XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH_RELEASE "NO"
		)

	add_custom_command(TARGET ten
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CFG_INTDIR}/ten.app/Contents/Resources
		COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/Data ${CMAKE_CFG_INTDIR}/ten.app/Contents/Resources/
		COMMENT "Copying Data files into place"
		)

	set(BUNDLE "${CMAKE_CURRENT_BINARY_DIR}/ten.app")
	set(DIRS "/usr/local/lib")
	install(CODE "
		set(BU_CHMOD_BUNDLE_ITEMS ON)
		include(BundleUtilities)
		fixup_bundle(\"${BUNDLE}\" \"\" \"${DIRS}\")
		" COMPONENT Runtime)

endif()


