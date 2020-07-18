option(FETCHCONTENT_UPDATES_DISCONNECTED "by default do not try to update the repo each time" ON)

include(FetchContent)

# FetchContent into ../folder_name
# nya_fetch(<git_url> <tag|branch|hash> <folder_name>)
macro(nya_fetch)
	if(NOT ${ARGC} EQUAL 0)
		if(${ARGC} GREATER 1)
			set(FETCH_TAG ${ARGV1})
		else()
			set(FETCH_TAG master)
		endif()

		if(${ARGC} GREATER 2)
			set(FETCH_NAME ${ARGV2})
		else()
			get_filename_component(FETCH_NAME ${ARGV0} NAME_WE)
		endif()

		get_filename_component(FETCH_ROOT ${CMAKE_SOURCE_DIR}/../${FETCH_NAME}  ABSOLUTE)

		message("++ fetch: " ${FETCH_ROOT})

		FetchContent_Declare(${FETCH_NAME}
				GIT_REPOSITORY ${ARGV0}
				GIT_TAG        ${FETCH_TAG}
				SOURCE_DIR     ${FETCH_ROOT}
		)
		FetchContent_MakeAvailable(${FETCH_NAME})
	endif()
endmacro(nya_fetch)
