var k,ans:int64;
    s:array[0..2000000] of char;
    r,w:array[0..2000000] of longint;
    be,n,i,p,mx,now:longint;
function qm(k:longint):int64;
var temp:int64;
 begin
  if k=1 then exit(be);
  temp:=qm(k shr 1);
  qm:=temp*temp mod 19930726;
  if k and 1=1 then qm:=(qm*be) mod 19930726;
 end;
function min(a,b:longint):longint;
begin
 if a<b then exit(a) else exit(b);
end;
begin
  readln(n,k);
  for i:=1 to n do read(s[i]);
  p:=0; mx:=0;
  for i:=1 to n do
   begin
    if mx>i then r[i]:=min(r[(p shl 1)-i],mx-i)
      else r[i]:=1;

    while (i+r[i]<=n)and(i-r[i]>0)and(s[i+r[i]]=s[i-r[i]]) do
     inc(r[i]);

    if i+r[i]>mx then
     begin
      p:=i;
      mx:=i+r[i];
     end;

    now:=(r[i] shl 1)-1;
    inc(w[1]); dec(w[now+1]);
   end;
  ans:=1;
  for i:=1 to n do w[i]:=w[i]+w[i-1];
  for i:=n downto 1 do
   if (i and 1=1)and(w[i]>0) then
    if k>=w[i] then
     begin
      be:=i;
      ans:=(ans*qm(w[i]))mod 19930726;
      k:=k-w[i];
     end
    else
     begin
      be:=i;
      ans:=(ans*qm(k)) mod 19930726;
      k:=0;
      break;
     end;

  if k>n then writeln(-1) else writeln(ans);
end.

