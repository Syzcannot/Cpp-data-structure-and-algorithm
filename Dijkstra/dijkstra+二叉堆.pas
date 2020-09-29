type eType=record
     b,w,next:longint;
     end;
const inf=1000000000;
      maxn=10000+100; maxm=100000+100;
var e:array[0..maxm] of eType;
    dis,pos,heap,first:array[0..maxn] of longint;
    n,m,s,t,size,tot:longint;
procedure insert(u,v,w:longint);
 begin
   inc(tot);
   e[tot].b:=v; e[tot].w:=w;
   e[tot].next:=first[u]; first[u]:=tot;
 end;
procedure init;
 var i,u,v,w:longint;
 begin
   assign(input,'road.in'); reset(input);
   assign(output,'dijkstra.out'); rewrite(output);
   readln(n,m,s,t);
   for i:=1 to m do begin readln(u,v,w); insert(u,v,w); end;
 end;
procedure swap(a,b:longint);
 var tmp:longint;
 begin
   tmp:=heap[a]; heap[a]:=heap[b]; heap[b]:=tmp;
   pos[heap[a]]:=a; pos[heap[b]]:=b;
 end;
procedure delete_head;
 var i,j:longint;
 begin
   swap(1,size); dec(size);
   i:=1; j:=2;
   while j<=size do
    begin
      if (j+1<=size)and(dis[heap[j]]>dis[heap[j+1]]) then j:=j+1;
      if dis[heap[j]]<dis[heap[i]] then
       begin
         swap(i,j);
         i:=j; j:=i<<1;
       end
      else break;
    end;
 end;
procedure maintain(i:longint);
 var j:longint;
 begin
   j:=i>>1;
   while (i>1)and(dis[heap[i]]<dis[heap[j]]) do
    begin
      swap(i,j);
      i:=j; j:=i>>1;
    end;
 end;
procedure dijkstra;
 var i,u,v,now:longint;
 begin
   for i:=1 to n do dis[i]:=inf;
   dis[s]:=0; size:=1; heap[1]:=s; pos[s]:=1;
   for i:=1 to n do if i<>s then
    begin
      inc(size);
      heap[size]:=i;
      pos[i]:=size;
    end;

   for i:=1 to n do
    begin
      u:=heap[1];
      if (u=t)or(dis[u]=inf) then break;
      delete_head;

      now:=first[u];
      while now<>0 do
       begin
         v:=e[now].b;
         if dis[u]+e[now].w<dis[v] then begin dis[v]:=dis[u]+e[now].w; maintain(pos[v]); end;
         now:=e[now].next;
       end;
    end;
 end;
begin
  init;
  dijkstra;
  writeln(dis[t]);
end.








