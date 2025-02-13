# include <math.h>
# include <stdlib.h>
#include "encoding.h"
/*
RSA System
1. Choose nuymber p and q, n=pq
2. Msg are integers M where 0<= M <=n
3. Encryption key is the pair of int's (e,n) where 1<e<ɸ(n)
   ɸ(n)= (p-1)(q-1) and GCD (e, ɸ(n))=1
4. ed =1(mod ɸ(n)) solve for ɸ where 1<d<ɸ(n)
   (d,n) is the decryption key
*/
long p,q,n,phi,M;
int e,d;
int c,l;
bool ierror;
int encoding::encrypt (int Message)
{
	NO_BITS=32;
	//c=congruence(1,n,Message^e,&ierror);
	c=congruence(1,2773,715^17,&ierror);
	double q=0,f=1;

	while(1)
		{
			//read from ip file into 'data'
			
			data =(double)Message;

			//calculate ((data)^e mod n) .i.e the remainder
			q=0;f=1;
			for(long i=;i>=0;i--)
			{
				q=2*q;
				f=fmod(f*f,n);
		
				if(bits[NO_BITS-i] == '1')
				{
					q=q+1;
					f=fmod(data*f,n);
				}//end of IF		
			}//end of for loop 

			//write to op file from 'd'
			fwrite(&d,sizeof_d,1,outFP);
			
		}//end of while loop 







	return c;
}
int encoding::decrypt (int Message)
{
	l=congruence(1,n,Message^d,&ierror);
	return l;
}
int encoding::generateRequiredValues()
{
	p=11;
	q=13;
	//p=579;
	//q=833;//q=2+rand()%10;

	n=p*q;

	phi = (p-1)*(q-1);
	e=phi-1;
	do
	{
		e--;
	}while (GCD(e,phi)!=1);
	
	d= congruence (e,phi,1, &ierror);
	return e;
}
int encoding::GCD(int a, int b)
{
    while( 1 )
    {
        a = a % b;
		if( a == 0 )
			return b;
		b = b % a;
        if( b == 0 )
			return a;
    }
}

// NOT WRITTEN BY MARK< STOLE IT FROM OTHER GUY< I THINK HIS NAME IS BELOW SOMEWHERE---------------------------------------------
int encoding::congruence ( int a, int b, int c, bool *error )

//****************************************************************************80
//
//  Purpose:
//
//    CONGRUENCE solves a congruence of the form A * X = C ( mod B ).
//
//  Discussion:
//
//    A, B and C are given integers.  The equation is solvable if and only
//    if the greatest common divisor of A and B also divides C.
//
//  Modified:
//
//    15 November 2004
//
//  Author:
//
//    John Burkardt
//
//  Reference:
//
//    Eric Weisstein, editor,
//    CRC Concise Encylopedia of Mathematics,
//    CRC Press, 1998, page 446.
//
//  Parameters:
//
//    Input, int A, B, C, the coefficients of the Diophantine equation.
//
//    Output, bool *ERROR, error flag, is TRUE if an error occurred..
//
//    Output, int CONGRUENCE, the solution of the Diophantine equation.
//    X will be between 0 and B-1.
//
{
# define N_MAX 100

  int a_copy;
  int a_mag;
  int a_sign;
  int b_copy;
  int b_mag;
  int b_sign;
  int c_copy;
  int g;
  int k;
  int n;
  float norm_new;
  float norm_old;
  int q[N_MAX];
  bool swap;
  int temp;
  int x;
  int xnew;
  int y;
  int ynew;
//
//  Defaults for output parameters.
//
  *error = false;
  x = 0;
  y = 0;
//
//  Special cases.
//
  if ( a == 0 && b == 0 && c == 0 )
  {
    return 0;
  }
  else if ( a == 0 && b == 0 && c != 0 )
  {
    *error = true;
    return (-1);
  }
  else if ( a == 0 && b != 0 && c == 0 )
  {
    return 0;
  }
  else if ( a == 0 && b != 0 && c != 0 )
  {
    if ( ( c % b ) != 0 )
    {
      *error = true;
      return (-1);
    }
    return 0;
  }
  else if ( a != 0 && b == 0 && c == 0 )
  {
    return 0;
  }
  else if ( a != 0 && b == 0 && c != 0 )
  {
    x = c / a;
    if ( ( c % a ) != 0 )
    {
      *error = true;
      return (-1);
    }
    return x;
  }
  else if ( a != 0 && b != 0 && c == 0 )
  {
    g = i4_gcd ( a, b );
    x = b / g;
    return x;
  }
//
//  Now handle the "general" case: A, B and C are nonzero.
//
//  Step 1: Compute the GCD of A and B, which must also divide C.
//
  g = i4_gcd ( a, b );

  if ( ( c % g ) != 0 )
  {
    *error = true;
    return (-1);
  }

  a_copy = a / g;
  b_copy = b / g;
  c_copy = c / g;
//
//  Step 2: Split A and B into sign and magnitude.
//
  a_mag = abs ( a_copy );
  a_sign = i4_sign ( a_copy );
  b_mag = abs ( b_copy );
  b_sign = i4_sign ( b_copy );
//
//  Another special case, A_MAG = 1 or B_MAG = 1.
//
  if ( a_mag == 1 )
  {
    x = a_sign * c_copy;
    return x;
  }
  else if ( b_mag == 1 )
  {
    return 0;
  }
//
//  Step 3: Produce the Euclidean remainder sequence.
//
  if ( b_mag <= a_mag )
  {
    swap = false;
    q[0] = a_mag;
    q[1] = b_mag;
  }
  else
  {
    swap = true;
    q[0] = b_mag;
    q[1] = a_mag;
  }

  n = 3;

  for ( ; ; )
  {
    q[n-1] = ( q[n-3] % q[n-2] );

    if ( q[n-1] == 1 )
    {
      break;
    }

    n = n + 1;

    if ( N_MAX < n )
    {
      *error = true;
//      cout << "\n";
//      cout << "CONGRUENCE - Fatal error!\n";
//      cout << "  Exceeded number of iterations.\n";
      exit ( 1 );
    }

  }
//
//  Step 4: Now go backwards to solve X * A_MAG + Y * B_MAG = 1.
//
  y = 0;
  for ( k = n; 2 <= k; k-- )
  {
    x = y;
    y = ( 1 - x * q[k-2] ) / q[k-1];
  }
//
//  Step 5: Undo the swapping.
//
  if ( swap )
  {
    i4_swap ( &x, &y );
  }
//
//  Step 6: Now apply signs to X and Y so that X * A + Y * B = 1.
//
  x = x * a_sign;
//
//  Step 7: Multiply by C, so that X * A + Y * B = C.
//
  x = x * c_copy;
//
//  Step 8: Now force 0 <= X < B.
//
  x = x % b;
//
//  Step 9: Force positivity.
//
  if ( x < 0 )
  {
    x = x + b;
  }

  return x;
# undef N_MAX
}

