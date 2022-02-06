//Key Re-distribution Method 2

#include<iostream>
using namespace std;

const int d=2;

struct bdnode{
	int data[2*d+1], space[2*d+1];
	struct bdnode *PTR[2*d+2];
	int d;
};

struct qnode{
	struct bdnode *TEMP=NULL;
	struct qnode *next=NULL;
};

struct Queue{
	struct qnode *F=NULL;
	struct qnode *R=NULL;
};

struct snode{
	struct bdnode *TR;
	struct snode *next;
};

struct stack{
	struct snode *T;
};

typedef struct bdnode *BDPTR;
typedef struct qnode* QPTR;
typedef struct snode* SPTR;

void L_enq(Queue &A, BDPTR M)
{
	QPTR T=NULL, F=A.F;
	T=new(qnode);
	T->TEMP=M;
	if(A.F == NULL)
	{
		A.F=T;
		A.R=T;
		T->next=NULL;
	}	
	else
	{
		while(F!=A.R)
			F=F->next;
		T->next=NULL;
		F->next=T;
		A.R=T;
	}
}

BDPTR L_deq(Queue &A)
{
	int t=0;
	QPTR TEMP;
	if(A.F == NULL)
		cout<<"\nEmpty!";
	else
	{
		BDPTR P=A.F->TEMP;
		TEMP=A.F;
		A.F=A.F->next;
		delete(TEMP);
		return P;
	}
}

BDPTR pop(stack &m){
	SPTR TEMP=m.T;
	BDPTR x=TEMP->TR;
	m.T=m.T->next;
	delete(TEMP);
	return x;	
}

void push(stack &m, BDPTR B){
	SPTR TEMP;
	TEMP=new(snode);
	TEMP->TR = B;
	TEMP->next=m.T;
	m.T=TEMP;
}

void handleOverflow(BDPTR &T, BDPTR P){
	BDPTR TEMP=new(bdnode); //Temporary node
	for(int i=0; i<2*d+2; i++){
		if(i<2*d+2) TEMP->data[i]=0;
		TEMP->PTR[i]=NULL;
	}
	//copying data into new node
	for(int i=d+1; i<2*d+1; i++) TEMP->data[i-(d+1)]=T->data[i]; 
	for(int i=d+1; i<2*d+2; i++) TEMP->PTR[i-d-1]=T->PTR[i];
	TEMP->d=d;
	//sort(TEMP);
	//changing old node
	int med=T->data[d], i=0;
	T->d=d;
 	for(int i=d; i<2*d+1; i++){
 		T->PTR[i+1]=NULL;
 		T->data[i]=0;
	 }
	//-------------------- PARENT STUFF-----------------/
	if(!P){
		P=new(bdnode);
		for(int j=0; j<2*d+1; ++j) P->data[j]=0;
		P->data[0]=med;
		P->d=1;
		for(int j=0; j<2*d+2; ++j) P->PTR[j]=NULL;
		P->PTR[0]=T;
		P->PTR[1]=TEMP;
		T=P;
	}
	else{
		int j=0;
		while(med > P->data[j] && j<P->d) j++;
		for(int i=P->d; i>j; --i) P->data[i]=P->data[i-1];
		P->d+=1;
		for(int i=P->d; i>j; --i) P->PTR[i]=P->PTR[i-1];
		P->data[j]=med;
		P->PTR[j+1]=TEMP;
	}
}

int isnotLeaf(BDPTR T){
	for(int i=0; i<2*d+2; i++){
		if(T->PTR[i]) return 1;
	}
	return 0;	
}

void putintoArray(BDPTR T, int a[], int &m, int i, int p){
	if(T->PTR[i] && i<=p){
		putintoArray(T->PTR[i],a,m,i,p);
		if(i<=T->d){
			a[m++]=T->data[i];
			T->data[i]=0;
			putintoArray(T,a,m,++i,p);
		}
	}
	else if(i<=p){
		int j=0;
		for(j=0; j<T->d; j++){
			a[m++]=T->data[j];
			T->data[j]=0;
		}
		if(T->d == 2*d+1) T->d-=1;
	}
}

void insertfromArray(BDPTR T, int a[], int m, int i, int &k, int p){
	if(T->PTR[i] && i<=p){
		insertfromArray(T->PTR[i],a,m,i,k,p);
		if(i<T->d && k<m){
			T->data[i]=a[k++];
			insertfromArray(T,a,m,++i,k,p);
		}
	}
	else if(i<=p){
		int j=0;
		if(T->d < 2*d) T->d+=1;
		for(j=0; j<T->d && k<m ;j++){
			T->data[j]=a[k++];
		}
	}
}

int isnotFull(BDPTR T){
	for(int i=0; i<=T->d; i++){
		if(T->PTR[i]){
			if(T->PTR[i]->d < 2*d) return i;
			else continue;
		}
	}
	return 0;
}

void print_line(Queue A, BDPTR T){
	L_enq(A,T);
	L_enq(A,NULL);
	do
	{
		T=L_deq(A);
		if(T==NULL)
		{
			cout<<"\n";
			T=L_deq(A);
			L_enq(A,NULL);
		}
		for(int i=0; i<=T->d; i++){
			if(T->data[i]!=0)cout<<T->data[i]<<" ";
			if(T->PTR[i]) L_enq(A,T->PTR[i]);
		}
		cout<<"   ";
	}while(A.F!=A.R);
}

void insert(BDPTR &T, int k, BDPTR P, int t=0){
	if(!T || T->data[0]==0){
		if(t==0)T=new(bdnode);
		int i=0;
		for(int j=0; j<2*d+1; ++j) T->data[j]=0;
		T->data[i]=k;
		T->d=1;
		for(int j=0; j<2*d+2; ++j) T->PTR[j]=NULL;
	}
	else{ //IF PARENT NODE EXISTS
		if(isnotLeaf(T)){
			int j=0; 
			while(k > T->data[j] && T->data[j]!=0 && j<2*d+1) j++;
			insert(T->PTR[j],k,T,j);
		}
		else{
			int j=0;
			while(k>T->data[j] && j<T->d) j++;
			for(int i=T->d; i>j; --i) T->data[i]=T->data[i-1];
			T->d+=1;
			T->data[j]=k;	
		}
		//overflow condition	
		if(T->d==2*d+1){
			int a[20], m=0;
			if(P){
				if(isnotFull(P)){
					int i=0;
					int n=isnotFull(P);
					if(n<=t) n=t;
					putintoArray(P,a,m,0,n);
					insertfromArray(P,a,m,0,i,n);
				}
				else handleOverflow(T,P);
			}
			else handleOverflow(T,P);
		}
	}	
}

int main()
{
	BDPTR T=NULL;
	Queue A;
	//int b[8]={9,2,15,30,5,40,25,7};
	int b[22]={4,7,22,21,35,12,23,39,16,32,29,46,28,43,64,9,49,53,40,42,24,60};
	cout<<"Input is : ";
	for(int i=0; i<22; i++) cout<<b[i]<<" ";
	cout<<"\n";
	for(int i=0; i<22; i++){
		insert(T,b[i],NULL);
		print_line(A,T);
		cout<<"\n----------------------------------\n";
	}
	cout<<"Tree (line by line) is : "<<endl;
	print_line(A,T);
	return 0;
}
