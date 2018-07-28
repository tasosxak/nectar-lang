#Returns the square root of integer x
func i_sqrt(n:int)->int
{
  var b:int = 0;

  while(n >= 0)
  {
		n = n - b;
		b = b + 1;
		n = n - b;
  }

  return b - 1;
}