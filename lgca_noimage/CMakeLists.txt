cmake_minimum_required(VERSION 2.8)
project( lgca )
add_executable(
	lgca
	main.cpp
	wire/aux_func.h
	wire/node.h
	wire/lgca.h
	simulations/sim001.h
	simulations/sim002.h
	simulations/sim003.h
	simulations/sim004.h
	simulations/sim005.h
)