function [g] = biSBM(network,nodeTypes,Ka,Kb,degreeCorrect,nKLiterations)
% g = biSBM(network,nodeTypes,Ka,Kb,degreeCorrect,nKLiterations)
%
% INPUTS:
%  network     - NxN adjacency matrix *or* Ex2 edge list
%  nodeTypes   - Nx1 or 1xN vector of node types. [0,1] or [1,2].
%  Ka,Kb       - Number of communities for types 0,1 respectively (or 1,2).
%  degreeCorrect - boolean: 0 uncorrected biSBM, 1 degree-corrected biSBM.
%  nKLiterations - positive integer number of Kernighan-Lin iterations. 
%
%  OUTPUTS:
%  g - Nx1 maximum likelihood partition vector
%
%
% Daniel Larremore
% Harvard School of Public Health
% April 10, 2014
% v1.1
%
% http://danlarremore.com/biSBM
% daniel.larremore@gmail.com
%
% biSBM - a method for community detection in bipartite networks, based on the publication:
% Efficiently inferring community structure in bipartite networks
% Daniel B. Larremore, Aaron Clauset, Abigail Z. Jacobs.
% http://arxiv.org/abs/1403.2933
% Please do not distribute without contacting the author above at daniel.larremore@gmail.com
% If a bug is located within the code, please contact the author, to correct the official version!
%
% This code is based on code written by Brian Karrer for the stochastic block model, http://arxiv.org/abs/1104.3590
% You can download that code at http://www-personal.umich.edu/~mejn/dcbm/


%% Input cleaning and error checking

% Are Ka and Kb real, nonzero, integer?
if sum(size(Ka,1)+size(Ka,2)) > 2
    error('Ka must be a positive integer');
end
if ~isreal(Ka)
    error('Ka must be real.');
end
if Ka <= 0
    error('Ka must be a positive integer.');
end
if mod(Ka,1)>0
    error('Ka must be a positive integer.');
end
if sum(size(Kb,1)+size(Kb,2)) > 2
    error('Kb must be a positive integer');
end
if ~isreal(Kb)
    error('Kb must be real.');
end
if Kb <= 0
    error('Kb must be a positive integer.');
end
if mod(Kb,1)>0
    error('Kb must be a positive integer.');
end

% Check types
if size(nodeTypes,2)~=1
    nodeTypes = nodeTypes';
end
if size(nodeTypes,2)~=1
    error('nodeTypes must be a row or column vector');
end
if length(unique(nodeTypes))<2
    error('nodeTypes vector specifies less than two node types.');
elseif length(unique(nodeTypes))>2
    error('nodeTypes vector specifies more than two node types.');
end
% If nodeTypes are given as [0,1], bump them to [1,2];
if min(nodeTypes)==0 && max(nodeTypes)==1
    nodeTypes = nodeTypes+1;
end

N_types = length(nodeTypes);

% Do we have a matrix or an edgelist?
if size(network,1)~=2 && size(network,2)~=2
    % we have an adjacency matrix
    if sum(sum(network~=network')) == 0 
        % A is symmetric
        [r,c,~] = find(triu(network));
    else
        [r,c,~] = find(network);
    end
    % turn into edgelist form for processing below
    network = [r,c];
end

% Now we have an edgelist
if (sum(sum(~isreal(network))) + sum(sum(mod(network,1))) + sum(sum(network<0))) > 0
    error('network must be real, positive, integer-valued');
end
minIndex = min(min(network));
if minIndex==0
    warning('network begins indexing at 0.')
    network = network+1;
end
N_edges = max(max(network));
if N_edges ~= N_types
    warning(['Dimensions of nodeTypes and network do not match.\n',...
        'This may occur is network consists of multiple components.']);
end

% Check for degreeCorrect
if ~(degreeCorrect==0 || degreeCorrect==1)
    error('degreeCorrect must be 0 or 1');
end

% Check nKLiterations
if ~isreal(nKLiterations)
    error('nKLiterations must be real.');
end
if mod(nKLiterations,1)>0
    error('nKLiterations must be integer.');
end
if nKLiterations<=0
    error('nKLiterations must be greater than zero.');
end


%% Call biSBMcore mex file
g = biSBMcore(network,nodeTypes,Ka,Kb,degreeCorrect,nKLiterations)+1;

%% Return output
return;