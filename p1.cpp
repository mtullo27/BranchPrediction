#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include <vector> 
#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

int alwaysT(vector<string> l){
  int correct = 0;
  for(int i = 0; i <l.size(); i++){
    //check to see if it is correct prediction
    if(l[i] == "T")
      correct++;
  }
  return correct;
}

int alwaysNT(vector<string> l){
  int correct = 0;
  for(int i = 0; i <l.size(); i++){
    //check to see if it is correct prediction
    if(l[i] == "NT")
      correct++;
  }
  return correct;
}
int bimodal(vector<string> t, vector<long long> pc, int size){
  int correct = 0;
  vector <string>hist;
  for(int i = 0; i<size; i++)
    hist.push_back("T");
  for(int i = 0; i<t.size(); i++){
    int j = pc[i]%size;
    if(t[i]==hist[j])
      correct++;
    else
      hist[j] = t[i];
  }
  return correct;
}  

int bimodal2(vector<string> t, vector<long long> p,  int size){
  int correct = 0;
  vector <string>hist;
  for(int i = 0; i<size; i++){
    hist.push_back("TT");
  }
  for(int i = 0; i<t.size(); i++){
    int j = p[i]%size;
    if(hist[j][0]==t[i][0])
      correct++;
    if(t[i]=="T"){
      if(hist[j]=="TNT")
				hist[j] = "TT";
      if(hist[j]=="NTT")
				hist[j] = "TNT";
      if(hist[j]=="NTNT")
				hist[j] = "NTT";
    }
    if(t[i] == "NT"){
      if(hist[j] == "NTT")
				hist[j] = "NTNT";
      if(hist[j] == "TNT")
				hist[j] = "NTT";
      if(hist[j] == "TT")
				hist[j] = "TNT";
    }
  }
  return correct;
}
int gshare(vector <string>t, vector<long long> p, int size){
  int correct = 0;
  vector<string>hist;
  int global = 0;
  int mod = pow(2,size);
  for(int i = 0; i<2048; i++)
    hist.push_back("TT");
  for(int i = 0; i<t.size(); i++){
    int j = (p[i]^global)%2048;
    if(t[i][0] == hist[j][0])
      correct++;
		//updating preditcor state
    if(t[i]=="T"){                                                        
      if(hist[j]=="TNT")                                                 
				hist[j] = "TT";                                                  
      if(hist[j]=="NTT")                                                 
				hist[j] = "TNT";                                                 
      if(hist[j]=="NTNT")                                                
				hist[j] = "NTT";                                                 
    }                                                                    
    if(t[i] == "NT"){                                                    
      if(hist[j] == "NTT")                                               
				hist[j] = "NTNT";                                                
      if(hist[j] == "TNT")                                              
				hist[j] = "NTT";
      if(hist[j] == "TT")                
				hist[j] = "TNT";                                                
    }  
    if(t[i] == "T")
      global=((global<<1)+1)%mod;
    else
      global = (global<<1)%mod;
  }
  return correct;
}
int tournament(vector<string> t, vector<long long> p){
  int correct = 0;
  int size = 2048;
  int gsize = 11;
  bool gCorrect = false;
  bool bCorrect = false;
  vector<string>hist;
  vector<string>hist1;
  vector<int>selector;
  int global = 0;
  int mod = pow(2,gsize);                                                      
  for(int i = 0; i<2048; i++){    //gshare
    selector.push_back(0);
    hist.push_back("TT");
    hist1.push_back("TT");
  }
  for(int i = 0; i<t.size(); i++){                                             
    int j = (p[i]^global)%2048;                                                
    if(t[i][0] == hist[j][0])                                                  
      gCorrect = true;
    if(t[i]=="T"){                                                             
      if(hist[j]=="TNT")                                                 
				hist[j] = "TT";                                                  
      if(hist[j]=="NTT")                                                 
				hist[j] = "TNT";                                                 
      if(hist[j]=="NTNT")                                                
				hist[j] = "NTT";                                                 
    }              
    if(t[i] == "NT"){
      if(hist[j] == "NTT")                                               
				hist[j] = "NTNT";                                                
      if(hist[j] == "TNT")                                               
				hist[j] = "NTT";                                                 
      if(hist[j] == "TT")                                                
				hist[j] = "TNT";                                                 
    }                                                                    
    if(t[i] == "T")                                                            
      global=((global<<1)+1)%mod;                                              
    else                                                                       
      global = (global<<1)%mod;                                                
    //bimodal                                                                                 
    int b = p[i]%size;                                                   
    if(hist1[b].at(0)==t[i].at(0))                                             
      bCorrect = true;                                                      
    if(t[i]=="T"){                                                       
      if(hist1[b]=="TNT")                                                
				hist1[b] = "TT";                                                 
      if(hist1[b]=="NTT")                                                
				hist1[b] = "TNT";                                                
      if(hist1[b]=="NTNT")                                               
				hist1[b] = "NTT";                                                
    }                                                                   
    if(t[i] == "NT"){                                                   
      if(hist1[b] == "NTT");
	 			hist1[b] = "NTNT";                                               
	 		if(hist1[b] == "TNT")                                              
	   		hist1[b] = "NTT";                                                
	 		if(hist1[b] == "TT")                                               
	   		hist1[b] = "TNT";                                                
    }                                                                    
    //updating selector
    if(selector[b]<2){
      if(gCorrect){
				correct++;
				if(!bCorrect)
	  			selector[b] = 0;
      }
      if(!gCorrect){
				if(bCorrect)
	  			selector[b]++;
	 hist1[b] = "NTNT";                                               
	 if(hist1[b] == "TNT")                                              
	   hist1[b] = "NTT";                                                
	 if(hist1[b] == "TT")                                               
	   hist1[b] = "TNT";                                                
    }  
	  	  //updating selector
    if(selector[b]<2){
      if(gCorrect){
	correct++;
	if(!bCorrect)
	  selector[b] = 0;
      }
      if(!gCorrect){
	if(bCorrect)
	  selector[b]++;
      }
    }
    if(selector[b]>1){
      if(bCorrect){
				correct++;
			if(!gCorrect)
	  		selector[b] = 3;
      }
      if(!bCorrect){
				if(gCorrect)
	  			selector[b]--;
      }
    }
  }
	correct++;
	if(!gCorrect)
	  selector[b] = 3;
      }
      if(!bCorrect){
	if(gCorrect)
	  selector[b]--;
      }
    }
  return correct;
}
vector <int> BTB(vector<long long>pc, vector<string> behave, vector<long long> target){
  vector <int> ret;
  int numCorrect = 0;
  int numAccess = 0;
  int size = 512;
  vector <string> prediction;
  vector <vector<long long>> bTarget;
  for(int i = 0; i<size; i++)
    prediction.push_back("T");
  for(int i = 0; i<128; i++)
		//[0] is the address and [1] is the target
    bTarget.push_back({0,0});
  for(int i = 0; i<pc.size(); i++){
    int index = pc[i]%size;
    int bIndex = pc[i] %128;
		if(prediction[index]=="T"){
      numAccess++;
      if(bTarget[bIndex][1] != target[i]||bTarget[bIndex][0] != pc[i]){
				bTarget[bIndex][1] = target[i];
				bTarget[bIndex][0] = pc[i];
			}
    	 else
				numCorrect++;
		}
		if(!(prediction[index] == behave[i]))
			prediction[index] = behave[i];
  }
  ret.push_back(numCorrect);
  ret.push_back(numAccess);
  return ret;
}

