{$inline on}
const D=1; maxn=1000000;
type Dtype=array[0..D] of longint;
     kdTree=record
       min,max,d:Dtype;
       l,r:longint;
     end;
var  t:array[0..maxn] of kdTree;
     p:Dtype;
     n,m,size,root,ans,now:longint;
     time:real;
function cmp(a,b:Dtype):boolean;inline;
 begin
   if (a[now]<b[now])or((a[now]=b[now])and(a[now xor 1]<b[now xor 1])) then exit(true) else exit(false);
 end;
procedure nth(l,r,k:longint);
 const limit=20;
 var i,j:longint; mid,tmp:Dtype;
 begin
   if l+limit>r then
    begin
      for i:=l to r do
       for j:=i+1 to r do
        if cmp(t[j].d,t[i].d) then begin tmp:=t[i].d; t[i].d:=t[j].d; t[j].d:=tmp; end;
      exit;
    end;
   i:=l; j:=r; mid:=t[(l+r)>>1].d;
   repeat
     while cmp(t[i].d,mid) do inc(i);
     while cmp(mid,t[j].d) do dec(j);
     if not(i>j) then
      begin
        tmp:=t[i].d; t[i].d:=t[j].d; t[j].d:=tmp;
        inc(i); dec(j);
      end;
   until i>j;
   if (l<j)and(k<=j) then nth(l,j,k);
   if (i<r)and(k>=i) then nth(i,r,k);
 end;
procedure update(k:longint);
 var i,x:longint;
 begin
   for i:=0 to D do
    begin
      if t[k].l<>0 then
       begin
         x:=t[k].l;
         if t[x].min[i]<t[k].min[i] then t[k].min[i]:=t[x].min[i];
         if t[x].max[i]>t[k].max[i] then t[k].max[i]:=t[x].max[i];
       end;
      if t[k].r<>0 then
       begin
         x:=t[k].r;
         if t[x].min[i]<t[k].min[i] then t[k].min[i]:=t[x].min[i];
         if t[x].max[i]>t[k].max[i] then t[k].max[i]:=t[x].max[i];
       end;
    end;
 end;
function build(l,r,dd:longint):longint;
 var mid,i:longint;
 begin
   now:=dd; mid:=(l+r)>>1;
   nth(l,r,mid);
   for i:=0 to D do begin t[mid].min[i]:=t[mid].d[i]; t[mid].max[i]:=t[mid].d[i]; end;
   if l<mid then t[mid].l:=build(l,mid-1,dd xor 1);
   if r>mid then t[mid].r:=build(mid+1,r,dd xor 1);
   update(mid);
   exit(mid);
 end;
procedure init;
 var i:longint;
 begin
   assign(input,'2648.in'); reset(input);
   assign(output,'2648.out'); rewrite(output);
   readln(n,m); size:=n;
   for i:=1 to n do readln(t[i].d[0],t[i].d[1]);
   root:=build(1,n,0);
 end;
procedure insert(k,now:longint);
 var i:longint;
 begin
   if p[now]>=t[k].d[now] then
    begin
      if t[k].r<>0 then insert(t[k].r,now xor 1)
       else
        begin
          inc(size); t[k].r:=size;
          for i:=0 to D do begin t[size].d[i]:=p[i]; t[size].min[i]:=t[size].d[i]; t[size].max[i]:=t[size].d[i]; end;
        end;
    end
   else
    begin
       if t[k].l<>0 then insert(t[k].l,now xor 1)
       else
        begin
          inc(size); t[k].l:=size;
          for i:=0 to D do begin t[size].d[i]:=p[i]; t[size].min[i]:=t[size].d[i]; t[size].max[i]:=t[size].d[i]; end;
        end;
    end;
   update(k);
 end;
function get(k:longint):longint;inline;
 var res:longint;
 begin
   res:=0;
   if p[0]<t[k].min[0] then res:=res+t[k].min[0]-p[0];
   if p[0]>t[k].max[0] then res:=res+p[0]-t[k].max[0];
   if p[1]<t[k].min[1] then res:=res+t[k].min[1]-p[1];
   if p[1]>t[k].max[1] then res:=res+p[1]-t[k].max[1];
   exit(res);
 end;
procedure query(k:longint);
 var dis,dl,dr:longint;
 begin
   dis:=abs(t[k].d[0]-p[0])+abs(t[k].d[1]-p[1]);
   if dis<ans then ans:=dis;
   dl:=maxlongint; dr:=maxlongint;
   if t[k].l<>0 then dl:=get(t[k].l);
   if t[k].r<>0 then dr:=get(t[k].r);
   if dl<dr then
    begin
      if dl<ans then query(t[k].l);
      if dr<ans then query(t[k].r);
    end
   else
    begin
      if dr<ans then query(t[k].r);
      if dl<ans then query(t[k].l);
    end;
 end;
procedure solve;
 var i,opt:longint;
 begin
   for i:=1 to m do
    begin
      readln(opt,p[0],p[1]);
      if opt=1 then insert(root,0)
        else begin ans:=maxlongint; query(root); writeln(ans); end;
    end;
 end;
begin
  init;
  solve;
end.















