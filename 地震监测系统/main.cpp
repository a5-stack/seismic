/*
#define _CRTDBG_MAP_ALLOC 
#include<stdlib.h>
#include<crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new (_NORMAL_BLOCK,_FILE_,_LINE_)
#define new DBG_NEW
#endif
#endif
*/
#include<iostream>
#include<Windows.h>
#include<fstream>
#include<string>
#include<cmath>

using namespace std;

const double THRESHOLD=1.5;  //阈值

double power_w(double seismic[],int length,int n);

int main(){
	string fileName;
	ifstream fin;
	int num=0;
	double time_incr=0;  //时间间隔
	double *sensor=NULL;
	int shortNum=0;
	int longNum=0;
	double short_power;
	double long_power;
	double ratio=0;

	cout<<"Please enter name of input file:";
	cin>>fileName;

	fin.open(fileName.c_str());
	if(fin.fail()){
		cerr<<"Error opening input file"<<endl;
		system("pause");
		exit(1);
	}

	fin>>num>>time_incr;

	cout<<"num:"<<num<<" time_incr:"<<time_incr<<endl;

	if(num>=0){
		sensor=new double[num];
		for(int i=0;i<num;i++){
			fin>>sensor[i];
		}

		cout<<"Please enter number of points short-window:";
		cin>>shortNum;
		cout<<"Please enter number of points long-window:";
		cin>>longNum;

		for(int i=longNum-1;i<num;i++){
			short_power=power_w(sensor,i,shortNum);
			long_power=power_w(sensor,i,longNum);
			ratio=short_power/long_power;
			if(ratio>THRESHOLD){
				cout<<"Possible event at "<<time_incr*i<<" seconds!"<<endl;
			}
		}
		delete[] sensor;
	}

	fin.close();
	//_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}

double power_w(double seismic[],int length,int n){
	double average=0;
	
	for(int i=0;i<n;i++){
		average+=pow(seismic[length-i],2);
	}
	return average/n;
}