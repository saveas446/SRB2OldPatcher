cmake_minimum_required(VERSION 3.10)

project(SRB2OldPatcher C)


add_executable(${PROJECT_NAME}
	src/file.c
	src/init.c
	src/main.c
	src/patch.c
)