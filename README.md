# This is the code for the simulations of the paper "On the onset of multicellular invasive behavior in hierarchical lineage: the role of inhibitory feedback and local fluctuations."

The simulations run on C++, and the output of these is graphed and visualized using a Jupyter Notebook in Python. Depending on the desired output, the simulations are divided into five different headers, contained in the directory "simulations". In each header file (files of the form *.h), one can change the simulation parameters in the first 20 lines of the code. These are the variables that can be assigned numerical values.
To perform the simulations, please follow these steps:
1. Change the path at line 14 of the file main.cpp to the directory where simulation output should be saved.
2. Relocate to this directory.
3. Run mkdir build
4. Run cd build
5. Run cmake ..
6. Run make
7. Run ./lgca *number*, where *number* is the number of the desired simulation header, 1 for sim001.h, 2 for sim002.h, and so on.
After running the simulations, the output can be visualized with the python notebooks generated in the "output" directory. Simply run these jupyter notebooks to obtain the plots.
