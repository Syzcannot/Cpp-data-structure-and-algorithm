type nodetype=record
     l,r,fa,path_fa:longint;
     rev:boolean;
     end;
const maxn=20000;
var n,m,i,u,v,x,y:longint;
    node:array[0..maxn] of nodetype;
    ch:char;
procedure readelse(k:longint);
 var ch:char; i:longint;
  begin
    for i:=1 to k do read(ch);
  end;
procedure swap(var a,b:longint);
 var tmp:longint;
  begin
    tmp:=a; a:=b; b:=tmp;
  end;
procedure normal(k:longint);
  begin
    if node[k].rev then
     begin
       node[k].rev:=false;
       if node[k].l<>0 then node[node[k].l].rev:=not node[node[k].l].rev;
       if node[k].r<>0 then node[node[k].r].rev:=not node[node[k].r].rev;
       swap(node[k].l,node[k].r);
     end;
  end;
procedure lo(x:longint);
 var y:longint;
  begin
    y:=node[x].fa;
    node[x].path_fa:=node[y].path_fa;
    node[y].path_fa:=0;
    node[y].r:=node[x].l;
    if node[x].l<>0 then node[node[x].l].fa:=y;
    node[x].fa:=node[y].fa;
    if node[x].fa<>0 then
      if y=node[node[y].fa].l then node[node[y].fa].l:=x else node[node[y].fa].r:=x;
    node[x].l:=y; node[y].fa:=x;
  end;
procedure ro(x:longint);
 var y:longint;
  begin
    y:=node[x].fa;
    node[x].path_fa:=node[y].path_fa;
    node[y].path_fa:=0;
    node[y].l:=node[x].r;
    if node[x].r<>0 then node[node[x].r].fa:=y;
    node[x].fa:=node[y].fa;
    if node[x].fa<>0 then
      if y=node[node[y].fa].l then node[node[y].fa].l:=x else node[node[y].fa].r:=x;
    node[x].r:=y; node[y].fa:=x;
  end;
procedure splay(k:longint);
 var i,father:longint;
  begin
    i:=k;
    while node[i].fa<>0 do
     begin
       father:=node[i].fa;
       if node[father].fa=0 then
        begin
          normal(father); normal(i);
          if i=node[father].l then ro(i) else lo(i)
        end
       else
        begin
          normal(node[father].fa); normal(father); normal(i);
          if father=node[node[father].fa].l then
            if i=node[father].l then begin ro(father); ro(i); end else begin lo(i); ro(i); end
          else
            if i=node[father].r then begin lo(father); lo(i); end else begin ro(i); lo(i); end
        end;
     end;
  end;
{procedure splay(k:longint);
 var father:longint;
  begin
    while node[k].fa<>0 do
     begin
       father:=node[k].fa;
       normal(father);
       if node[father].l<>0 then normal(node[father].l);
       if node[father].r<>0 then normal(node[father].r);
       if k=node[father].l then ro(k) else lo(k);
     end;
  end; }
procedure access(u:longint);
 var v,x:longint;
  begin
    splay(u);
    normal(u);
    v:=node[u].r;
    if v<>0 then
     begin
       node[u].r:=0; node[v].fa:=0;
       node[v].path_fa:=u;
     end;
    v:=node[u].path_fa;
    while v<>0 do
     begin
       splay(v);
       normal(v);
       x:=node[v].r;
       if x<>0 then
        begin
          node[x].fa:=0;
          node[x].path_fa:=v;
        end;
       node[v].r:=u;
       node[u].fa:=v;
       node[u].path_fa:=0;
       u:=v;
       v:=node[u].path_fa;
     end;
  end;
procedure evert(u:longint);
  begin
    access(u);
    splay(u);
    node[u].rev:=not node[u].rev;
  end;
procedure link(u,v:longint);
  begin
    evert(u);
    normal(u);
    access(v);
    splay(v);
    node[u].l:=v;
    node[v].fa:=u;
  end;
procedure cut(u,v:longint);
  begin
    evert(v);
    access(u);
    splay(u);
    normal(u);
    node[node[u].l].fa:=0;
    node[u].l:=0;
  end;
function findroot(u:longint):longint;
  begin
    access(u);
    splay(u);
    normal(u);
    while node[u].l<>0 do
     begin
       u:=node[u].l;
       normal(u);
     end;
    splay(u);
    exit(u);
  end;
begin
  assign(input,'test.in'); reset(input);
  readln(n,m);
  for i:=1 to n do
   begin
     node[i].fa:=0; node[i].l:=0; node[i].r:=0; node[i].path_fa:=0;
     node[i].rev:=false;
   end;

  for i:=1 to m do
   begin
     read(ch);
     if ch='C' then
      begin
        readelse(6); readln(u,v);
        link(u,v);
        continue;
      end;
     if ch='D' then
      begin
        readelse(6); readln(u,v);
        cut(u,v);
        continue;
      end;
     if ch='Q' then
      begin
        readelse(4); readln(u,v);
        x:=findroot(u); y:=findroot(v);
        if x=y then writeln('Yes') else writeln('No');
      end;
   end;
end.
