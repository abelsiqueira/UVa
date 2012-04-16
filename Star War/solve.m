function d = solve (T);

T1 = T(1:4,:)';
T2 = T(5:8,:)';

A = [T1(:,2:4)-T1(:,1)*ones(1,3), T2(:,1)*ones(1,3) - T2(:,2:4)];
b = T1(:,1) - T2(:,2);

Q = A'*A;
g = A'*b;

A = [ones(1,3),zeros(1,3);zeros(1,3),ones(1,3)];
b = [1;1];
l = zeros(6,1);

options = optimset('quadprog');
options = optimset(options,'LargeScale','off');

[x,f] = quadprog(Q,g,A,b,[],[],l,[],l,options);
