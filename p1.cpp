#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <vector> 
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

  // Temporary variables
  unsigned long long addr;
  char behavior[10];
  unsigned long long target;

  // Open file for reading
  FILE *input = fopen("./test_input.txt", "r");

  // The following loop will read a hexadecimal number and
  // a string each time and then output them
	vector <string> behaves;
  while(fscanf(input, "%llx %10s %llx\n", &addr, behavior, &target) != EOF) {
    if(!strncmp(behavior, "T", 2)) {
      printf("%lld -> taken, target=%lld\n", addr, target);
			behaves.push_back("T");
    }else {
      printf("%lld -> not taken, target=%lld\n", addr, target);
			behaves.push_back("NT");
    }
  }

  return 0;
}

int alwaysT(vector<string> l){
	int correct = 0;
	for(int i = 0; i <l.size(); i++){
		if(l[i] == "T")
			correct++;
	}
	return correct;
}

int alwaysNT(vector<string> l){
	int correct = 0;
	for(int i = 0; i <l.size(); i++){
		if(l[i] == "NT")
			correct++;
	}
	return correct;
}
int bimodal(vector<string> l){
	int correct = 0;
	string predict = "T";
	for(int i = 0; i<l.size(); i++){
		if(l[i] == predict)
			correct++;
		else
			predict = l[i];
	}
	return correct;
}