int main(int argc, char *argv[]) {

  // Temporary variables
  unsigned long long addr;
  char behavior[10];
  unsigned long long target;

  // Open file for reading
  FILE *input = fopen(argv[1], "r");
  ofstream cout(argv[2]);
  // The following loop will read a hexadecimal number and
  // a string each time and then output them
  vector <string> behaves;
  vector <long long> pc;
  vector <long long> targets; 
  while(fscanf(input, "%llx %10s %llx\n", &addr, behavior, &target) != EOF) {
    if(!strncmp(behavior, "T", 2)) {
      behaves.push_back("T");
    }else {
      behaves.push_back("NT");
    }
    pc.push_back(addr);
    targets.push_back(target);
  }
  vector<int> vect{16,32, 128, 256, 512, 1024, 2048};
  cout << alwaysT(behaves) << "," << behaves.size() << "; " << endl;
  cout << alwaysNT(behaves) << "," << behaves.size() << "; " << endl;
  for(int i = 0; i<vect.size(); i++){
    cout << bimodal(behaves, pc, vect[i]) << "," << behaves.size() << "; ";  
  }
  cout <<  endl;
  for(int i = 0; i<vect.size(); i++){                                       
    cout << bimodal2(behaves, pc, vect[i]) << ","<< behaves.size() << "; ";                          
  }                                                                          
  cout << endl;
  for(int i = 3; i<12; i++)
    cout << gshare(behaves, pc, i) <<"," << behaves.size() << "; ";
  cout << endl;
  cout<< tournament(behaves, pc) << "," << behaves.size() << "; " << endl;
  cout << BTB(pc, behaves, targets)[1] << "," << BTB(pc, behaves, targets)[0] << "; " <<endl;
  return 0;
}


