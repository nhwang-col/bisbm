% Test the biSBM code

% TEST 1 %
edges = load('southernWomen.edgelist');
N = max(max(edges));
r = edges(:,1);
c = edges(:,2);
A = sparse(r,c,ones(size(edges,1),1),N,N);
types = load('southernWomen.types');
g = biSBM(A,types,2,3,1,3);

% TEST 2 %
edges = load('test.edgelist');
N = max(max(edges));
r = edges(:,1);
c = edges(:,2);
A = sparse(r,c,ones(size(edges,1),1),N,N);
types = load('test.types');
g = biSBM(A,types,2,3,1,3);

% SHOULD PRODUCE OUTPUT:
% % 
% % Calling biSBM with the following parameters.
% % KA:	2
% % KB:	3
% % NA:	18
% % NB:	14
% % Type A Communities: 1,2,
% % Type B Communities: 3,4,5,
% % DegreeCorrect:	1
% % Edges:	89
% % >1,0.000000,-367.657617
% % >2,0.000000,-367.657617
% % >3,0.000000,-367.657617
% % Final Score: -367.658
% % 
% % Calling biSBM with the following parameters.
% % KA:	2
% % KB:	3
% % NA:	700
% % NB:	300
% % Type A Communities: 1,2,
% % Type B Communities: 3,4,5,
% % DegreeCorrect:	1
% % Edges:	7696
% % >1,0.000000,-65525.804037
% % >2,1.000000,-65525.804037
% % >3,1.000000,-65525.804037
% % Final Score: -65525.8
