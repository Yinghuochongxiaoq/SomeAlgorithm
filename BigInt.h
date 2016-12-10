#include <iostream>
#include <string>
using namespace std;
struct Bignum
{
	enum {MAXSIZE=300,JINZHI=10};//
	char Number[MAXSIZE];
	Bignum() //
	{
		int i;
		for(i=MAXSIZE-1;i>-1;--i) Number[i]=0;
	}
	Bignum(const char * a) //
	{
		int i;
		for(i=MAXSIZE-1;i>-1;--i) 
		{
			if(a[i]==0) Number[i]=0;
			else Number[i]=a[i]-'0';
		}//
		//
	}

	Bignum(string in)
	{
		int i;
		for(i=0;i<MAXSIZE;++i)
		{
			Number[i]=0;
		}
		for(i=0;i < in.size();++i)
		{
			Number[in.size()-i-1]=in[i]-'0';
		}
	}
	Bignum(int in) //
	{
		int i=0;
		while(in!=0)
		{
			Number[i++]=in%JINZHI;
			in/=JINZHI;
		}
		for(;i<MAXSIZE;++i)
		{
			Number[i]=0;
		}
	}
	Bignum operator +=(const Bignum& other) //
	{
		int i;
		for(i=0;i<MAXSIZE-1;++i)
		{
			Number[i]+=other.Number[i];
			Number[i+1]+=Number[i]/JINZHI;
			Number[i]%=JINZHI;
		}
		return *this;
	}
	Bignum operator -=(const Bignum& other)//
	{
		int i;
		for(i=0;i<MAXSIZE-1;++i)
		{
			if(Number[i]>=other.Number[i])
			{
				Number[i]-=other.Number[i];
			}
			else
			{
				--Number[i+1];
				Number[i]+=JINZHI-other.Number[i];
			}
		}
		return *this;
	}
	Bignum operator *=(const Bignum& other)//
	{
		int i,j;
		Bignum temp=*this;
		for(i=0;i<MAXSIZE;++i)
		{
			Number[i]=0;
		}
		for(i=0;i<MAXSIZE;++i)
		{
			for(j=0;j<other.Number[i];++j)
			{
				*this+=temp;
			}
			for(j=MAXSIZE-1;j>0;--j)
			{
				temp.Number[j]=temp.Number[j-1];
			}
			temp.Number[0]=0;
		}
		return *this;
	}
	Bignum operator /=(Bignum other) 
	{   //
		Bignum temp = *this;
		int i,j,k;
		for(i=0;i<MAXSIZE;++i)
		{
			if(other.Number[MAXSIZE-i-1]!=0) break;
		}
		Bignum shang,yushu,chushu=other;
		for(j=i;j>-1;--j)
		{
			for(k=MAXSIZE-1;k-j>=0;--k)
			{
				chushu.Number[k]=other.Number[k-j];
			}
			for(;k>-1;--k)
			{
				chushu.Number[k]=0;
			}
			while(!(temp<chushu))
			{
				++shang.Number[j];
				temp-=chushu;
			}
		}
		return shang;
	}
	Bignum operator %(Bignum other)//
	{   //
		Bignum tempa = *this;
		int i,j,k;
		for(i=0;i<MAXSIZE;++i)
		{
			if(other.Number[MAXSIZE-i-1]!=0) break;
		}
		Bignum shang,yushu,chushu=other;
		for(j=i;j>-1;--j)
		{
			for(k=MAXSIZE-1;k-j>=0;--k)
			{
				chushu.Number[k]=other.Number[k-j];
			}
			for(;k>-1;--k)
			{
				chushu.Number[k]=0;
			}
			while(!(tempa<chushu))
			{
				++shang.Number[j];
				tempa-=chushu;
			}
		}
		return tempa;
	}
	void display() //
	{
		int i;
		bool flag=false;
		for(i=MAXSIZE-2;i>-1;--i)
		{
			if(Number[i]!=0) flag=true;
			if(flag) cout << int(Number[i]);
		}
		if(!flag) cout<<0;
		cout<<endl; //
	}
	bool operator <(Bignum& other)
	{
		int i;
		for(i=MAXSIZE-1;i>-1;--i)
		{
			if(Number[i]<other.Number[i]) return 1;
			if(Number[i]>other.Number[i]) return 0;
		}
		return 0;
	}
	bool operator >=(Bignum& other)
	{
		return !(*this < other);
	}
	bool operator >(Bignum& other)
	{
		for(int i=MAXSIZE-1;i>-1;--i)
		{
			if(Number[i]<other.Number[i]) return 0;
			if(Number[i]>other.Number[i]) return 1;
		}
		return 0;
	}
	bool operator <= (Bignum& other)
	{
		return !(*this > other);
	}
};
Bignum operator+(Bignum a,const Bignum& b)
{
	return a+=b;
}
Bignum operator-(Bignum a,const Bignum& b)
{
	return a-=b;
}
Bignum operator*(Bignum a,const Bignum& b)
{
	return a*=b;
}
Bignum operator/(Bignum a,Bignum& b)//
{
	return a/=b;
}
bool operator==(Bignum a, Bignum& b)
{
	for(int i = 0; i < a.MAXSIZE; i++)
		if(a.Number[i] != b.Number[i]) return false;
	return true;
}
bool operator!=(Bignum a, Bignum& b)
{
	return !(a == b);
}

//-----------------------End Bignum--------------------------------------
Bignum GCD(Bignum a, Bignum b)
{
	Bignum zero(0), r;
	if(a < b) swap(a, b);
	while((r = a%b) != zero)
	{
		a = b;
		b = r;
	}
	return  b;
}