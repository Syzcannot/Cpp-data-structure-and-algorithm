type eType=record
     a,b,flow,cap,cost,next:longint;
     end;
const inf=1000000000; maxn=1000+10; maxm=50000+100;
var n,m,s,t,tot,cnt:longint;
    d,q,r,p,first:array[0..maxn] of longint;
    e:array[0..maxm] of eType;
    ex:array[0..maxn] of boolean;
procedure insert(u,v,cap,cost:longint);
 begin
   inc(cnt);
   e[cnt].a:=u; e[cnt].b:=v;
   e[cnt].flow:=0; e[cnt].cap:=cap; e[cnt].cost:=cost;
   e[cnt].next:=first[u]; first[u]:=cnt;
   inc(cnt);
   e[cnt].a:=v; e[cnt].b:=u;
   e[cnt].flow:=0; e[cnt].cap:=0; e[cnt].cost:=-cost;
   e[cnt].next:=first[v]; first[v]:=cnt;
 end;
procedure init;
 var i,last,now,l,r,cost:longint;
 begin
   readln(n,m);
   s:=n+2; t:=n+3; tot:=n+3; cnt:=1;
   last:=0;
   for i:=1 to n do
    begin
      read(now);
      if now>last then insert(s,i,now-last,0) else insert(i,t,last-now,0);
      insert(i+1,i,inf,0);
      last:=now;
    end;
   insert(n+1,t,last,0);

   for i:=1 to m do
    begin
      readln(l,r,cost);
      insert(l,r+1,inf,cost);
    end;
 end;
procedure solve;
 var cost,flow,i,k,cl,op,u,v,now:longint;
 begin
   cost:=0; flow:=0;
   while true do
    begin
      for i:=1 to tot do begin d[i]:=inf; ex[i]:=false; p[i]:=0; r[i]:=inf; end;
      d[s]:=0; cl:=0; op:=1; q[1]:=s;
      repeat
        cl:=(cl+1) mod (tot+1);
        u:=q[cl]; ex[u]:=false;

        now:=first[u];
        while now<>0 do
         begin
           v:=e[now].b;
           if (e[now].flow<e[now].cap)and(d[u]+e[now].cost<d[v]) then
            begin
              d[v]:=d[u]+e[now].cost; p[v]:=now;
              if e[now].cap-e[now].flow<r[u] then r[v]:=e[now].cap-e[now].flow else r[v]:=r[u];
              if not ex[v] then
               begin
                 op:=(op+1) mod (n+1);
                 q[op]:=v; ex[v]:=true;
               end;
            end;
           now:=e[now].next;
         end;
      until cl=op;

      if d[t]=inf then break;
      k:=r[t]; u:=t;
      while p[u]<>0 do
       begin
         now:=p[u];
         e[now].flow:=e[now].flow+k;
         e[now xor 1].flow:=e[now xor 1].flow-k;
         cost:=cost+k*e[now].cost;
         u:=e[now].a;
       end;
      flow:=flow+k;
    end;
   writeln(cost);
 end;
begin
  init;
  solve;
end.