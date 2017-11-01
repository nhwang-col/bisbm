// biSBM v1.2
//
//Daniel Larremore
//Harvard School of Public Health
//July 29, 2014
//http://danlarremore.com/bipartiteSBM
//daniel.larremore@gmail.com
//
//biSBM - a method for community detection in bipartite networks, based on the publication:
//"Efficiently inferring community structure in bipartite networks"
//Daniel B. Larremore, Aaron Clauset, and Abigail Z. Jacobs
//Physical Review E 90(1), 012805 (2014).
//http://danlarremore.com/pdf/2014_LCJ_EfficientlyInferringCommunityStructureInBipartiteNetworks_PRE.pdf
//
// Please do not distribute without contacting the author above at daniel.larremore@gmail.com
// If a bug is located within the code, please contact the author, to correct the official version!
//
// This code is based on code written by Brian Karrer for the stochastic block model, http://arxiv.org/abs/1104.3590
// You can download that code at http://www-personal.umich.edu/~mejn/dcbm/

#include "mex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <limits>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
#include <vector>
#include "biSBM.h"

using namespace std;

/********** biSBM **********/
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] )
{
    srandom(time(NULL));
    /*
     * 0 edgelist
     * 1 types
     * 2 KA
     * 3 KB
     * 4 DegreeCorrect
     * 5 KLSteps
     */
    double *g;
    int KA,KB;
    double *types;
    double *edges;
    double *e;
    Types.clear();
    Comms.clear();
    
    /**********  0 edgelist  **********/
    size_t mrows;
    mrows = mxGetM(prhs[0]);
    e = mxGetPr(prhs[0]);
    GetTheNetworkEdges(e,mrows);
    
    
    /**********  1 types  **********/
    types = mxGetPr(prhs[1]);
    Nodes = mxGetM(prhs[1]); // GLOBAL - Number of nodes
    int maxTypes = 0;
    for (unsigned int i=0; i<Nodes; ++i)
    {
        Types.push_back(types[i]-1); // GLOBAL - Vertex types
        maxTypes = max(maxTypes,Types[i]+1);
    }
    vector<int> tally (maxTypes+1,0);
    for (unsigned int i=0; i<Types.size(); ++i)
    {
        tally[Types[i]]++;
    }
    /**********  2 KA  **********/
    KA = (int) *mxGetPr(prhs[2]);
    /**********  3 KB  **********/
    KB = (int) *mxGetPr(prhs[3]);
    /**********  4 isDegreeCorrect  **********/
    isDegreeCorrect = (bool) *mxGetPr(prhs[4]);
    /**********  5 KLPerNetwork  **********/
    KLPerNetwork = (int) *mxGetPr(prhs[5]);
    
    /**********  Output  **********/
    plhs[0] = mxCreateDoubleMatrix((mwSize)Nodes, (mwSize)1, mxREAL);
    g = mxGetPr(plhs[0]);
    
    int counter = 0;
    vector<int> commlist;
    for (unsigned int q=0; q<KA; ++q)
    {
        commlist.push_back(counter);
        counter++;
    }
    Comms.push_back(commlist);
    commlist.clear();
    for (unsigned int q=0; q<KB; ++q)
    {
        commlist.push_back(counter);
        counter++;
    }
    Comms.push_back(commlist);
    commlist.clear();
    MaxComms = counter;
    
    mexPrintf("\nCalling biSBM with the following parameters.\n");
    mexPrintf("KA:\t%i\n",KA);
    mexPrintf("KB:\t%i\n",KB);
    mexPrintf("NA:\t%i\n",tally[0]);
    mexPrintf("NB:\t%i\n",tally[1]);
    mexPrintf("Type A Communities: ");
    unsigned int i=0;
    for (unsigned int j=0; j<Comms[i].size(); ++j) {
        mexPrintf("%i,",Comms[i][j]+1);
    }
    mexPrintf("\n");
    mexPrintf("Type B Communities: ");
    i=1;
    for (unsigned int j=0; j<Comms[i].size(); ++j) {
        mexPrintf("%i,",Comms[i][j]+1);
    }
    mexPrintf("\n");
    mexPrintf("DegreeCorrect:\t%i\n",isDegreeCorrect);
    mexPrintf("Edges:\t%i\n",mrows);
    mexEvalString("drawnow;");
    
    /**********  Call the biSBM subroutine.  **********/
    biSBM();
    
    /**********  Put the output into g.  **********/
    for (unsigned int i=0; i<Nodes; ++i)
    {
        g[i] = BestState[i];
    }
}

void GetTheNetworkEdges(double *e, mwSize mrows)
{
    unsigned int counter = 0;
    mwSize ii;
    for (ii=0; ii<mrows; ++ii)
    {
        EdgeList[ii][0] = (long int)e[ii]-1;
        EdgeList[ii][1] = (long int)e[mrows+ii]-1;
        counter = counter+1;
        Nodes = max(Nodes,(long int)e[ii]);
        Nodes = max(Nodes,(long int)e[mrows+ii]);
    }
    TwiceEdges = 2*counter; // GLOBAL
    
    if(TrueCommsAvailable == 1)
    {
        // DBL
        //        InputFile2.open(trueCommsName.c_str());
        //        if (!InputFile2)
        //        {
        //            cout << "Error in opening file";
        //            cin.get();
        //            return;
        //        }
        //
        //        for(i=0; i < Nodes; i++)
        //            TrueState[i] = -1;
        //
        //        while(std::getline(InputFile2, lineread)) // Read line by line
        //        {
        //            buffer = new char [lineread.size()+1];
        //            strcpy(buffer, lineread.c_str());
        //            //  cout << buffer << endl;
        //            sscanf(buffer, "%ld", &entry1);
        //            //  sscanf(buffer, "n%d,%*[^,],%d", &ignore, &entry1); //%*s
        //            // entry1 = entry1+1;
        //            //sscanf(buffer, "%d %d", &entry1, &entry2);
        //            // TrueState[entry1-1] = entry2;
        //            TrueState[counter2] = entry1;
        //
        //            counter2 = counter2+1;
        //            delete[] buffer;
        //        }
        //        InputFile2.close();
        //
        //        for(i=0; i < Nodes; i++)
        //        {
        //            if((TrueState[i] == -1) || (TrueState[i] >= MaxComms))
        //            {
        //                cout << "STOP A VERTEX WAS NOT LABELED OR WAS LABELED INCORRECTLY." << TrueState[i] << " "  << i << endl;
        //                cin.get();
        //            }
        //        }
    }
    // We start the degree values and LastEmpty all at zero
    for(unsigned int i=0; i<Nodes; ++i)
    {
        Degree[i] = 0;
        LastEmpty[i] = 0;
    }
    // First we count the degrees by scanning through the list once
    for(unsigned int i=0; i<counter; ++i)
    {
        Degree[EdgeList[i][0]]++;
        Degree[EdgeList[i][1]]++;
    }
    // Now we make space in the adjacency lists
    for(unsigned int i=0; i<Nodes; ++i)
    {
        AdjList[i] = new long int [Degree[i]];
    }
    // Now we read the edges into the adjacency lists utilizing lastempty to put them into
    // the proper spots
    for(unsigned int i=0; i<counter; ++i)
    {
        AdjList[EdgeList[i][0]][LastEmpty[EdgeList[i][0]]] = EdgeList[i][1];
        LastEmpty[EdgeList[i][0]]++;
        
        AdjList[EdgeList[i][1]][LastEmpty[EdgeList[i][1]]] = EdgeList[i][0];
        LastEmpty[EdgeList[i][1]]++;
    }
    return;
}
