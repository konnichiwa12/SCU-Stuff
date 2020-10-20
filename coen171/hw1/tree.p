

program tree(input, output);
	type treeA = ^node;

	node = record
       		info : integer;
       		left : TreeA;
       		right: TreeA;
	end;
function insert(var root : treeA; value: integer) : treeA;
       	begin
               	if root = nil then 
               	begin
                       	new(root);
                       	root^.left := nil;
                       	root^.right := nil;
                       	root^.info := value
               	end
               	else if root^.info < value then
                       	root^.right := insert(root^.right, value)
               	else if root^.info > value then
                       	root^.left := insert(root^.left, value);
               	insert := root
       	end;
function member(var root : treeA; value : integer) : integer;
	begin
		if root = nil then
			member := 0
		else if root^.info = value then
			member := 1
		else if root^.info < value then
			member := member(root^.right, value)
		else
			member := member(root^.left, value);
	end;
                
var t : treeA;
var x : integer;

begin 
	t := nil;
	readln(x);

	while x <> -1 do 
	begin
		t := insert(t, x);
		readln(x)
	end;

	readln(x);
	while x <> -1 do
	begin
		if member(t, x) = 1 then
			writeln('True')
		else
			writeln('False');
		readln(x);
		
	end;
end.
