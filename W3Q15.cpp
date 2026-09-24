#include <iostream>
#include <string.h>

using namespace std;

class MIPS{
    private:
    char *shamt,*opcode,*opcodei;
    public:
    char *rs,*rd,*rt,*funct;

    string getshamt(){
        return shamt;
    }
     string getopcode(){
        return opcode;
    }

       string getopcodei(){
        return opcodei;
    }
    
    MIPS(){
        shamt=(char *)"00000";
        opcode=(char *)"000000";
        opcodei=(char *)"001000";
    };
   
};

class sum:public MIPS{
    public:
    sum(char *addrt, char *addrd, char *addrs, char *addfunct):MIPS(){

        rt=addrt;
        rs=addrs;
        rd=addrd;
        funct=addfunct;       
    }
  
     string setrs(){
        int num=this->rs[2]-'0';
       
        return sets(num);
     }

     string setrt(){
        int num=this->rt[2]-'0';
        return sets(num);

     }

      string setrd(){
        int num=this->rd[2]-'0';
        return sets(num);
      }

      string sets(int n){

         switch(n){
            case 0:
            return "01000";
            
            case 1:
            return "01001";
            
            case 2:
            return "01010";

            case 3:
            return "01011";

            case 4:
            return "01100";

            case 5:
            return "01101";

            case 6:
            return "01110";

            case 7:
            return "01111";
        }

      }

      void print(){

            cout<<this->getopcode()<<this->setrs()<<this->setrt()<<this->setrd()<<this->getshamt()<<this->funct<<endl;

        }

        string setrdi(){
           
            int num=atoi(this->rt);

            if(num==0){
                char zero[]="0000000000000000";
                return zero;

            }else{
            
            char binary[10]="\0";
            char extra0s[20]="\0";
            binarycode(num,binary);
    
            sprint(binary,extra0s);

            strcat(extra0s, binary);
            
            return extra0s;
            }
        }

        void binarycode(int n, char *b){
      
            if(n>0){
                binarycode(n/2,b);
                sprintf(b, "%s%d", b,n%2);
               
            }

        }

        void sprint(char *d, char *e){
            if(strlen(d)<16){
                
                for(int i=strlen(d);i<15;i++){
                    sprintf(e, "%c%s",'0',e );
                    
                }
            }
        }

        void printi(){
            cout<<this->getopcodei()<<this->setrd()<<this->setrs()<<this->setrdi()<<endl;

        }        
    
};

int main(){
    char type[6], Rs[6],Rd[6],Rt[6];
    while(scanf("%s", type)==1){
        
        
        scanf("%s", Rd);
        scanf("%s", Rs);
        scanf("%s", Rt);

        if(strcmp(type, "add") == 0) {
        char function[]="100000";
        sum addition(Rt,Rd,Rs,function);
       
        addition.print();
       }else if(strcmp(type, "sub") == 0){

        char function[]="100010";
        sum subtraction(Rt,Rd,Rs,function);

        subtraction.print();
       }else if(strcmp(type, "or") == 0){
        char function[]="100101";
        sum opor(Rt,Rd,Rs,function);

        opor.print();
       }else if(strcmp(type, "and") == 0){
        char function[]="100100";
        sum opand(Rt,Rd,Rs,function);

        opand.print();
       }else if(strcmp(type, "addi") == 0){
        char function[]="001000";
        sum addi(Rt,Rd,Rs,function);

        addi.printi();
       }
    }

}