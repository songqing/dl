#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<sys/stat.h>

using namespace std;
int countNum[11]={0};
int main(){
	const char* filename="lableTxtFile.txt";
	fstream f1;
	f1.open(filename);
	string arg1,arg2;
	int arg3[11]={0};
	int i,j;
	
	//create 10 folders
	const char* folders[10]={"./num0","./num1","./num2","./num3","./num4",
	"./num5","./num6","./num7","./num8","./num9"};
	for(i=0;i<10;i++)
	{
		mkdir(folders[i],0775);
	}
	
	char picpath[25]="./num0/0_0000000000.png";
	const char* picRealPath=picpath;
	//put every pic into the folder
	fstream fTemp;
	int countTemp=0;
	int yu=0;
	int pathTemp=0;
	while(f1>>arg1>>arg2)
	{
//		f1>>arg1>>arg2;
//		cout<<"arg1="<<arg1<<" arg2="<<arg2<<endl;
		for(j=0;j<11;j++)
		{
			f1>>arg3[j];
		//	cout<<arg3[j]<<" ";
		}
//		cout<<endl;
		for(j=9;j<19;j++)
		  picpath[j]='0';
		for(j=0;j<11;j++)
		{
			pathTemp=0;
			switch(arg2[j])
			{
				case '0':
					countNum[0]++;
					picpath[5]='0';
					picpath[7]='0';
					
					countTemp=countNum[0];
					while(countTemp>0)
					{
						yu=countTemp % 10;
						picpath[18-pathTemp++]=yu+'0';
						countTemp/=10;
					}

					picRealPath=picpath;
//					cout<<picRealPath<<endl;
					fTemp.open(picRealPath,ios::out);
					if(!fTemp)
					{
						cout<<"put pic into folder failed!"<<endl;
						exit(1);
					}
					fTemp.close();
					break;
				case '1':
					countNum[1]++;
					picpath[5]='1';
					picpath[7]='1';
					
					countTemp=countNum[1];
					while(countTemp>0)
					{
						yu=countTemp % 10;
						picpath[18-pathTemp++]=yu+'0';
						countTemp/=10;
					}

					picRealPath=picpath;
//					cout<<picRealPath<<endl;
					fTemp.open(picRealPath,ios::out);
					if(!fTemp)
					{
						cout<<"put pic into folder failed!"<<endl;
						exit(1);
					}
					fTemp.close();
					break;
				case '2':
					countNum[2]++;
					picpath[5]='2';
					picpath[7]='2';
					
					countTemp=countNum[2];
					while(countTemp>0)
					{
						yu=countTemp % 10;
						picpath[18-pathTemp++]=yu+'0';
						countTemp/=10;
					}

					picRealPath=picpath;
//					cout<<picRealPath<<endl;
					fTemp.open(picRealPath,ios::out);
					if(!fTemp)
					{
						cout<<"put pic into folder failed!"<<endl;
						exit(1);
					}
					fTemp.close();
					break;
				case '3':
					countNum[3]++;
					picpath[5]='3';
					picpath[7]='3';
					
					countTemp=countNum[3];
					while(countTemp>0)
					{
						yu=countTemp % 10;
						picpath[18-pathTemp++]=yu+'0';
						countTemp/=10;
					}

					picRealPath=picpath;
//					cout<<picRealPath<<endl;
					fTemp.open(picRealPath,ios::out);
					if(!fTemp)
					{
						cout<<"put pic into folder failed!"<<endl;
						exit(1);
					}
					fTemp.close();
					break;
				case '4':
					countNum[4]++;
					picpath[5]='4';
					picpath[7]='4';
					
					countTemp=countNum[4];
					while(countTemp>0)
					{
						yu=countTemp % 10;
						picpath[18-pathTemp++]=yu+'0';
						countTemp/=10;
					}

					picRealPath=picpath;
//					cout<<picRealPath<<endl;
					fTemp.open(picRealPath,ios::out);
					if(!fTemp)
					{
						cout<<"put pic into folder failed!"<<endl;
						exit(1);
					}
					fTemp.close();
					break;
				case '5':
					countNum[5]++;
					picpath[5]='5';
					picpath[7]='5';
					
					countTemp=countNum[5];
					while(countTemp>0)
					{
						yu=countTemp % 10;
						picpath[18-pathTemp++]=yu+'0';
						countTemp/=10;
					}

					picRealPath=picpath;
//					cout<<picRealPath<<endl;
					fTemp.open(picRealPath,ios::out);
					if(!fTemp)
					{
						cout<<"put pic into folder failed!"<<endl;
						exit(1);
					}
					fTemp.close();
					break;
				case '6':
					countNum[6]++;
					picpath[5]='6';
					picpath[7]='6';
					
					countTemp=countNum[6];
					while(countTemp>0)
					{
						yu=countTemp % 10;
						picpath[18-pathTemp++]=yu+'0';
						countTemp/=10;
					}

					picRealPath=picpath;
//					cout<<picRealPath<<endl;
					fTemp.open(picRealPath,ios::out);
					if(!fTemp)
					{
						cout<<"put pic into folder failed!"<<endl;
						exit(1);
					}
					fTemp.close();
					break;
				case '7':
					countNum[7]++;
					picpath[5]='7';
					picpath[7]='7';
					
					countTemp=countNum[7];
					while(countTemp>0)
					{
						yu=countTemp % 10;
						picpath[18-pathTemp++]=yu+'0';
						countTemp/=10;
					}

					picRealPath=picpath;
//					cout<<picRealPath<<endl;
					fTemp.open(picRealPath,ios::out);
					if(!fTemp)
					{
						cout<<"put pic into folder failed!"<<endl;
						exit(1);
					}
					fTemp.close();
					break;
				case '8':
					countNum[8]++;
					picpath[5]='8';
					picpath[7]='8';
					
					countTemp=countNum[8];
					while(countTemp>0)
					{
						yu=countTemp % 10;
						picpath[18-pathTemp++]=yu+'0';
						countTemp/=10;
					}

					picRealPath=picpath;
//					cout<<picRealPath<<endl;
					fTemp.open(picRealPath,ios::out);
					if(!fTemp)
					{
						cout<<"put pic into folder failed!"<<endl;
						exit(1);
					}
					fTemp.close();
					break;
				case '9':
					countNum[9]++;
					picpath[5]='9';
					picpath[7]='9';
					
					countTemp=countNum[9];
					while(countTemp>0)
					{
						yu=countTemp % 10;
						picpath[18-pathTemp++]=yu+'0';
						countTemp/=10;
					}

					picRealPath=picpath;
//					cout<<picRealPath<<endl;
					fTemp.open(picRealPath,ios::out);
					if(!fTemp)
					{
						cout<<"put pic into folder failed!"<<endl;
						exit(1);
					}
					fTemp.close();
					break;
				default:
					cout<<"number format error!"<<endl;
					exit(1);
			}
		}
	}

	f1.close();
	return 0;
}