int encoding::i4_gcd ( int i, int j )

//****************************************************************************80
//
//  Purpose:
//
//    I4_GCD finds the greatest common divisor of I and J.
//
//  Discussion:
//
//    Only the absolute values of I and J are considered, so that the 
//    result is always nonnegative.
//
//    If I or J is 0, I4_GCD is returned as max ( 1, abs ( I ), abs ( J ) ).
//
//    If I and J have no common factor, I4_GCD is returned as 1.
//
//    Otherwise, using the Euclidean algorithm, I4_GCD is the
//    largest common factor of I and J.
//
//  Modified:
//
//    07 May 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int I, J, two numbers whose greatest common divisor
//    is desired.
//
//    Output, int I4_GCD, the greatest common divisor of I and J.
//
{
  int ip;
  int iq;
  int ir;
//
//  Return immediately if either I or J is zero.
//
  if ( i == 0 )
  {
    return i4_max ( 1, abs ( j ) );
  }
  else if ( j == 0 )
  {
    return i4_max ( 1, abs ( i ) );
  }
//
//  Set IP to the larger of I and J, IQ to the smaller.
//  This way, we can alter IP and IQ as we go.
//
  ip = i4_max ( abs ( i ), abs ( j ) );
  iq = i4_min ( abs ( i ), abs ( j ) );
//
//  Carry out the Euclidean algorithm.
//
  for ( ; ; )
  {
    ir = ip % iq;

    if ( ir == 0 )
    {
      break;
    }

    ip = iq;
    iq = ir;
  }

  return iq;
}
void encoding::i4_swap ( int *i, int *j )

//****************************************************************************80
//
//  Purpose:
//
//    I4_SWAP switches two I4's.
//
//  Modified:
//
//    07 January 2002
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input/output, int *I, *J.  On output, the values of I and
//    J have been interchanged.
//
{
  int k;

  k = *i;
  *i = *j;
  *j = k;
 
  return;
}
int encoding::i4_sign ( int i )

//****************************************************************************80
//
//  Purpose:
//
//    I4_SIGN returns the sign of an I4.
//
//  Discussion:
//
//    The sign of 0 and all positive integers is taken to be +1.
//    The sign of all negative integers is -1.
//
//  Modified:
//
//    06 May 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int I, the integer whose sign is desired.
//
//    Output, int I4_SIGN, the sign of I.
{
  if ( i < 0 ) 
  {
    return (-1);
  }
  else
  {
    return 1;
  }

}
int encoding::i4_max ( int i1, int i2 )

//****************************************************************************80
//
//  Purpose:
//
//    I4_MAX returns the maximum of two I4's.
//
//  Modified:
//
//    05 May 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int I1, I2, two integers to be compared.
//
//    Output, int I4_MAX, the larger of I1 and I2.
//
{
  if ( i2 < i1 ) 
  {
    return i1;
  }
  else 
  {
    return i2;
  }

}
int encoding::i4_min ( int i1, int i2 )

//****************************************************************************80
//
//  Purpose:
//
//    I4_MIN returns the smaller of two I4's.
//
//  Modified:
//
//    05 May 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int I1, I2, two integers to be compared.
//
//    Output, int I4_MIN, the smaller of I1 and I2.
//
{
  if ( i1 < i2 ) 
  {
    return i1;
  }
  else 
  {
    return i2;
  }

}
// -------------------------------------------------------------------------