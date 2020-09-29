var  l,r,s,fa:array[0..200000] of longint;
     re:array[0..200000] of boolean;
     n,m,i,k,ll,rr,x,y,root:longint;
function build(ll,rr:longint):longint;
 var mid,k,x:longint;
  begin
    mid:=(ll+rr)>>1;
    x:=mid;
    if ll<mid then
     begin
       k:=build(ll,mid-1);
       l[x]:=k; fa[k]:=x;
     end;
    if mid<rr then
     begin
       k:=build(mid+1,rr);
       r[x]:=k; fa[k]:=x;
     end;
    s[x]:=s[l[x]]+s[r[x]]+1;
    exit(x);
  end;
procedure addtion(k:longint);
 begin
   l[n+2]:=n+1; s[n+2]:=n+2;
   fa[n+1]:=n+2; r[n+1]:=k; s[n+1]:=n+1;
   fa[k]:=n+1;
   root:=n+2;
 end;
procedure swap(var a,b:longint);
 var temp:longint;
  begin
    temp:=a; a:=b; b:=temp;
  end;
procedure normal(i:longint);
 begin
   if re[i] then
    begin
      re[i]:=false;
      swap(l[i],r[i]);
      if l[i]<>0 then re[l[i]]:=not re[l[i]];
      if r[i]<>0 then re[r[i]]:=not re[r[i]];
    end;
 end;
procedure lo(x:longint);
 var y:longint;
  begin
    y:=fa[x];
    r[y]:=l[x];
    if l[x]<>0 then fa[l[x]]:=y;
    if y=root then begin root:=x; fa[x]:=0; end
     else
      begin
        fa[x]:=fa[y];
        if y=l[fa[y]] then l[fa[y]]:=x else r[fa[y]]:=x;
      end;
    l[x]:=y; fa[y]:=x;
    s[x]:=s[y];
    s[y]:=s[l[y]]+s[r[y]]+1;
  end;
procedure ro(x:longint);
 var y:longint;
  begin
    y:=fa[x];
    l[y]:=r[x];
    if r[x]<>0 then fa[r[x]]:=y;
    if y=root then begin root:=x; fa[x]:=0; end
     else
      begin
        fa[x]:=fa[y];
        if y=l[fa[y]] then l[fa[y]]:=x else r[fa[y]]:=x;
      end;
    r[x]:=y; fa[y]:=x;
    s[x]:=s[y];
    s[y]:=s[l[y]]+s[r[y]]+1;
  end;
procedure splay(k:longint);
 var i,father:longint;
  begin
    i:=k;
    while fa[i]<>0 do
     begin
       father:=fa[i];
       if fa[father]=0 then
          if i=l[father] then ro(i) else lo(i)
       else
         if father=l[fa[father]] then
           if i=l[father] then begin ro(father); ro(i); end else begin lo(i); ro(i); end
         else
           if i=r[father] then begin lo(father); lo(i); end else begin ro(i); lo(i); end
     end;
  end;
function get(k:longint):longint;
 var  i:longint;
  begin
    i:=root; normal(i);
    while s[l[i]]+1<>k do
      if s[l[i]]+1<k then
       begin
         k:=k-s[l[i]]-1;
         i:=r[i]; normal(i);
       end
      else
       begin
         i:=l[i]; normal(i);
       end;
    splay(i); exit(i);
  end;
procedure print(k:longint);
 begin
   normal(k);
   if l[k]<>0 then print(l[k]);
   if (k<>n+1)and(k<>n+2) then write(k,' ');
   if r[k]<>0 then print(r[k]);
 end;
begin
  readln(n,m);
  k:=build(1,n);

  addtion(k);
  for i:=1 to n+2 do re[i]:=false;

  for i:=1 to m do
   begin
     readln(x,y);
     ll:=get(x); rr:=get(y+2);
     if fa[ll]<>rr then if ll=l[fa[ll]] then ro(ll) else lo(ll);

     re[r[ll]]:=not re[r[ll]];
   end;
  print(root);
end.