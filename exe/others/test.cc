#include <iostream>
#include <vector>

typedef unsigned long long int ll;

unsigned long long int ack(unsigned long long int m,unsigned long long int n)
{
  if(m == 0)
    return (n + 1);
  else if(n == 0)
    return ack(m - 1,1);
  else
    {
      return ack(m - 1,ack(m, n - 1));
    }
}

ll arrow(ll m,ll n,int arrownum)
{
  if(arrownum == 1)
    {
      ll result = 1;
      for(ll i = 0;i < n;i++)
	{
	  result *= m;
	}
      return result;
    }
  else
    {
      ll result = m;
      for(ll j = 1;j < n;j++)
	{
	  result = arrow(m,result,arrownum - 1);
	}
      return result;
    }
  return 0;
}

	    
int main(int argc,char** argv)
{
  try
    {
      if(argc != 4)
	{
	  std::cout << "invalid input value number!" << std::endl;
	  throw "int main()";
	}
      ll m = (ll)atoi(argv[1]);
      ll n = (ll)atoi(argv[2]);
      int arrownum = atoi(argv[3]);
      std::cout << "arrow(" << m << "," << n << "," << arrownum << ") = " << arrow(m,n,arrownum) << std::endl;
    }
  catch(const char* e)
    {
      std::cout << "error in " << e << std::endl;
    }
  return 0;
}

  
