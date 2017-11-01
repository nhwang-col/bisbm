README for biSBM v1.2

Daniel Larremore
Harvard School of Public Health
July 29, 2014
http://danlarremore.com/bipartiteSBM
daniel.larremore@gmail.com

biSBM - a method for community detection in bipartite networks, based on the publication: 
	"Efficiently inferring community structure in bipartite networks"
	Daniel B. Larremore, Aaron Clauset, and Abigail Z. Jacobs 
	Physical Review E 90(1), 012805 (2014).
	http://danlarremore.com/pdf/2014_LCJ_EfficientlyInferringCommunityStructureInBipartiteNetworks_PRE.pdf

/***** MATLAB vs R vs C++ *****/

This file explains how to use the pure MATLAB version of the biSBM code. If you prefer using a wrapper in R or just pure C++, see README_R.txt or README_cplusplus.txt. 

/***** Overview *****/

I. Installation
II. License, Usage, and Distribution
III. Citation
IV. Submit a bug or Translate this code
V. License

v1.1 - Increased the maximum number of edges to 10,000,000, maximum number of vertices to 1,000,000, and maximum number of communities to 1,000. Code now exits if Log(x) for x<0 is called, instead of just warning. 


/***** I. Installation *****/

The implementation of the biSBM algorithm described in the paper is written in C++ using a MATLAB mex file. Please see MATLAB documentation for installation or troubleshooting of mex files or MATLAB.

1. Place the files 
	biSBM.m
	biSBM.h
	biSBM_MATLAB.cpp
	-----
	example_MATLAB.m
	southernWomen.edgelist
	southernWomen.types
	test.edgelist
	test.types
into the MATLAB directory of your choice. 

2. Compile the biSBMcore.cpp in MATLAB by typing
	mex biSBM_MATLAB.cpp
which should produce the message
	MEX completed successfully.

This procedure has been tested using MATLAB R2014a and OSX 10.9.2. There are known issues for various combinations of MATLAB and OSX / XCode. These are beyond the scope of this installation, but solutions are searchable online. 

/***** II. License, Usage, and Distribution *****/

This code is freely available and open source under a Creative Commons Non-commercial Share-alike license. This means that you are free to use the code only for non-commercial purposes, and you may modify and share this code freely, provided that the modified code is ALSO non-commercial and share-alike. For details, read LICENSE.txt.

/***** III. Citation *****/

This code is based on 
	Efficiently inferring community structure in bipartite networks
	Daniel B. Larremore, Aaron Clauset, Abigail Z. Jacobs
	Physical Review E 90(1), 012805 (2014)
Please cite as appropriate. If you choose to apply the code without discussing the algorithm, please send an email to the authors (daniel.larremore@gmail.com) to let us know—just curious!

/***** IV. Submit a bug or Translate this code *****/

Please submit any and all bugs to daniel.larremore@gmail.com, as well as any corrections, so that we may correct the official posted version. 

If you translate this code from a MATLAB wrapper into another language, we will freely host your implementation and acknowledge your contribution on the biSBM site. Note that some translations already exist on the website. Get in touch at daniel.larremore@gmail.com

/***** V. License *****/

This bipartite stochastic blockmodel (biSBM) implementation by Daniel Larremore is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.