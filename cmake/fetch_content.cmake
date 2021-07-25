include_guard()

option(FETCHCONTENT_UPDATES_DISCONNECTED "by default do not try to update the repo each time" ON)

include(FetchContent)

macro(nya_fetch_content FETCH_REPO FETCH_TAG #[[<args for FetchContent_Declare>]])
	get_filename_component(FETCH_NAME ${FETCH_REPO} NAME_WE)
	message("++ fetch: " ${FETCH_NAME})

	fetchcontent_declare(${FETCH_NAME}
			GIT_REPOSITORY ${FETCH_REPO}
			GIT_TAG ${FETCH_TAG}
			${ARGN}
	)
	fetchcontent_makeavailable(${FETCH_NAME})
endmacro(nya_fetch_content)
